//
//  main.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <stdio.h>

#include "Socket.hpp"
#include "TCPCommunicator.hpp"

int main(int argc, const char ** argv){

  TCPCommunicator server = TCPCommunicator("127.0.0.1", 4500);
  server.startListening();
  
  return 0;
  
}
