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


struct PacketState {
  bool ack;
  bool sent;
};

class GBNServerProtocol{

public:
  //timers
  Timer synackTimer;
  Timer ackTimer;
  float timeoutInterval;
  
  //window
  int windowSize;
  int windowBase;
  PacketState * stateWindow;
  char ** fileData;
  
  //data
  int chunkSize;
  int expectedSeqNum;
  int expectedAckNum;
  int receivedSeqNum;
  int receivedAckNum;
  
  //file splitting
  FileSplitter fileSplitter;
  
  //constructors
  GBNServerProtocol(int windowSize, double timeoutInterval, int port);
  
  // 3-way handshake
  bool receivedSyn();
  void sendSynack(int seqNum, int ackNum);

  
  //data transfer
  bool receivedAck();
  void sendData();
  
  UDPCommunicator communicator;


};
#endif

