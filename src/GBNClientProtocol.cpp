//
//  GBNClientProtocol.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "GBNClientProtocol.hpp"
#include "Header.hpp"

#include "UDPCommunicator.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


GBNClientProtocol::GBNClientProtocol(int windowSize, string ip, int port, string fname)
{
    communicator = UDPCommunicator(ip, port);
    this->windowSize = windowSize;
    //Double check this:
    expectedAck = 0;
    expectedSeq = 0;
    filename = fname;
}

void GBNClientProtocol::sendSyn(std::string filename)
{
    Header header = Header();
    header.syn = true;
    header.seqNum = 0; //for now
    strncpy(header.filename, filename.c_str(), filename.length());
    //filename = header.filename; //wrong?
    
    communicator.send(header.generateMessage());
    
}

void GBNClientProtocol::sendAck(int seqNum, int ackNum){
    Header header = Header();
    header.ackNum = ackNum;
    header.seqNum = seqNum;
    
    communicator.send(header.generateMessage());
}

void GBNClientProtocol::receiveSynAck()
{
    char* message = communicator.receive();
    Header * header = ((Header *) message);
    
    fileLength = header->fileSize; //Check this?!
    

    sendAck(0, 0);
    
    
}

//Check it's what we're expecting and if so write to file
//Update bytesReceived
void GBNClientProtocol::receiveData()
{
    char* message = communicator.receive();
    Header * header = ((Header *) message);
    
    if(header->ackNum == expectedAck)
    {
        writeTofile(header->data);
        expectedAck++;
        bytesReceived += header->dataSize;
        
        //Not totally sure how to update expectedSeq...
        expectedSeq++;
    }
    
    //Check if end of file:
    if(bytesReceived >= fileLength)
    {
        //Begin closing connection
    }

    
}

void GBNClientProtocol::writeTofile(std::string data)
{
    ofstream outputFile;
    outputFile.open(filename, ios::app);
    outputFile << data;
    
}
