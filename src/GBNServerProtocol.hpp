//
//  GBNServerProtocol.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COGBNServerProtocol
#define COGBNServerProtocol

#include <stdio.h>
#include "UDPCommunicator.hpp"
#include "FileSplitter.hpp"
#include "Timer.hpp"


enum PacketState {
  Unsent,
  Sent,
  Acked
};

class GBNServerProtocol{
public:
  UDPCommunicator communicator;
  
  //timers
  Timer timeoutTimer;
  float timeoutInterval;
  
  //window
  int currentWindowBase;
  int windowSize;
  int lowestAckedPacket;
  
  //data
  int chunkSize;
  char ** fileData;
  int totalChunks;
  PacketState * packetState;
  
  //incoming headers
  int receivedAckNum;
  int receivedSeqNum;
  
  //outgoing headers
  int currentSequenceNum;
  int expectedAckNum;
  
  //file splitting
  FileSplitter fileSplitter;
  
  bool verbose;
  
  //constructors
  GBNServerProtocol(int windowSize, double timeoutInterval, int port);
  
  // 3-way handshake
  bool keepAlive;
  bool receivedSyn();
  void sendSynack();
  
  //data transfer
  bool receivedAck();
  void sendData(int packetNum);
};
#endif

