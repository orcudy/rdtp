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
  //socket creation instance properties
  struct addrinfo hints;
  struct addrinfo* res;
  
public:
  //constructors
  Socket(std::string ip, int port, TransportLayer type);
  Socket(){};
  
  //instance properties
  struct sockaddr destinationAddress;
  socklen_t destinationAddressLength;

  struct sockaddr sourceAddress;
  socklen_t sourceAddressLength;
  
  int port;
  int descriptor;
  std::string ip;
  TransportLayer type;
  
  //instance methods
  void getAddressInfo();
  void getDescriptor();
  void bind();
};

#endif
