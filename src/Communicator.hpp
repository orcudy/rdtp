//
//  Communicator.hpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COCommunicator
#define COCommunicator

#include "Socket.hpp"
#include <string>

class Communicator {
protected:
  double getPortInfo(struct sockaddr *sa);
  std::string getIPAddress(struct sockaddr *sa);

public:
  Socket socket;
  int receiveBufferSize;

  virtual int send(std::string message) = 0;
  virtual std::string receive() = 0;
};

#endif
