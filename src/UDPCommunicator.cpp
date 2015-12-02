//
//  UDPCommunicator.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "UDPCommunicator.hpp"
#include "Header.hpp"
#include "Error.hpp"
#include <iostream>
#include <sys/time.h>


using namespace std;

void UDPCommunicator::baseConstructor(UDPCommunicator * communicator, std::string ip, int port){
  communicator->receiveBufferSize = 1000;
  communicator->receiveBuffer = (char*)malloc(sizeof(char) * receiveBufferSize);
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

int UDPCommunicator::send(char * message){
  int nbytes = (int)sendto(this->socket.descriptor, message, sizeof(char) * sizeof(Header), 0, &this->socket.destinationAddress, this->socket.destinationAddressLength);
  if (nbytes == -1) {
    cout << "Error sending data: " << strerror(errno) << endl;
    Error::exit(1);
  }
  if (printSent){
    struct timeval now;
    gettimeofday(&now, NULL);
    cout << "Sent Data: " << now.tv_sec << " " << now.tv_usec << endl;
    Header * header = ((Header*)message);
    header->description();
    cout << endl;
  }
  return nbytes;
}

char * UDPCommunicator::receive(){
  if ((recvfrom(this->socket.descriptor, this->receiveBuffer, this->receiveBufferSize, 0, &this->socket.destinationAddress, &this->socket.destinationAddressLength)) == -1){
    cout << "Error receiving data: " << strerror(errno) << endl;
    Error::exit(1);
  }
  if (printReceieved){
    struct timeval now;
    gettimeofday(&now, NULL);
    cout << "Received Data: " << now.tv_sec << " " << now.tv_usec << endl;
    Header * header = ((Header*)this->receiveBuffer);
    header->description();
    cout << endl;
  }
  return this->receiveBuffer;
}












