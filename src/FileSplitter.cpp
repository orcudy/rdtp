//
//  FileSplitter.cpp
//  rdt
//
//  Created by Chloe Drazen on 11/14/15.
//  Copyright © 2015 Chloe Drazen. All rights reserved.
//

#include "FileSplitter.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

FileSplitter::FileSplitter(std::string filename, int chunkSize)
{
    this->filename = filename;
    this->chunkSize = chunkSize;
  
  ifstream file(filename.c_str());
  if (file.good()) {
    ifstream in(filename.c_str(), ifstream::ate | ifstream::binary);
    fileSize = in.tellg();
  }
}

char ** FileSplitter::split()
{
    FILE * fileDescriptor;
    size_t retval;
   
    int totalChunks = ceil((double)fileSize/ chunkSize) + 1;
    int currentChunkIndex = 0;
    
    char ** chunks = (char **) malloc(sizeof(char*) * totalChunks);
    memset((void*)chunks, 0, totalChunks);
    
    fileDescriptor = fopen ( filename.c_str() , "r" );
    if (fileDescriptor == NULL)
    {
        fputs ("File error", stderr);
        exit (1);
    }
    
    // obtain file size
    fseek (fileDescriptor , 0 , SEEK_CUR);
    rewind (fileDescriptor);
    
    size_t i;
    for(i = 0; i < fileSize/chunkSize; i++){
        // allocate memory to contain the whole file
        char * chunk = (char*)malloc(sizeof(char) * chunkSize);
        if (chunk == NULL) {
            fputs ("Memory error", stderr);
            exit (2);
        }
        // copy the file into the buffer:
        retval = fread (chunk, 1, chunkSize, fileDescriptor);
        chunks[currentChunkIndex] = chunk;
        currentChunkIndex++;
    }
    
    //get smaller leftovers
    if(i * chunkSize < fileSize)
    {
        char * chunk = (char*) malloc(sizeof(char)*(fileSize - i * chunkSize));
        if (chunk == NULL) {
            fputs ("Memory error", stderr);
            exit (2);
        }
        retval = fread(chunk, 1, chunkSize, fileDescriptor);
        chunks[currentChunkIndex] = chunk;
        currentChunkIndex++;
    }

    fclose (fileDescriptor);
    return chunks;
}