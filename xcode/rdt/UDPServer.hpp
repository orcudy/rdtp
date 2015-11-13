//
//  UDPServer.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 orcudy. All rights reserved.
//

#ifndef COUDPServer
#define COUDPServer

#include "Server.hpp"

class UDPServer: public Server {
public:
  UDPServer(std::string ip, int port);
  int send(std::string message);
  std::string receive();
};

#endif
