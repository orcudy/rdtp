//
//  Socket.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COSocket
#define COSocket

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

enum TransportLayer {
  UDP,
  TCP
};

class Socket {
  //properties
  struct addrinfo hints;
  struct addrinfo* res;

public:
  //properties
  int port;
  int descriptor;
  std::string ip;
  TransportLayer type;
  
  //constructor
  Socket(std::string ip, int port, TransportLayer type);
  Socket(){};
  
  //methods
  void getAddressInfo();
  void getDescriptor();
  void bind();
};

#endif
