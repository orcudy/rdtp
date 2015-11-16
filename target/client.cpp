//
//  main.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <stdio.h>

#include "Socket.hpp"
#include "UDPCommunicator.hpp"

int main(int argc, const char ** argv){
    
  UDPCommunicator client = UDPCommunicator("", 4500);
  client.send("This is a client to server test");
  return 0;
  
}
