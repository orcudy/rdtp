//
//  GBNServerProtocol.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "GBNServerProtocol.hpp"
#include "Header.hpp"
#include <iostream>
#include "Timer.hpp"
#include <math.h>
#include <string.h>

using namespace std;

//constructors
GBNServerProtocol::GBNServerProtocol(int windowSize, double timeoutInterval, int port){
  this->communicator = UDPCommunicator(port);
  
  this->timeoutTimer = Timer();
  this->timeoutInterval = timeoutInterval;
  
  this->currentWindowBase = 0;
  this->windowSize = windowSize;
  this->lowestAckedPacket = -1;
  
  this->chunkSize = -1;
  this->fileData = NULL;
  
  this->receivedAckNum = -1;
  this->receivedSeqNum = -1;
  
  this->currentSequenceNum = 0;
  this->expectedAckNum = 0;
  
  this->verbose = false;
  this->keepAlive = true;
  
  this->packetState = (PacketState*)malloc(sizeof(PacketState) * this->totalPackets);
}

// 3-way handshake
bool GBNServerProtocol::receivedSyn(){
  char * message = communicator.receive();
  Header * requestHeader = ((Header*) message);
  
  if (requestHeader->syn) {
    this->chunkSize = requestHeader->chunkSize;
    this->fileSplitter = FileSplitter(requestHeader->filename, this->chunkSize);
    this->fileData = this->fileSplitter.split();
    this->totalPackets = ceil(fileSplitter.fileSize / (double)chunkSize);
    
    for (int index = 0; index < this->totalPackets; index++) {
      this->packetState[index] = Unsent;
    }
    
    return true;
  }
  return false;
}

void GBNServerProtocol::sendSynack(){
  Header responseHeader = Header();
  responseHeader.totalPackets = totalPackets;
  responseHeader.synack = true;
  communicator.send(responseHeader.generateMessage());
}


//data transfer
bool GBNServerProtocol::receivedAck(){
  char * message = communicator.receive();
  Header * receivedHeader = ((Header *) message);

  //check if fin bit set
  if (receivedHeader->fin){
    this->keepAlive = false;
  }
  
  if (receivedHeader->ackNum > this->lowestAckedPacket){
    this->receivedAckNum = receivedHeader->ackNum;
    this->lowestAckedPacket = this->receivedAckNum;
    return true;
  }
  return false;
}

void GBNServerProtocol::sendData(int packetNum){
  char * data = fileData[packetNum];
  if (data){
    int dataSize = (int)strlen(data);
    Header dataHeader = Header();
    dataHeader.seqNum = packetNum;
    dataHeader.ackNum = expectedAckNum;
    dataHeader.dataSize = dataSize;
    dataHeader.setData(data);
    communicator.send(dataHeader.generateMessage());
  }
}


