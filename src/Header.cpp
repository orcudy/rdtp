//
//  header.cpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Header.hpp"
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

Header::Header(){
  syn = false;
  synack = false;
  ack = -1;
  seq = -1;
  dataLength = -1;
  memset(this->data, Header::dataSize, '\0');
}

Header::Header(char * data){
  memcpy(this, data, sizeof(char) * sizeof(Header));
}

void Header::setData(std::string data){
  memset(this->data, 0, this->dataSize);
  memcpy(this->data, data.c_str(), this->dataSize);
}

char * Header::generateMessage(){
  char * msg = (char*)malloc(sizeof(char) * sizeof(Header));
  memcpy(msg, this, sizeof(char) * sizeof(Header));
  return msg;
}

void Header::sendSyn(int seq, std::string filename){
  
}

void Header::sendSynack(int seq, int ack, int dataLength){
  
}

