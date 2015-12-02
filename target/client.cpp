//
//  client.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//


#include "Error.hpp"
#include "Header.hpp"
#include "Socket.hpp"
#include "GBNClientProtocol.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FileSplitter.hpp"
#include <pthread.h>

using namespace std;

pthread_mutex_t timerLock;

void * receiveSynAck(void * aclient);


int main(int argc, const char ** argv){
  
  
  // !! begin command line argument parsing !!
  if (argc > 17){
    Error::usage();
  }
  
  std::string ip = "127.0.0.1";
  int port = 45000;
  bool printSent = false;
  bool printReceived = false;
  bool verbose = false;
  
  double timeoutInterval = 2;
  std::string filename = "";
  double lostProb = 0;
  double corrProb = 0;
  
  int index;
  for (index = 0; index < argc; index++){
    //indicate ip address
    if (strcmp(argv[index], "--ip-address") == 0 || strcmp(argv[index], "-i") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      ip = std::string (argv[index + 1]);
    }
    
    //indicate port number
    if (strcmp(argv[index], "--port") == 0 || strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
    }
    
    //indicate filename
    if (strcmp(argv[index], "--filename") == 0 || strcmp(argv[index], "-f") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      filename = std::string(argv[index + 1]);
    }
    
    //indicate probability of packet loss
    if (strcmp(argv[index], "--lost") == 0 || strcmp(argv[index], "-l") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      lostProb = atoi(argv[index + 1]);
    }
    
    //indicate probability of packet being corrupted
    if (strcmp(argv[index], "--corrupt") == 0 || strcmp(argv[index], "-c") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      corrProb = atoi(argv[index + 1]);
    }
    
    //indicate timeout interval
    if (strcmp(argv[index], "--timeout") == 0 || strcmp(argv[index], "-t") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      timeoutInterval = atoi(argv[index + 1]);
    }
    
    //print all sent data
    if (strcmp(argv[index], "--print-sent") == 0 || strcmp(argv[index], "-ps") == 0){
      printSent = true;
    }
    
    //print all received data
    if (strcmp(argv[index], "--print-recv") == 0 || strcmp(argv[index], "-pr") == 0){
      printReceived = true;
    }
    
    //print all data
    if (strcmp(argv[index], "--print-all") == 0 || strcmp(argv[index], "-pa") == 0){
      printReceived = true;
      printSent = true;
    }
    
    //print server protocol
    if (strcmp(argv[index], "--verbose") == 0 || strcmp(argv[index], "-v") == 0){
      verbose = true;
    }
  }
  // !! end command line argument parsing !!
  
  if(filename == "")
  {
    Error::usage();
    Error::exit(-1);
  }
  
  GBNClientProtocol client = GBNClientProtocol(timeoutInterval, ip, port, filename, lostProb, corrProb);
  client.communicator.receieveLog = printReceived;
  client.communicator.sendLog = printSent;
  client.verbose = verbose;
  
  // !! Begin handshake !!
  if (verbose){
    cout << "Sending syn for file " << filename << endl;
  }
  client.sendSyn(filename);
  client.timeout.start();
  
  //wait for synack
  pthread_t receiveThread;
  if(pthread_create(&receiveThread, NULL, receiveSynAck, &client))
  {
    cout<< "Error creating thread" << endl;
    exit(1);
  }
  
  while(client.timeout.timing)
  {
    if(client.timeout.elapsedTime() >= client.timeoutInterval)
    {
      pthread_mutex_lock(&timerLock);
      if (!client.timeout.timing){
        if (client.verbose){
          cout << "Breaking out of timeout loop." << endl;
        }
        break;
      }
      if (client.verbose){
        cout << "Timed out! Resending syn." << endl;
      }
      client.sendSyn(filename);
      client.timeout.start();
      pthread_mutex_unlock(&timerLock);
    }
  }
  
  //join thread when synack received
  if(pthread_join(receiveThread, NULL))
  {
    cout<< "Error joining thread" << endl;
    exit(1);
  }
  
  // !! Begin Data Receipt !!
  while(client.bytesReceived < client.fileLength)
  {
    client.receiveData();
    if (client.verbose){
      cout << "Received data . Bytes received: " << client.bytesReceived << " of " << client.fileLength << endl;
    }
  }
  
  return 0;
}

void * receiveSynAck(void * aclient)
{
  GBNClientProtocol * client = (GBNClientProtocol*)aclient;
  while(!client->receiveSynAck());
  if (client->verbose){
    cout << "Received synack." << endl;
  }
  pthread_mutex_lock(&timerLock);
  client->timeout.stop();
  pthread_mutex_unlock(&timerLock);
  
  return NULL;
}
