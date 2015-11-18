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


class GBNClientProtocol {
  //client
  GBNClientProtocol(int windowSize, char * ip, int port);
  
  // RECEIVING SIDE (Client)
  int corruptionProbability;
  int lostProbability;
  int expectedSeq;
  int bytesReceived;
};


#endif
