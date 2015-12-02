//
//  Timer.hpp
//  rdt
//
//  Created by Chris Orcutt on 11/22/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COTimer
#define COTimer

#include <stdio.h>
#include <sys/time.h>

class Timer {
  timeval startTime;
  
public:
  Timer();
  
  bool timing;
  bool valid;

  void start();
  void stop();
  float elapsedTime();
  
  
};

#endif
