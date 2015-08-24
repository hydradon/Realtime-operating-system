/*
 * lab3part0.cpp
 *
 * Created: 17-Sep-13 04:18:25 PM
 *  Author: Vu Ngoc Quang
 */ 

#include <avr/io.h>
#include <Arduino.h>
#include <stdlib.h>
#include <limits.h>
int fun1(int x, int y)
{
	return x+y;
}
int fun2(int x, int y)
{
	return x*y;
}
void setup()
{
	Serial.begin(9600);
}
// Declare the function pointer
int (*funcptr)(int, int);
void loop()
{
	float turn=(float) rand() / INT_MAX;
	int result;
	if(turn>0.5)
	funcptr=fun1;
	else
	funcptr=fun2;
	// Invoke the function
	result=funcptr(2,3);
	Serial.print("Computation result:");
	Serial.println(result);
}
// Main has been written to work correctly with Arduino. Do not modify.
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