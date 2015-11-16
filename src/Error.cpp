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

void Error::usage(){
  cout << "Usage: client [-i <ip>] [-p <port>]" << endl;
  cout << "       server [-p <port>]" << endl;

  Error::exit(1);
}


void Error::exit(int status){
  cout << "Exiting." << endl;
  std::exit(status);
}
