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
#include "UDPCommunicator.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FileSplitter.hpp"

using namespace std;

int main(int argc, const char ** argv){
  
  // !! begin command line argument parsing !!
  if (argc > 5){
    Error::usage();
  }
  
  std::string ip = "127.0.0.1";
  int port = 4500;
  
  int index;
  for (index = 0; index < argc; index++){
    if (strcmp(argv[index], "-i") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      ip = std::string (argv[index + 1]);
    }
    
    if (strcmp(argv[index], "-p") == 0){
      if (index + 1 == argc) {
        Error::usage();
      }
      port = atoi(argv[index + 1]);
    }
  }
  // !! end command line argument parsing !!
//
//  Header header = Header();
//  header.setData("Franzen trust fund thundercats single-origin coffee, next level scenester ethical farm-to-table photo booth ugh pug cold-pressed. Offal irony master cleanse direct trade, swag meggings hashtag shoreditch. Swag organic dreamcatcher lo-fi. Heirloom actually retro austin four loko 3 wolf moon. Chicharrones four loko yuccie distillery hoodie authentic. Fixie biodiesel thundercats, wolf fap knausgaard bespoke. Quinoa retro tilde keffiyeh letterpress, selvage banh mi farm-to-table franzen. Organic irony squid pitchfork, meggings artisan shabby chic retro microdosing craft beer typewriter twee. VHS jean shorts tacos +1, kogi pitchfork synth. Locavore intelligentsia chambray, meggings marfa distillery yr letterpress mixtape. Photo booth put a bird on it normcore listicle, mixtape kogi selvage leggings. Fap dreamcatcher ramps, jean shorts put a bird on it schlitz wayfarers helvetica heirloom tacos beard four dollar toast yr.");
//  
//  UDPCommunicator client = UDPCommunicator(ip, port);
//  client.send(header.generateMessage());
    
    FileSplitter fs = FileSplitter("/Users/chloedrazen/testfile.txt", 1000);
    char ** array = fs.split();

    

  return 0;
}
