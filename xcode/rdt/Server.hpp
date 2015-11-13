//
//  Server.hpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COServer
#define COServer


#include "Socket.hpp"
#include <string>

class Server {  
public:
  Socket socket;
  virtual int send(std::string message) = 0;
  virtual std::string receive() = 0;
};

#endif
