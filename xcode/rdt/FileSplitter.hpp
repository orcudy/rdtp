//
//  FileSplitter.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef FileSplitter_hpp
#define FileSplitter_hpp

#include <stdio.h>
#include <string>

class FileSplitter {
  std::string filename;
  int chunkSize;
  
public:
  FileSplitter(std::string filename);
  char ** split();
};

#endif /* FileSplitter_hpp */
