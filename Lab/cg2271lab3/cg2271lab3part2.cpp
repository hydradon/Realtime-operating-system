/*
 * cg2271lab3part2.cpp
 *
 * Created: 14/9/2013 8:18:59 AM
 *  Author: dcstanc
 */ 


#include <avr/io.h>
#include <Arduino.h>
#include "prioq.h"

const int INT0_PRIORITY = 0; //priority of INT0
const int INT1_PRIORITY = 1; //priority of INT1 

TPrioQueue *queue;

// Do switch debouncing
unsigned long int0time=0, int1time=0;

// Debouncing function. Returns TRUE if this interrupt was not caused by a bouncing switch
int debounce(unsigned long *debTimer)
{
	unsigned long tmp=*debTimer;
	unsigned long currTime=millis();
	
	if((currTime-tmp) > 500)
	{
		*debTimer=currTime;
		return 1;
	}	
	else
		return 0;
		
}

// Declares a new type called "funcptr"

typedef void (*funcptr)(void);

funcptr fp;


// Flashes LED at pin 7 5 times a 4 Hz
void int0task()
{
	int ctr=0;
	for(int i=0; i<5; i++)
	{
		digitalWrite(7, HIGH);
		delay(125);
		digitalWrite(7, LOW);
		delay(125);
		Serial.println(ctr);
		ctr++;
	}
}

// Flashes LED at pin 6 5 times at 2HZ
void int1task()
{
	for(int i=0; i<5; i++)
	{
		digitalWrite(6, HIGH);
		delay(250);
		digitalWrite(6, LOW);
		delay(250);
	}
}

void int0ISR()
{
	if (debounce(&int0time)) {
		enq(queue, (void *)int0task, INT0_PRIORITY);
	}
}

void int1ISR()
{
	if(debounce(&int1time)) {
		enq(queue, (void *)int1task, INT1_PRIORITY);
	}
}

void setup()
{
	queue=makeQueue();

	pinMode(7, OUTPUT);
	pinMode(6, OUTPUT);
	
	attachInterrupt(INT0, int0ISR, RISING);
	attachInterrupt(INT1, int1ISR, RISING);

	Serial.begin(9600);
}

// Dequeues and calls functions if the queue is not empty
void loop()
{
	if (qlen(queue) > 0) {
		fp = (funcptr) deq(queue);
		fp();
	}
}

// 
int main(void)
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