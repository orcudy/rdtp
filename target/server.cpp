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

using namespace std;

int main(int argc, const char ** argv){
  
  // !! begin command line argument parsing !!
  if (argc > 6){
    Error::usage();
  }
  
  int port = 4500;
  bool printSent = false;
  bool printReceived = false;
  for (int index = 0; index < argc; index++){
    //indicate port number
    if (strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
    }
    
    //print all sent data
    if (strcmp(argv[index], "--print-sent") == 0){
      printSent = true;
    }
    
    //print all received data
    if (strcmp(argv[index], "--print-recv") == 0){
      printReceived = true;
    }
    
    //print all data
    if (strcmp(argv[index], "--print") == 0){
      printSent = true;
      printReceived = true;
    }
  }
  // !! end command line argument parsing !!
  
  GBNServerProtocol server = GBNServerProtocol(10, 1, port);
  server.communicator.receieveLog = printReceived;
  server.communicator.sendLog = printSent;
  
  //waiting for client to request connection
  while (!server.receivedSyn());

  //send synack
  server.sendSynack(0, server.expectedAckNum);
  server.synackTimer.start();
  
  //wait for synack ack
  if (fork() == 0){
    while(!server.receivedAck());
    server.synackTimer.stop();
    exit(1);
  }
  
  //resend synack at timeout
  while (server.synackTimer.timing){
    if (server.synackTimer.elapsedTime() >= server.timeoutInterval){
      server.sendSynack(0, server.expectedAckNum);
      server.synackTimer.start();
    }
  }
  
  //reap child
  int status;
  wait(&status);
  
  //begin data transmission
  server.sendData();
  server.ackTimer.start();
  
  //wait for ack
//  if (fork() == 0){
//    while (server.){
//      if (server.receivedAck()){
//        for (int packNum = server.windowBase; packNum < server.receivedAckNum; packNum++){
//          
//        }
//        //track packet number and adjust window accordingly 
//      }
//    }
//  }
  
  
  
  

  


  
  
  
  
  
  
  return 0;
}
