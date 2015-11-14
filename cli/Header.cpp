//
//  header.cpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "header.hpp"


Header::Header(){
  syn = false;
  synack = false;
  ack = -1;
  seq = -1;
  dataLength = -1;
  memset(this->data, Header::dataSize, '\0');
}