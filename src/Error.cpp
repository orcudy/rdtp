//
//  Error.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include <iostream>

using namespace std;

void Error::clientUsage(){
  cout << "Usage: client -f filename [-i ip] [-p port] [-l packetLossProbability] [-c packetCorruptionProbability] [-t timeout] [-pa] [-pr] [-ps] [-v]" << endl;
  Error::exit(1);
}

void Error::serverUsage(){
  cout << "Usage: server [-p port] [-t timeout] [-w windowSize] [-pa] [-pr] [-ps] [-v]" << endl;
  Error::exit(1);
}

void Error::exit(int status){
  cout << "Exiting." << endl;
  std::exit(status);
}
