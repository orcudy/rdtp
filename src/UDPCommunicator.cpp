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
  this->socket = Socket("", port, UDP);
  this->socket.getAddressInfo();
  this->socket.getDescriptor();
  this->socket.bind();
}

int UDPCommunicator::send(string message){
  
  struct addrinfo hints;
  struct addrinfo *recieverinfo;
  
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  
  int retval = getaddrinfo(this->socket.ip.c_str(), (std::to_string(this->socket.port)).c_str(), &hints, &recieverinfo);
  if (retval != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retval));
    exit(200);
  }
  
  const char buffer[100] = "This is a test";
  int nbytes = (int)sendto(this->socket.descriptor, buffer, 100, 0, recieverinfo->ai_addr, recieverinfo->ai_addrlen);
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