//
//  main.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 orcudy. All rights reserved.
//

#include <stdio.h>

#include "Socket.hpp"
#include "UDPServer.hpp"

int main(int argc, const char ** argv){

  UDPServer server = UDPServer("127.0.0.1", 4500);
  server.receive();
  
  return 0;
  
}
