//
//  clientSyn.cpp
//  rdt
//
//  Created by Chloe Drazen on 11/30/15.
//  Copyright (c) 2015 Chris Orcutt. All rights reserved.
//

#include <stdio.h>
#include "UDPCommunicator.hpp"

int main(){
    UDPCommunicator communicator = UDPCommunicator("", 4500);
    communicator.receieveLog = true;
    communicator.sendLog = true;
    while (true){
        communicator.receive();
    }
}