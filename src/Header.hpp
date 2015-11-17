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
  bool syn;
  bool synack;
  int ack;
  int seq;
  int dataLength;
  const static int dataSize = 1000;
  std::string filename;
  
public:
  //constructors
  Header();
  Header(char * data);
  
  //instance properties (& getters/setters)
  char data[1000];
  void setData(std::string data);
  
  //instance methods
  char * generateMessage();
  void sendSyn(int seq, std::string filename);
  void sendSynack(int seq, int ack, int dataLength);
};

#endif
