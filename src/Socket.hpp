//
//  Socket.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COSocket
#define COSocket

#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

enum TransportLayer {
  UDP,
  TCP
};

class Socket {
  //socket creation helpers
  struct addrinfo hints;
  struct addrinfo* res;
  
public:
  //necessary for Socket::send()
  struct sockaddr addressInfo;
  socklen_t addressInfoLength;
  
  int port;
  int descriptor;
  std::string ip;
  TransportLayer type;
  
  Socket(std::string ip, int port, TransportLayer type);
  Socket(){};
  
  void getAddressInfo();
  void getDescriptor();
  void bind();
};

#endif
