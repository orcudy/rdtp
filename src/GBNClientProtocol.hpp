//
//  GBNClientProtocol.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/17/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef CDGBNClientProtocol
#define CDGBNClientProtocol

#include <stdio.h>

#include <string>
#include "UDPCommunicator.hpp"




class GBNClientProtocol {
public:

    //client
    GBNClientProtocol(int windowSize, std::string ip, int port, std::string fname);
    
    // RECEIVING SIDE (Client)
    int corruptionProbability;
    int lostProbability;
    int expectedSeq;
    int expectedAck;
    int bytesReceived;
    int fileLength; //Given by server during handshake
    
    
    void sendSyn(std::string filename);
    void receiveSynAck();
    void sendAck(int seqNum, int ackNum);
    
    //Check it's what we're expecting and if so write to file
    //Update bytesReceived
    void receiveData();
    
    void writeTofile(std::string data);
    UDPCommunicator communicator;
    
    //std::string filename; //temporarily public instead of private

    
private:
    std::string filename;
    double timerWindow;
    int windowSize;
    
    
};


#endif
