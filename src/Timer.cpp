//
//  Timer.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/22/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include <sys/time.h>
#include <stdlib.h>
#include "Timer.hpp"


Timer::Timer(){
  valid = true;
}

void Timer::start(){
  timing = true;
  gettimeofday(&startTime, NULL);
}

void Timer::stop(){
  timing = false;
}

float Timer::elapsedTime(){
  if (timing){
    timeval now;
    gettimeofday(&now, NULL);
    time_t millisecondsElapsed = (now.tv_sec - startTime.tv_sec) * 1000.0;
    millisecondsElapsed += (now.tv_usec - startTime.tv_usec) / 1000;
    return millisecondsElapsed / 1000.0;
  }
  return 0;
}