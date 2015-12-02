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

class Header {
public:
  bool syn;
  bool synack;
  bool fin;
  int ackNum;
  int seqNum;
  int dataSize;
  const static int chunkSize = 100;

  const static int maxFilenameSize = 200;
  char filename[maxFilenameSize];
  int fileSize;
  
  //constructors
  Header();
  Header(char * data);
  
  //instance properties (& getters/setters)
  char data[1000];
  void setData(char * data);
  
  //instance methods
  char * generateMessage();
  void description();

};

#endif
