//
//  UDPCommunicator.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COUDPCommunicator
#define COUDPCommunicator

#include "Communicator.hpp"

class UDPCommunicator: public Communicator {
public:
  //create client who communicates with address <ip> on port <port>
  UDPCommunicator(std::string ip, int port);
  //create server at machine ip listening on port <port>
  UDPCommunicator(int port);
  
  int send(std::string message);
  std::string receive();
};

#endif
