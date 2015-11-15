//
//  Error.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COError
#define COError

#include <unordered_map>

class Error{
public:
  static void exit(int status);
};

#endif
