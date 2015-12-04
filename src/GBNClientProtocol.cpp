//
//  GBNClientProtocol.cpp
//  rdt
//
//  Created by Chloe Drazen on 11/14/15.
//  Copyright © 2015 Chloe Drazen. All rights reserved.
//

#include "GBNClientProtocol.hpp"
#include "Header.hpp"

#include "UDPCommunicator.hpp"
#include <string.h>
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
  totalPackets = -1;
}

void GBNClientProtocol::sendSyn(std::string filename)
{
  Header header = Header();
  header.syn = true;
  strncpy(header.filename, filename.c_str(), filename.length());
  communicator.send(header.generateMessage());
}

void GBNClientProtocol::sendFin()
{
  Header header = Header();
  header.fin = true;
  communicator.send(header.generateMessage());
}

bool GBNClientProtocol::receiveFin(){
  char* message = communicator.receive();
  Header * header = ((Header *) message);
  if(header->fin){
    return true;
  }
  return false;
}

void GBNClientProtocol::sendAck(int seqNum, int ackNum){
  Header header = Header();
  header.ackNum = ackNum;
  header.seqNum = seqNum;
  if (verbose){
    cout << "Sent: Ack (Sequence: " << seqNum << ", Ack: " << ackNum << ")" << endl;
  }
  communicator.send(header.generateMessage());
}

bool GBNClientProtocol::receiveSynAck()
{
  char* message = communicator.receive();
  Header * header = ((Header *) message);
  
  if(!header->synack)
    return false;
  
  totalPackets = header->totalPackets;
  
  return true;
  
}

//Check it's what we're expecting and if so write to file
//Update bytesReceived
void GBNClientProtocol::receiveData()
{
  char* message = communicator.receive();
  Header * header = ((Header *) message);
  
  if (badPacketProb(lostProbability)){
    if (verbose){
      cout << "Received: Packet lost!" << endl;
    }
    return;
  } else {
    if (badPacketProb(corruptionProbability)){
      if (verbose){
        cout << "Received: Packet corrupted!" << endl;
      }
    } else {
      if (header->seqNum == expectedSeq){
        writeTofile(header->data);
        expectedSeq++;
        bytesReceived += header->dataSize;
        if (verbose){
          cout << "Received: Expected packet. (Sequence number " << expectedSeq - 1 << ")" << endl;
        }
      }
    }
    if (verbose){
      cout << "Received: Out of order packet. (Expected: " << expectedSeq << ", Received: " << header->seqNum << ")" << endl;
    }
    sendAck(currentSeq, expectedSeq);
  }
}

void GBNClientProtocol::writeTofile(std::string data)
{
  ofstream outputFile;
  
  //outputFile.open(filename, ios::app);
  //outputFile.open("/Users/orcudy/Desktop/received.txt", ios::app | ios::out);
  outputFile.open("/home/cs118/Desktop/received.txt", ios::app | ios::out);
  outputFile << data;
  outputFile.close();
}

//Returns true is packet is lost, false otherwise
bool GBNClientProtocol::badPacketProb(double lostProbability)
{
  int test = rand() % 100 + 1;
  if(test <= lostProbability * 100){
    return true;
  }
  return false;
}
