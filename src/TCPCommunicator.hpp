//
//  TCPCommunicator.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/13/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COTCPCommunicator
#define COTCPCommunicator

#include <string>

#include "Communicator.hpp"
#include "Socket.hpp"

class TCPCommunicator: public Communicator {
private:
  TCPCommunicator * acceptConnection();
  int concurrentConnections;
  bool listening;
  
public:
  //constructor
  TCPCommunicator(std::string ip, int port);
  TCPCommunicator(){};
  
  //methods
  int send(std::string message);
  std::string receive();
  
  void startListening();
  void stopListening();
  
  void setConcurrentConnections(int connections){this->concurrentConnections = connections;};
  int getConcurrentConnections(){return this->concurrentConnections;};
};

#endif
