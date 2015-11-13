//
//  UDPCommunicator.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COUDPCommunicator
#define COUDPCommunicator

#include "Communicator.hpp"

class UDPCommunicator: public Communicator {
public:
  //constructor
  UDPCommunicator(std::string ip, int port);
  
  //methods
  int send(std::string message);
  std::string receive();
};

#endif
