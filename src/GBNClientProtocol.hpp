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
#include "Timer.hpp"


class GBNClientProtocol {
public:

    //client
    GBNClientProtocol(double TOInterval, std::string ip, int port, std::string fname, double lProb, double cProb);
    
    // RECEIVING SIDE (Client)
    double corruptionProbability;
    double lostProbability;
    int currentSeq;
    int expectedSeq;
    int expectedAck;
    int bytesReceived;
    int fileLength; //Given by server during handshake
    
    
    void sendSyn(std::string filename);
    bool receiveSynAck();
    void sendAck(int seqNum, int ackNum);
    
    //Check it's what we're expecting and if so write to file
    //Update bytesReceived
    void receiveData();
    bool badPacketProb(double lostProbability);
    
    void writeTofile(std::string data);
    UDPCommunicator communicator;
    
    Timer timeout;
    double timeoutInterval;
    
private:
    std::string filename;
  
    
    
};


#endif
