//
//  GBNClientProtocol.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef CDGBNClientProtocol
#define CDGBNClientProtocol

#include <stdio.h>
#include "UDPCommunicator.hpp"


class GBNClientProtocol {
public:
  //client
  GBNClientProtocol(int windowSize, std::string ip, int port);
  
  int corruptionProbability;
  int lostProbability;
  int expectedSeq;
  int bytesReceived;
  
  int windowSize;
  
  void sendSyn();
  void sendAck(int ackNum, int seqNum);
  
  UDPCommunicator communicator; 
};


#endif
