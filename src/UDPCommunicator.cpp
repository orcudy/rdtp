//
//  UDPCommunicator.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "UDPCommunicator.hpp"
#include <iostream>

using namespace std;

void UDPCommunicator::baseConstructor(UDPCommunicator * communicator, std::string ip, int port){
  communicator->receiveBufferSize = 1000;
  communicator->socket = Socket(ip, port, UDP);
  communicator->socket.getAddressInfo();
  communicator->socket.getDescriptor();
}

UDPCommunicator::UDPCommunicator(string ip, int port){
  baseConstructor(this, ip, port);
}

UDPCommunicator::UDPCommunicator(int port){
  baseConstructor(this, "", port);
  this->socket.bind();
}

int UDPCommunicator::send(string message){
  char * msg = (char*)message.c_str();
  int nbytes = (int)sendto(this->socket.descriptor, msg, strlen(msg), 0, &this->socket.addressInfo, this->socket.addressInfoLength);
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