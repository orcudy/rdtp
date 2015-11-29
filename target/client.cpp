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

using namespace std;

int main(int argc, const char ** argv){
  
  // !! begin command line argument parsing !!
  if (argc > 8){
    Error::usage();
  }
  
  std::string ip = "127.0.0.1";
  int port = 4500;
  bool printSent = false;
  bool printReceived = false;
  
  int index;
  for (index = 0; index < argc; index++){
    //indicate ip address
    if (strcmp(argv[index], "-i") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      ip = std::string (argv[index + 1]);
    }
    
    //indicate port
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
  


  GBNClientProtocol client = GBNClientProtocol(10, ip, port);
  client.communicator.sendLog = printSent;
  client.communicator.receieveLog = printReceived;
  
  client.sendSyn();

  char* message = client.communicator.receive();
  Header * header = ((Header*)message);
  cout << header->ackNum;

  
  
  return 0;
}
