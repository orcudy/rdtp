//
//  UDPCommunicator.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <iostream>
#include "UDPCommunicator.hpp"

using namespace std;

UDPCommunicator::UDPCommunicator(string ip, int port){
  this->socket = Socket(ip, port, UDP);
  this->socket.getAddressInfo();
  this->socket.getDescriptor();
}

UDPCommunicator::UDPCommunicator(int port){
  UDPCommunicator("", port);
  this->socket.bind();
}

int UDPCommunicator::send(string message){
  struct sockaddr * clientsockaddr = NULL;
  socklen_t len = sizeof(clientsockaddr);
  int nbytes = (int)sendto(this->socket.descriptor, message.c_str(), message.size(), 0, clientsockaddr, len);
  // std::string ip = getIPAddress(clientsockaddr);
  // double port = getPortInfo(clientsockaddr);
  //  this->receiver = Socket(ip, port, UDP);
  return nbytes;
}

string UDPCommunicator::receive(){
  struct sockaddr client_addr;
  socklen_t client_addr_len;
  
  char recieve_buffer[1000];
  ssize_t nbytes = 0;
  if ((nbytes = recvfrom(this->socket.descriptor, recieve_buffer, 1000, 0, &client_addr, &client_addr_len)) == -1){
    cout << "ERROR recieving";
  }
  
  cout << recieve_buffer;
  
  return string(recieve_buffer);
}