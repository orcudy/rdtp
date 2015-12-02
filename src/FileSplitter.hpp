//
//  FileSplitter.hpp
//  rdt
//
//  Created by Chloe Drazen on 11/14/15.
//  Copyright © 2015 Chloe Drazen. All rights reserved.
//

#ifndef CDFileSplitter
#define CDFileSplitter

#include <stdio.h>
#include <string>

class FileSplitter {
  std::string filename;
  int chunkSize;
  
public:
  FileSplitter(std::string filename, int chunkSize);
  FileSplitter(){};
  char ** split();
  size_t fileSize;
};

#endif
