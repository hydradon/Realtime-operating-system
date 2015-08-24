#include <Arduino.h>

const int T = 100;

int fastLoopTimer = 0;
int slowLoopCounter = 0;

void togglePin6()
{
  static char state=1;
  
  if(state)
    digitalWrite(6, HIGH);
  else
    digitalWrite(6, LOW);
    
  state=!state;
}


void togglePin7()
{
  static char state=1;
  
  if(state)
    digitalWrite(7, HIGH);
  else
    digitalWrite(7, LOW);
    
  state=!state;
}

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

//LED-pin 6 flashes 5 times a sec
void fastLoop()
{
	togglePin6();
}

//LED-pin 7 flashes 1 time a sec
void slowLoop()
{	
	switch(slowLoopCounter) {

		case 0:
			slowLoopCounter++;
			break;

		case 1:
			slowLoopCounter++;
			break;

		case 2:
			slowLoopCounter++;
			break;

		case 3:
			slowLoopCounter++;
			break;

		case 4:
			slowLoopCounter = 0;
			togglePin7();
			break;
	}
}

void loop()
{
	int deltaMiliSeconds = millis() - fastLoopTimer;

	if(deltaMiliSeconds > (T-1)) {
		fastLoopTimer = millis();
		fastLoop();
		slowLoop();
	}
		
}

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