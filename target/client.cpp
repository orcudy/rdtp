//
//  client.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include "Header.hpp"
#include "Socket.hpp"
#include "GBNClientProtocol.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FileSplitter.hpp"
#include <pthread.h>
#include <string.h>

using namespace std;

void * receiveSynAck(void * aclient);
void * receiveFin(void * aclient);

int main(int argc, const char ** argv){

// !! Begin Command Line Argument Parsing !!

  if (argc > 17){
    Error::clientUsage();
  }

  std::string ip = "127.0.0.1";
  int port = 45000;
  bool printSent = false;
  bool printReceived = false;
  bool verbose = false;

  float timeoutInterval = 2;
  std::string filename = "";
  float lostProb = 0;
  float corrProb = 0;

  int index;
  for (index = 0; index < argc; index++){
    //indicate ip address
    if (strcmp(argv[index], "--ip-address") == 0 || strcmp(argv[index], "-i") == 0){
      if (index + 1 == argc) {
        Error::clientUsage();
      }
      ip = std::string (argv[index + 1]);
    }

    //indicate port number
    if (strcmp(argv[index], "--port") == 0 || strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::clientUsage();
      }
      port = atoi(argv[index + 1]);
    }

    //indicate filename
    if (strcmp(argv[index], "--filename") == 0 || strcmp(argv[index], "-f") == 0){
      if (index + 1 == argc) {
        Error::clientUsage();
      }
      filename = std::string(argv[index + 1]);
    }

    //indicate probability of packet loss
    if (strcmp(argv[index], "--lost") == 0 || strcmp(argv[index], "-l") == 0){
      if (index + 1 == argc) {
        Error::clientUsage();
      }
      lostProb = atof(argv[index + 1]);
    }

    //indicate probability of packet being corrupted
    if (strcmp(argv[index], "--corrupt") == 0 || strcmp(argv[index], "-c") == 0){
      if (index + 1 == argc) {
        Error::clientUsage();
      }
      corrProb = atof(argv[index + 1]);
    }

    //indicate timeout interval
    if (strcmp(argv[index], "--timeout") == 0 || strcmp(argv[index], "-t") == 0){
      if (index + 1 == argc) {
        Error::clientUsage();
      }
      timeoutInterval = atof(argv[index + 1]);
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

  if(filename == ""){
    Error::clientUsage();
    Error::exit(-1);
  }

// !! Begin Client Initialization !!

  GBNClientProtocol client = GBNClientProtocol(timeoutInterval, ip, port, filename, lostProb, corrProb);
  client.communicator.printReceieved = printReceived;
  client.communicator.printSent = printSent;
  client.verbose = verbose;

// !! Begin Handshake !!

  if (verbose){
    cout << "Sent: Syn for file " << filename << endl;
  }
  client.sendSyn(filename);
  client.timeout.start();
  
  //wait for synack
  pthread_t receiveThread;
  if(pthread_create(&receiveThread, NULL, receiveSynAck, &client)){
    cout<< "Error creating thread" << endl;
    exit(1);
  }
  
  while(client.timeout.valid){
    if(client.timeout.elapsedTime() >= client.timeoutInterval){
      if (client.verbose){
        cout << "Timed out! Resending syn." << endl;
      }
      client.sendSyn(filename);
      client.timeout.start();
    }
  }
  
  //join thread when synack received
  if(pthread_join(receiveThread, NULL)){
    cout<< "Error joining thread" << endl;
    exit(1);
  }
  
// !! Begin Data Receipt !!
  
  while(client.expectedSeq < client.totalPackets){
    client.receiveData();
  }
  
// !! Begin End Transmission Protocol !!

  if (client.verbose){
    cout << "Data transmission complete." << endl;
    cout << "Sent: Fin." << endl;
  }
  
  //send initial fin
  client.timeout.valid = true;
  client.timeout.start();
  client.sendFin();

  
  //resend fin on timeout, for up to 10 * timeoutInterval
  int finCounter = 0;
  while(finCounter < 10 && client.timeout.valid){
    if (client.timeout.elapsedTime() >= client.timeoutInterval){
      if (client.verbose){
        cout << "Timed out! Resending fin." << endl;
      }
      client.sendFin();
      client.timeout.start();
      ++finCounter;
    }
  }

  return 0;
}

void * receiveSynAck(void * aclient){
  GBNClientProtocol * client = (GBNClientProtocol*)aclient;
  while(!client->receiveSynAck());
  if (client->verbose){
    cout << "Received: Synack." << endl;
  }
  client->timeout.stop();
  client->timeout.valid = false;
  return NULL;
}

void * receiveFin(void * aclient){
  GBNClientProtocol * client = (GBNClientProtocol*)aclient;
  while(!client->receiveFin());
  client->timeout.valid = false;
  return NULL;
}
