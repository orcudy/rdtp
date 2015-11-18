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
#include "FileSplitter.hpp"

struct PacketState {
  bool ack;
  bool sent;
};

class GBNServerProtocol{
  GBNServerProtocol(int windowSize, int port);
  
  
  
  // SENDING SIDE (Server)
  //  timer
  int windowSize;
  int windowBase;
  PacketState * window;
  FileSplitter fs;
};
#endif
