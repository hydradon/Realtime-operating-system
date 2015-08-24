//
//  timing.c
//  memmang
//
//  Created by Colin Tan on 25/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#include <stdio.h>
#include <time.h>

clock_t _begin=0, _end=0;
unsigned long _timeSpent;

void startClock()
{
    _begin=clock();
}

unsigned long endClock()
{
    _end=clock();
    _timeSpent=_end-_begin;
    return _timeSpent;
}

unsigned long getLastTimeSpent()
{
    return _timeSpent;
}