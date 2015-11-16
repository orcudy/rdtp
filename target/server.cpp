//
//  server.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include "UDPCommunicator.hpp"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char ** argv){
  
  if (argc > 3){
    Error::usage();
  }
  
  int port = 4500;
  
  int index;
  for (index = 0; index < argc; index++){
    if (strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
    }
  }
  
  UDPCommunicator server = UDPCommunicator(port);
  server.receive();
  
  return 0;
}
