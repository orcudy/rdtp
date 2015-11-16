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
  this->receiveBufferSize = 1000;
  this->socket = Socket(ip, port, UDP);
  this->socket.getAddressInfo();
  this->socket.getDescriptor();
}

UDPCommunicator::UDPCommunicator(int port){
  UDPCommunicator("", port);
  this->socket.bind();
}

int UDPCommunicator::send(string message){
  char buffer[100] = "This is a test";
  int nbytes = (int)sendto(this->socket.descriptor, buffer, 100, 0, &this->socket.addressInfo, this->socket.addressInfoLength);
  if (nbytes == -1) {
    cout << "Error sending data: " << strerror(errno) << endl;
  }
  cout << "nbytes: " << nbytes << endl;
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