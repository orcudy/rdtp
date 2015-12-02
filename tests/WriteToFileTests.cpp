//
//  WriteToFileTests.cpp
//  rdt
//
//  Created by Chloe Drazen on 12/1/15.
//  Copyright (c) 2015 Chris Orcutt. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


void writeTofile(std::string data)
{
    ofstream outputFile;
    
    //outputFile.open(filename, ios::app);
    outputFile.open("/Users/chloedrazen/Desktop/chrisisapoop2.txt", ios::app | ios::out);
    outputFile << data;
    outputFile.close();
}

int main()
{
    writeTofile("blah 1\n");
    writeTofile("blah 2\n");
    writeTofile("blah 3\n");
    writeTofile("blah 4\n");
    writeTofile("blah 5\n");
}