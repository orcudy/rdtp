//
//  Error.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 orcudy. All rights reserved.
//

#include "Error.hpp"
#include <iostream>
#include <vector>

using namespace std;

void Error::exit(int status){
  cout << "Exiting." << endl;
  std::exit(status);
}
