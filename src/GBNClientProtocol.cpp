//
//  GBNClientProtocol.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "GBNClientProtocol.hpp"
#include "Header.hpp"
#include <string>

#include <stdlib.h>

using namespace std;

GBNClientProtocol::GBNClientProtocol(int windowSize, string ip, int port){
  this->communicator = UDPCommunicator(ip, port);
  this->windowSize = windowSize;
}


void GBNClientProtocol::sendSyn(){
  Header header = Header();
  header.syn = true;

  const char * filename = "/Users/orcudy/Desktop/rdt/tests/test.txt";
  strncpy(header.filename, filename, strlen(filename));
  header.seqNum = 0;
  communicator.send(header.generateMessage());
}

void GBNClientProtocol::sendAck(int ackNum, int seqNum){
  Header header = Header();
  header.ackNum = ackNum;
  header.seqNum = seqNum;
  communicator.send(header.generateMessage());
}
