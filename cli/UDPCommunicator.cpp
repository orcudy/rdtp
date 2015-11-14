//
//  UDPServer.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <string>

#include "UDPCommunicator.hpp"
#include <sys/socket.h>
#include <iostream>

#define recieve_buffer_size 1000
using namespace std;

UDPCommunicator::UDPCommunicator(string ip, int port){
  this->socket = Socket(ip, port, UDP);
}

int  UDPCommunicator::send(string message){
  return 1;
}

string UDPCommunicator::receive(){
  struct sockaddr client_addr;
  socklen_t client_addr_len;

  char recieve_buffer[recieve_buffer_size];
  ssize_t nbytes = 0;
  if ((nbytes = recvfrom(this->socket.descriptor, recieve_buffer, recieve_buffer_size, 0, &client_addr, &client_addr_len)) == -1){
    cout << "ERROR recieving";
  }
  
  cout << recieve_buffer;
  
  return string(recieve_buffer);
}