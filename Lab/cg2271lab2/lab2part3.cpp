/*
* Lab2Part3.cpp
*
* Created: 28/8/2013 2:39:27 PM
* Author: Vu Ngoc Quang
*		  Prachi Singhal
*/
#include <avr/io.h>
#include <Arduino.h>
#define polledPin 2
#define analogOut 6
#define analogChannel 0

#define FROM_MAX_TOUCH 1002.0 //max value obtained from touch sensor
#define FROM_MIN_TOUCH 0.0 //min value obtained from touch sensor
#define TO_MAX_TOUCH 500 //max remapped value of touch sensor
#define TO_MIN_TOUCH 125 //min remapped value of touch sensor

#define FROM_MAX_PTM 1023.0 //max value obtained from potentiometer
#define FROM_MIN_PTM 0.0 //min value obtained from potentiometer
#define TO_MAX_PTM 255.0 //max remapped value of potentiometer
#define TO_MIN_PTM 0.0 //min remapped value of potentiometer

#define INPUT1BUTTON 0 //connected to pin 2, first push button
#define	INPUT2BUTTON 1 //connected to pin 3, second push button

int val = 0.0;
int analogVal = 0.0;
int touch = 0.0;
int analogTouch = 0.0;

int remap(int val)
{
	return map(val, FROM_MIN_PTM, FROM_MAX_PTM, TO_MIN_PTM, TO_MAX_PTM);
}

int remapTouch(int val)
{
	return map(val, FROM_MIN_TOUCH, FROM_MAX_TOUCH, TO_MIN_TOUCH, TO_MAX_TOUCH);
}

void potentiometerISR()
{
	val = analogRead(0);
	analogVal = remap(val);
}

void touchSensorISR()
{
	touch=analogRead(1);
	analogTouch = remapTouch(touch);
}

void setup()
{
	pinMode(7, OUTPUT);
	
	attachInterrupt(INPUT1BUTTON, potentiometerISR, FALLING);
	attachInterrupt(INPUT2BUTTON, touchSensorISR, FALLING);
	
	Serial.begin(9600);
}

void flashPin7(int delayVal)
{
	digitalWrite(7, HIGH);
	delay(delayVal);
	digitalWrite(7, LOW);
	delay(delayVal);
}

void loop()
{
	analogWrite(analogOut, analogVal);
	flashPin7(analogTouch);
}

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
	return 0;
}