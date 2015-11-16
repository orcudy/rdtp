//
//  header.hpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COHeader
#define COHeader

#include <stdio.h>
#include <string>

const std::string delimiter = "?";

class Header {
  const static int dataSize = 1000;
  
  std::string filename;
  bool syn;
  bool synack;
  int ack;
  int seq;
  int dataLength;
  char data[1000];
  
public:
  Header();
  Header(char * data);
  
  char * generateMessage();
  void setData(std::string data);

  
//  int sendSyn(int seq, std::string filename);
//  int sendSynack(int seq, int ack, int dataLength);
  
  
};

#endif
