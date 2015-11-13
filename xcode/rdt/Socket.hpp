//
//  Socket.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COSocket
#define COSocket

#include <stdio.h>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

enum TransportLayer {
  UDP,
  TCP
};

class Socket {
  //helper members
  struct addrinfo hints;
  struct addrinfo* res;
  
  //methods
  void getAddressInfo();
  void getDescriptor();
  void bind();
  
public:
  //constructor
  Socket(std::string ip, int port, TransportLayer type);
  Socket(){};
  
  //members
  int port;
  std::string ip;
  TransportLayer type;
  int descriptor;
};

#endif
