//
//  server.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include "GBNServerProtocol.hpp"
#include "Header.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <string.h>

using namespace std;

void * receiveAck(void *);
void sendValidPackets(GBNServerProtocol *);
void resendValidPackets(GBNServerProtocol *);
void sendSynack(GBNServerProtocol *);

int main(int argc, const char ** argv){

// !! Begin Command Line Argument Parsing !!

  if (argc > 9){
    Error::usage();
  }

  int port = 45000;
  bool verbose = false;
  bool printSent = false;
  bool printReceived = false;
  int windowSize = 10;
  int timeoutInterval = 2;

  for (int index = 1; index < argc; index++){

    //indicate port number
    if (strcmp(argv[index], "--port") == 0 || strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
      index++;
    }

    //indicate window size
    else if (strcmp(argv[index], "--window") == 0 || strcmp(argv[index], "-w") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      windowSize = atoi(argv[index + 1]);
      index++;
    }

    //indicate timeout interval
    else if (strcmp(argv[index], "--timeout") == 0 || strcmp(argv[index], "-t") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      timeoutInterval = atoi(argv[index + 1]);
      index++;
    }

    //print all sent data
    else if (strcmp(argv[index], "--print-sent") == 0 || strcmp(argv[index], "-ps") == 0){
      printSent = true;
    }

    //print all received data
    else if (strcmp(argv[index], "--print-recv") == 0 || strcmp(argv[index], "-pr") == 0){
      printReceived = true;
    }

    //print all data
    else if (strcmp(argv[index], "--print-all") == 0 || strcmp(argv[index], "-pa") == 0){
      printReceived = true;
      printSent = true;
    }

    //print server protocol
    else if (strcmp(argv[index], "--verbose") == 0 || strcmp(argv[index], "-v") == 0){
      verbose = true;
    }else {
      Error::usage();
      Error::exit(-1);
    }
  }

// !! Begin GBN Server Initialization  !!

  GBNServerProtocol server = GBNServerProtocol(windowSize, timeoutInterval, port);
  server.communicator.printReceieved = printReceived;
  server.communicator.printSent = printSent;
  server.verbose = verbose;

// !! Begin Handshake !!

  if (server.verbose){
    cout << "Waiting for connection on port " << server.communicator.socket.port << "." << endl;
  }

  //waiting for client to request connection
  while (!server.receivedSyn());
  if (server.verbose){
    cout << "Received: Syn." << endl;
    cout << "Sent: Synack." << endl << endl;
  }
  sendSynack(&server);

  //wait for synack ack
  pthread_t receiveSynackThread;
  if (pthread_create(&receiveSynackThread, NULL, receiveAck, &server)) {
    cout << "Error creating ack thread." << endl;
    exit(1);
  }

  //resend synack at timeout
  while (server.timeoutTimer.valid){
    if (server.timeoutTimer.elapsedTime() >= server.timeoutInterval){
      if (server.verbose){
        cout << "Timed out!" << endl;
        cout << "Sent: Synack." << endl << endl;
      }
      sendSynack(&server);
    }
  }

  //join thread when ack received
  if (pthread_join(receiveSynackThread, NULL)) {
    cout << "Error joining ack thread" << endl;
    exit(1);
  }

// !! Begin Data Transmission !!

  //send data
  while (server.keepAlive/* && (server.currentWindowBase < server.totalPackets)*/ ){
    if (server.verbose){
      cout << "Current window base: " << server.currentWindowBase << ", Total packets: " << server.totalPackets << endl;
    }
    server.timeoutTimer.valid = true;
    sendValidPackets(&server);


    //wait for ack
    pthread_t receiveAckThread;
    if (pthread_create(&receiveAckThread, NULL, receiveAck, &server)) {
      cout << "Error creating ack thread" << endl;
      exit(1);
    }

    //resend data at timeout
    while (server.keepAlive && server.timeoutTimer.valid){
      if (!server.timeoutTimer.timing){
        server.timeoutTimer.start();
      }
      if (server.timeoutTimer.elapsedTime() >= server.timeoutInterval){
        if (server.verbose){
          cout << "Timed out!" << endl << "Resending packets " << server.currentWindowBase << " to " << server.currentWindowBase + server.windowSize - 1 << endl;
        }
        resendValidPackets(&server);
      }
    }

    if (!server.keepAlive){
      return 0;
    }

    //join thread when ack received
    if (pthread_join(receiveAckThread, NULL)) {
      cout << "Error joining receive thread" << endl;
      exit(1);
    }
  }
  return 0;
}

//receives ack in new thread
void * receiveAck(void * aserver){
  GBNServerProtocol * server = (GBNServerProtocol*)aserver;
  while(!server->receivedAck());
  if (server->verbose){
    cout << "Received: Ack " << server->receivedAckNum << endl;
  }
  server->currentWindowBase = server->receivedAckNum;
  server->timeoutTimer.stop();
  server->timeoutTimer.valid = false;
  return NULL;
}

//sends all packets in current window
void resendValidPackets(GBNServerProtocol * server){
  for (int packetNum = server->currentWindowBase; packetNum < server->currentWindowBase + server->windowSize; packetNum++){
    if (packetNum < server->totalPackets){
      if (server->verbose){
        cout << "Sent: Packet number " << packetNum << endl;
      }
      server->timeoutTimer.start();
      server->sendData(packetNum);
    } 
  }
  if (server->verbose){
    cout << endl;
  }
}

//TODO: refactorable with resendValidPackets!
void sendValidPackets(GBNServerProtocol * server){
  for (int packetNum = server->currentWindowBase; packetNum < server->currentWindowBase + server->windowSize; packetNum++){
    if (packetNum < server->totalPackets && server->packetState[packetNum] == Unsent){
      if (server->verbose){
        cout << "Sent: Packet number " << packetNum << endl;
      }
      server->packetState[packetNum] = Sent;
      server->timeoutTimer.start();
      server->sendData(packetNum);
    }
  }
  if (server->verbose){
    cout << endl;
  }
}

//sends synack
void sendSynack(GBNServerProtocol * server){
  server->timeoutTimer.start();
  server->sendSynack();
}


