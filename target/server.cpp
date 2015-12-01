//
//  server.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include "GBNServerProtocol.hpp"
#include "Header.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

using namespace std;

void * receiveAck(void *);
void sendValidPackets(GBNServerProtocol *);
void sendSynack(GBNServerProtocol *);

int main(int argc, const char ** argv){
    
    // !! begin command line argument parsing !!
    if (argc > 10){
        Error::usage();
    }
    
    int port = 4500;
    bool verbose = false;
    bool printSent = false;
    bool printReceived = false;
    int windowSize = 10;
    int timeoutInterval = 1;
    for (int index = 0; index < argc; index++){
        //indicate port number
        if (strcmp(argv[index], "-p") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            port = atoi(argv[index + 1]);
        }
        
        //indicate window size
        if (strcmp(argv[index], "--window") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            windowSize = atoi(argv[index + 1]);
        }
        
        //indicate timeout interval
        if (strcmp(argv[index], "--timeout") == 0){
            if (index + 1 == argc) {
                Error::usage();
            }
            timeoutInterval = atoi(argv[index + 1]);
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
        if (strcmp(argv[index], "--verbose") == 0){
            verbose = true;
            printSent = true;
            printReceived = true;
        }
    }
    // !! end command line argument parsing !!
        
    GBNServerProtocol server = GBNServerProtocol(windowSize, timeoutInterval, port);
    server.communicator.receieveLog = printReceived;
    server.communicator.sendLog = printSent;
    server.verbose = verbose;
    
    // !! Begin Handshake !!
    
    //waiting for client to request connection
    while (!server.receivedSyn());
    
    sendSynack(&server);
    
    //wait for synack ack
    pthread_t receiveThread;
    if (pthread_create(&receiveThread, NULL, receiveAck, &server)) {
        cout << "Error creating thread" << endl;
        exit(1);
    }
    
    //resend synack at timeout
    while (server.timeoutTimer.timing){
        if (server.timeoutTimer.elapsedTime() >= server.timeoutInterval){
            sendSynack(&server);
        }
    }
    
    //join thread when ack received
    if (pthread_join(receiveThread, NULL)) {
        cout << "Error joining thread" << endl;
        exit(1);
    }
    
    // !! Begin Data Transmission !!
    
    while (server.currentWindowBase < server.totalChunks){
        sendValidPackets(&server);
        
        //wait for ack
        if (pthread_create(&receiveThread, NULL, receiveAck, &server)) {
            cout << "Error creating thread" << endl;
            exit(1);
        }
        
        //resend data at timeout
        while (server.timeoutTimer.timing){
            if (server.timeoutTimer.elapsedTime() >= server.timeoutInterval){
                if (server.verbose){
                    cout << "Timed out! Resending packets " << server.currentWindowBase << " to " << server.currentWindowBase + server.windowSize << endl;
                }
                sendValidPackets(&server);
            }
        }
        
        //join thread when ack received
        if (pthread_join(receiveThread, NULL)) {
            cout << "Error joining thread" << endl;
            exit(1);
        }
    }
    
    return 0;
}

//receives ack in new thread
void * receiveAck(void * aserver){
    GBNServerProtocol * server = (GBNServerProtocol*)aserver;
    if (server->verbose){
        cout << "Receiving ack " << server->receivedAckNum << " with current window base at " << server->currentWindowBase << endl;
    }
    while(!server->receivedAck());
    server->currentWindowBase = server->receivedAckNum;
    server->timeoutTimer.stop();
    return NULL;
}

//sends all packets in current window
void sendValidPackets(GBNServerProtocol * server){
    for (int packetNum = server->currentWindowBase; packetNum < server->windowSize; packetNum++){
        if (packetNum < server->totalChunks){
            if (server->verbose){
                cout << "Sending packet number " << packetNum + 1 << " of " << server->totalChunks << endl;
            }
            server->sendData(packetNum);
            server->timeoutTimer.start();
        }
    }
}

//sends synack
void sendSynack(GBNServerProtocol * server){
    if (server->verbose){
        cout << "Sending synack with current sequence number " << server->currentSequenceNum << " and expected ack number " << server->expectedAckNum << endl;
    }
    server->sendSynack(server->currentSequenceNum, server->expectedAckNum);
    server->timeoutTimer.start();
}


