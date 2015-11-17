//
//  server.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include "UDPCommunicator.hpp"
#include "Header.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, const char ** argv){
  
  // !! begin command line argument parsing !!
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
  // !! end command line argument parsing !!
  
  UDPCommunicator server = UDPCommunicator(port);
  char * message = server.receive();
  Header * header = ((Header*)message);
  printf("%s", header->data);
  
  
  
  
  return 0;
}
