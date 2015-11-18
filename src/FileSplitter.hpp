//
//  FileSplitter.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/14/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COFileSplitter
#define COFileSplitter

#include <stdio.h>
#include <string>

class FileSplitter {
    std::string filename;
    int chunkSize;
  
public:
    FileSplitter(std::string filename, int chunkSize);
    char ** split();
    size_t fileSize;
};

#endif
