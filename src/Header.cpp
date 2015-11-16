//
//  header.cpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Header.hpp"
#include "Parser.hpp"
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
  vector<string> tokens = Parser::parse(string (data), "???");
  
  for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++){
    cout << *it << endl;
  }
  (tokens[0] == "1") ? (this->syn = true) : (this->syn = false);
  (tokens[1] == "1") ? (this->synack = true) : (this->synack = false);
  ack = atoi(tokens[2].c_str());
  seq = atoi(tokens[3].c_str());
  dataLength = atoi(tokens[4].c_str());
  strncpy(this->data, tokens[5].c_str(), dataSize);
}

char * Header::generateMessage(){
  string message;
  (syn) ? message.append("1") : message.append("0");
  message.append(delimiter);
  (synack) ? message.append("1") : message.append("0");
  message.append(delimiter);
  message.append(std::to_string(ack));
  message.append(delimiter);
  message.append(std::to_string(seq));
  message.append(delimiter);
  message.append(std::to_string(dataLength));
  message.append(delimiter);
  int messageLength = (int)message.length();
  
  char * msg = (char*)malloc(sizeof(char) * messageLength * dataSize);
  strncpy(msg, message.c_str(), messageLength);
  strncpy(&msg[messageLength], data, dataSize);
  return msg;
}

void Header::setData(string data){
  strncpy(this->data, data.c_str(), dataSize);
}