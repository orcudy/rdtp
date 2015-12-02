//
//  Communicator.hpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COCommunicator
#define COCommunicator

#include "Socket.hpp"
#include <string>

// abstract base class
class Communicator {
public:
  //constructor
  Socket socket;
  
  //print output/input
  bool printReceieved;
  bool printSent;
  
  //instance properties
  int receiveBufferSize;
  char * receiveBuffer;

  //pure virtual methods
  virtual int send(char * message) = 0;
  virtual char * receive() = 0;
};

#endif
