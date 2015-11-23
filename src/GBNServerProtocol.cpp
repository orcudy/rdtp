//
//  GBNServerProtocol.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "GBNServerProtocol.hpp"
#include "Header.hpp"

using namespace std;

//constructors
GBNServerProtocol::GBNServerProtocol(int windowSize, double timeoutInterval, int port){
  this->communicator = UDPCommunicator(port);
  this->windowBase = 0;
  this->windowSize = windowSize;
  this->timeoutInterval = timeoutInterval;
}

// 3-way handshake
bool GBNServerProtocol::receivedSyn(){
  char * message = communicator.receive();
  Header * requestHeader = ((Header*) message);

  if (requestHeader->syn) {
    this->chunkSize = requestHeader->chunkSize;
    this->fileSplitter = FileSplitter(requestHeader->filename, this->chunkSize);
    
    this->fileData = this->fileSplitter.split();
    this->expectedAckNum = requestHeader->seqNum + requestHeader->dataSize + 1;
    return true;
  }
  return false;
}

void GBNServerProtocol::sendSynack(int seqNum, int ackNum){
  Header responseHeader = Header();
  responseHeader.fileSize = (int)this->fileSplitter.fileSize;
  responseHeader.ackNum = ackNum;
  responseHeader.seqNum = seqNum;
  responseHeader.synack = true;
  communicator.send(responseHeader.generateMessage());
}

//data transfer
bool GBNServerProtocol::receivedAck(){
  char * message = communicator.receive();
  Header * receiveHeader = ((Header *) message);
  if (receiveHeader->ackNum == this->expectedAckNum){
    return true;
  }
  return false;
}

void GBNServerProtocol::sendData(){
  for (int packetNum = this->windowBase; packetNum < this->windowSize; packetNum++){
    char * data = fileData[packetNum];
    int dataSize = (int)strlen(data);
    
    Header dataHeader = Header();
    dataHeader.seqNum = packetNum * chunkSize;
    dataHeader.ackNum = expectedAckNum;
    dataHeader.dataSize = dataSize;
    dataHeader.setData(data);
    communicator.send(dataHeader.generateMessage());
  }
}


