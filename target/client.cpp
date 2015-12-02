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
    

    double timeoutInterval = 5;
    std::string filename = "";
    double lostProb = 0;
    double corrProb = 0;
    
    int index;
    for (index = 0; index < argc; index++){
        //indicate ip address
        if (strcmp(argv[index], "-i") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            ip = std::string (argv[index + 1]);
        }
        
        //indicate port
        if (strcmp(argv[index], "-p") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            port = atoi(argv[index + 1]);
        }
        
        //indicate timeout interval
        if (strcmp(argv[index], "--timeout") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            timeoutInterval = atoi(argv[index + 1]);
        }
        
        //indicate filename
        if (strcmp(argv[index], "--filename") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            filename = std::string(argv[index + 1]);
        }
        
        //indicate timeout interval
        if (strcmp(argv[index], "--timeout") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            timeoutInterval = atoi(argv[index + 1]);
        }
        
        //indicate loss probability
        if (strcmp(argv[index], "--lProb") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            lostProb = atoi(argv[index + 1]);
        }
        
        //indicate corruption probability
        if (strcmp(argv[index], "--cProb") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            corrProb = atoi(argv[index + 1]);
        }
        
        //print all sent data
        if (strcmp(argv[index], "--print-sent") == 0){
            printSent = true;
        }
        
        //print all received data
        if (strcmp(argv[index], "--print-recv") == 0){
            printReceived = true;
        }
        
        //print all data
        if (strcmp(argv[index], "--print") == 0){
            printSent = true;
            printReceived = true;
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
    
    // !! Begin handshake !!
    client.sendSyn(filename);
    client.timeout.start();
    
    cout << "Creating thread" << endl;
    
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
            client.sendSyn(filename);
            pthread_mutex_lock(&timerLock);
            if (!client.timeout.timing){
                break;
            }
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
    while(client.bytesReceived <= client.fileLength)
    {
        client.receiveData();
    }
    
    
    
    
    return 0;
}

void * receiveSynAck(void * aclient)
{
    GBNClientProtocol * client = (GBNClientProtocol*)aclient;
    while(!client->receiveSynAck());
    pthread_mutex_lock(&timerLock);
    client->timeout.stop();
    pthread_mutex_unlock(&timerLock);
    
    return NULL;
}
