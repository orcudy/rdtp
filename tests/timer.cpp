//
//  main.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/22/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <stdio.h>
#include "Timer.hpp"
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
  Timer timer;
  timer.start();
  sleep(1);
  cout << "Expected 1 second elapsed, actual: ";
  cout << timer.elapsedTime() << endl;
  timer.stop();
  
  timer.start();
  sleep(2);
  cout << "Expected 2 second elapsed, actual: ";
  cout << timer.elapsedTime() << endl;
  timer.stop();
  
  cout << "Expected 0 second elapsed, actual: ";
  cout << timer.elapsedTime() << endl;
  

  
}