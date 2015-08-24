/*
 * lab4part3.cpp
 *
 * Created: 4/10/2013 6:19:58 PM
 *  Author: dcstanc
 */ 


#include <avr/io.h>
#include <Arduino.h>
#include "kernel.h"
#include "sema.h"

// Do switch debouncing
unsigned long int0time=0, int1time=0;

// Debouncing function. Returns TRUE if this interrupt was not caused by a bouncing switch
int debounce(unsigned long *debTimer)
{
	unsigned long tmp=*debTimer;
	unsigned long currTime=OSticks();
	
	if((currTime-tmp) > 500)
	{
		*debTimer=currTime;
		return 1;
	}
	else
	return 0;
	
}


void setup()
{
}

void loop()
{
	// Empty
}

// Do not modify
int main()
{
	init();
	setup();
	
	while(1)
	{
		loop();
		
		if(serialEventRun)
		serialEventRun();
	}
}