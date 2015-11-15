//
//  Communicator.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Communicator.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string>

using namespace std;

double Communicator::getPortInfo(struct sockaddr *sa){
  if (sa->sa_family == AF_INET) {
    return ntohs((((struct sockaddr_in*)sa)->sin_port));
  }
  return ntohs((((struct sockaddr_in6*)sa)->sin6_port));
}

string Communicator::getIPAddress(struct sockaddr *sa){
  if (sa->sa_family == AF_INET) {
    char * ip = (char *)&(((struct sockaddr_in*)sa)->sin_addr);
    return string(ip);
  }
  char * ip = (char *)&(((struct sockaddr_in6*)sa)->sin6_addr);
  return string(ip);
}