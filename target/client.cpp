//
//  client.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//


#include "Error.hpp"
#include "Socket.hpp"
#include "UDPCommunicator.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, const char ** argv){
  
  if (argc > 5){
    Error::usage();
  }
  
  std::string ip = "127.0.0.1";
  int port = 4500;
  
  int index;
  for (index = 0; index < argc; index++){
    if (strcmp(argv[index], "-i") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      ip = std::string (argv[index + 1]);
    }
    
    if (strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
    }
  }

  
  string message = "This is my string test";
  UDPCommunicator client = UDPCommunicator(ip, port);
  client.send(message);
  return 0;
  
}
