//
//  header.hpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 chrisorcutt. All rights reserved.
//

#ifndef COHeader
#define COHeader

#include <stdio.h>
#include <string>

class Header {
  const static int dataSize = 1000;
  
  std::string filename;
  bool syn;
  bool synack;
  int ack;
  int seq;
  int dataLength;
  char data[1000];
  
  //constructor
  Header();
  
};

#endif
