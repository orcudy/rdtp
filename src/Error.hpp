//
//  Error.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COError
#define COError

class Error{
public:
  static void usage();
  static void exit(int status);
};

#endif
