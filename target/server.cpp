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

using namespace std;

void * receiveAck(void *);
//void * receiveFin(void *);
void sendValidPackets(GBNServerProtocol *);
void sendSynack(GBNServerProtocol *);

int main(int argc, const char ** argv){
  
  // !! begin command line argument parsing !!
  if (argc > 10){
    Error::usage();
  }
  
  int port = 45000;
  bool verbose = false;
  bool printSent = false;
  bool printReceived = false;
  int windowSize = 10;
  int timeoutInterval = 2;
  
  for (int index = 0; index < argc; index++){

    //indicate port number
    if (strcmp(argv[index], "--port") == 0 || strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
    }
    
    //indicate window size
    if (strcmp(argv[index], "--window") == 0 || strcmp(argv[index], "-w") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      windowSize = atoi(argv[index + 1]);
    }
    
    //indicate timeout interval
    if (strcmp(argv[index], "--timeout") == 0 || strcmp(argv[index], "-t") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      timeoutInterval = atoi(argv[index + 1]);
    }
    
    //print all sent data
    if (strcmp(argv[index], "--print-sent") == 0 || strcmp(argv[index], "-ps") == 0){
      printSent = true;
    }
    
    //print all received data
    if (strcmp(argv[index], "--print-recv") == 0 || strcmp(argv[index], "-pr") == 0){
      printReceived = true;
    }
    
    //print all data
    if (strcmp(argv[index], "--print-all") == 0 || strcmp(argv[index], "-pa") == 0){
      printReceived = true;
      printSent = true;
    }
    
    //print server protocol
    if (strcmp(argv[index], "--verbose") == 0 || strcmp(argv[index], "-v") == 0){
      verbose = true;
    }
  }
  // !! end command line argument parsing !!
  
  GBNServerProtocol server = GBNServerProtocol(windowSize, timeoutInterval, port);
  server.communicator.receieveLog = printReceived;
  server.communicator.sendLog = printSent;
  server.verbose = verbose;
  
  // !! Begin Handshake !!
  
  if (server.verbose){
    cout << "Waiting for connection on port " << server.communicator.socket.port << "." << endl;
  }
  
  //waiting for client to request connection
  while (!server.receivedSyn());
  if (server.verbose){
    cout << "Received Syn." << endl;
  }
  
  if (server.verbose){
    cout << "Sending synack." <<  endl;
  }
  sendSynack(&server);
  
  //wait for synack ack
  pthread_t receiveThread;
  if (pthread_create(&receiveThread, NULL, receiveAck, &server)) {
    cout << "Error creating thread." << endl;
    exit(1);
  }
  
  //resend synack at timeout
  while (server.timeoutTimer.timing){
    if (server.timeoutTimer.elapsedTime() >= server.timeoutInterval){
      if (server.verbose){
        cout << "Timed out! Resending synack." << endl;
      }
      sendSynack(&server);
    }
  }
  
  //join thread when ack received
  if (pthread_join(receiveThread, NULL)) {
    cout << "Error joining thread" << endl;
    exit(1);
  }
  
  // !! Begin Data Transmission !!
  
//  //wait for fin
//  pthread_t finThread;
//  if (pthread_create(&finThread, NULL, receiveFin, &server)) {
//    cout << "Error creating fin thread" << endl;
//    exit(1);
//  }
  
  //continually send data
  while (server.currentWindowBase < server.totalChunks ){
    if (!server.keepAlive) {
      return 0;
    }
    
    if (server.verbose){
      cout << "Current window base: " << server.currentWindowBase << ", Total chunks: " << server.totalChunks << endl;
    }
    sendValidPackets(&server);
    
    //wait for ack
    if (pthread_create(&receiveThread, NULL, receiveAck, &server)) {
      cout << "Error creating receive thread" << endl;
      exit(1);
    }
    
    //resend data at timeout
    while (server.timeoutTimer.timing){
      if (!server.keepAlive){
        return 0;
      }
      if (server.timeoutTimer.elapsedTime() >= server.timeoutInterval){
        if (server.verbose){
          cout << "Timed out! Resending packets " << server.currentWindowBase << " to " << server.currentWindowBase + server.windowSize << endl;
        }
        sendValidPackets(&server);
      }
    }
    
    //join thread when ack received
    if (pthread_join(receiveThread, NULL)) {
      cout << "Error joining receive thread" << endl;
      exit(1);
    }
  }
  
//  //join thread when fin received
//  if (pthread_join(finThread, NULL)) {
//    cout << "Error joining fin thread" << endl;
//    exit(1);
//  } else {
//    return 0;
//  }
  
  return 0;
}

//receives ack in new thread
void * receiveAck(void * aserver){
  GBNServerProtocol * server = (GBNServerProtocol*)aserver;
  while(!server->receivedAck());
  if (server->verbose){
    cout << "Received ack " << server->receivedAckNum << " with current window base at " << server->currentWindowBase << " with window size " << server->windowSize <<  endl;
  }
  server->currentWindowBase = server->receivedAckNum;
  server->timeoutTimer.stop();
  return NULL;
}

////receive fin in new thread
//void * receiveFin(void * aserver){
//  GBNServerProtocol * server = (GBNServerProtocol*)aserver;
//  while(!server->receiveFin());
//  server->sendFin();
//  return NULL;
//}

//sends all packets in current window
void sendValidPackets(GBNServerProtocol * server){
  for (int packetNum = server->currentWindowBase; packetNum < server->currentWindowBase + server->windowSize; packetNum++){
    if (packetNum < server->totalChunks){
      if (server->verbose){
        cout << "Sending packet number " << packetNum + 1 << " of " << server->totalChunks << endl;
      }
      server->sendData(packetNum);
      server->timeoutTimer.start();
    }
  }
}

//sends synack
void sendSynack(GBNServerProtocol * server){
  server->sendSynack();
  server->timeoutTimer.start();
}


