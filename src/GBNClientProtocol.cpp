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


GBNClientProtocol::GBNClientProtocol(double TOInterval, string ip, int port, string fname, double lProb, double cProb)
{
    communicator = UDPCommunicator(ip, port);
    //Double check this:
    expectedAck = 0;
    lostProbability = lProb;
    corruptionProbability = cProb;
    currentSeq = 0;
    filename = fname;
    timeoutInterval = TOInterval;
    expectedSeq = 0;
}

void GBNClientProtocol::sendSyn(std::string filename)
{
    Header header = Header();
    header.syn = true;
    header.seqNum = currentSeq; 
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

bool GBNClientProtocol::receiveSynAck()
{
    char* message = communicator.receive();
    Header * header = ((Header *) message);
    
    if(!header->synack)
        return false;
    
    fileLength = header->fileSize; //Check this?!
    
    return true;
    
}

//Check it's what we're expecting and if so write to file
//Update bytesReceived
void GBNClientProtocol::receiveData()
{
    char* message = communicator.receive();
    Header * header = ((Header *) message);
    
    if(header->seqNum == expectedSeq && !badPacketProb(lostProbability) && !badPacketProb(corruptionProbability))
    {
        writeTofile(header->data);
        expectedSeq++;
        bytesReceived += header->dataSize;

    }
    
    sendAck(currentSeq, expectedSeq);
    
}

void GBNClientProtocol::writeTofile(std::string data)
{
    ofstream outputFile;
    
    cout << "printing the data: "<< data << endl << endl;
    
    //outputFile.open(filename, ios::app);
    outputFile.open("/Users/chloedrazen/Desktop/chrisisapoop.txt", ios::app | ios::out);
    outputFile << data;
    outputFile.close();
}

//Returns true is packet is lost, false otherwise
bool GBNClientProtocol::badPacketProb(double lostProbability)
{
    int test = rand() % 100 + 1;
    
    if(test <= lostProbability*100)
        return true;
    return false;
}
