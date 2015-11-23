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
  //constructors
  void baseConstructor(UDPCommunicator * communicator, std::string ip, int port);
  //create client who communicates with address <ip> on port <port>
  UDPCommunicator(std::string ip, int port);
  //create server at machine ip listening on port <port>
  UDPCommunicator(int port);
  UDPCommunicator(){};
  
  //instance methods
  int send(char * message);
  char * receive();
};

#endif
