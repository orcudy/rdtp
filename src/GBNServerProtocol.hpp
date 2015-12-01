//
//  GBNServerProtocol.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef GBNServerProtocol_h
#define GBNServerProtocol_h

#include <stdio.h>
#include "UDPCommunicator.hpp"
#include "FileSplitter.hpp"
#include "Timer.hpp"


class GBNServerProtocol{

public:
  UDPCommunicator communicator;

  //timers
  Timer timeoutTimer;
  float timeoutInterval;
  
  //window
  int currentWindowBase;
  int windowSize;
  
  //data
  int chunkSize;
  char ** fileData;
  int totalChunks;
  
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
  bool receivedSyn();
  void sendSynack(int seqNum, int ackNum);

  //data transfer
  bool receivedAck();
  void sendData(int packetNum);
};
#endif

