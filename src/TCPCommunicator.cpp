//
//  TCPCommunicator.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/13/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//


#include "Error.hpp"
#include "Socket.hpp"
#include "TCPCommunicator.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>

using namespace std;

TCPCommunicator::TCPCommunicator(string ip, int port){
  this->socket = Socket(ip, port, TCP);
  this->concurrentConnections = 5;
}

char * TCPCommunicator::receive(){
  char * message = (char*)malloc(sizeof(char) * 1000);
  strcpy(message, "TCPCommunicator::recieve() default return");
  return message;
}

int TCPCommunicator::send(char * message){
  char c_message[100] = "Do you want to build a snowman?";
  return (int)write(this->socket.descriptor, &c_message, 100);
}


void TCPCommunicator::startListening(){
  cout << "Listening on port " << std::to_string(this->socket.port) << endl;
  int retval = listen(this->socket.descriptor, this->concurrentConnections);
  if (retval == -1) {
    cout << "Error listening on port " << this->socket.port << " with " << this->concurrentConnections << " concurrent connections: " <<  strerror(errno) << endl;
    Error::exit(4);
  }
  
  this->listening = true;
  while (this->listening) {
    TCPCommunicator *client = acceptConnection();

    if (fork() == 0){
      cout << "Process " << getpid() << " created" << endl;
      close(this->socket.descriptor);
      
      char buffer[1000];
      read(client->socket.descriptor, buffer, 1000);
      
      cout << string(buffer) << endl;
      close(client->socket.descriptor);
      exit(0);
    }
    close(client->socket.descriptor);
    int status;
    wait(&status);
  }
  
  close(this->socket.descriptor);
}

void TCPCommunicator::stopListening() {
  this->listening = false;
  return;
}

TCPCommunicator* TCPCommunicator::acceptConnection(){
  TCPCommunicator *client = (TCPCommunicator *)malloc(sizeof(TCPCommunicator));
  
  struct sockaddr * clientsockaddr = NULL;
  socklen_t addrlen = sizeof(clientsockaddr);
  client->socket.descriptor = accept(this->socket.descriptor, clientsockaddr, &addrlen);
  cout << "Accepting connection from socket " << client->socket.descriptor <<  endl;
  if (client->socket.descriptor == -1) {
    cout << "Error accepting connection on port " << this->socket.descriptor << ": " <<  strerror(errno) << endl;
    cout << "Exiting." << endl;
    exit(7);
  }
  
  return client;
}












