//
//  main.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <stdio.h>

#include "UDPCommunicator.hpp"

int main(int argc, const char ** argv){
  
  UDPCommunicator server = UDPCommunicator(4500);
  server.receive();
  
  return 0;
}
