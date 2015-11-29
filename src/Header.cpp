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
  ackNum = -1;
  seqNum = -1;
  dataSize = -1;
  fileSize = -1;
  memset(this->data, '\0', this->chunkSize);
  memset(this->filename, '\0', maxFilenameSize);

}

Header::Header(char * data){
  memcpy(this, data, sizeof(char) * sizeof(Header));
}

void Header::setData(char * data) {
  memset(this->data, '\0', this->chunkSize);
  memcpy(this->data, data, this->chunkSize);
}

char * Header::generateMessage(){
  char * msg = (char*)malloc(sizeof(char) * sizeof(Header));
  memcpy(msg, this, sizeof(char) * sizeof(Header));
  return msg;
}

void Header::description(){
  cout << "syn: " << syn << endl;
  cout << "synack: " << synack << endl;
  cout << "ackNum: " << ackNum << endl;
  cout << "seqNum: " << seqNum << endl;
  cout << "dataSize: " << dataSize << endl;
  cout << "chunkSize: " << chunkSize << endl;
  printf("filename: %s\n", filename);
  cout << "fileSize: " << fileSize << endl;
  printf("data: %s\n", data);
}

