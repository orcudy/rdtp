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
public:
  Socket socket;
  virtual int send(std::string message) = 0;
  virtual std::string receive() = 0;
};

#endif
