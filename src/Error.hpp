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
  //class methods
  static void clientUsage();
  static void serverUsage();
  static void exit(int status);
};

#endif
