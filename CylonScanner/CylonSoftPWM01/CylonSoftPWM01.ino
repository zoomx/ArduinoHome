//CylonSoftPWM01
//http://blog.jabawoki.com/2012/02/07/cylon-brake-light-development/
//https://code.google.com/p/rogue-code/wiki/SoftPWMLibraryDocumentation
// changes from 3 to 4 and one 4 to 5
#include "SoftPWM.h"

#define FirstLed 4
#define LastLed 11
#define FirstLedPlusOne 5
#define LastLedMinusOne 10

int timeron = 50;
int timeroff = 50;
int fadeUp = 100;
int fadeDown = 500;

void setup()
{
  Serial.begin(9600);
  Serial.println("CylonSoftPWM01");
  // Initialize
  SoftPWMBegin();
  // Create and set pins to 0 (off) and set timers
  for (int thisPin = FirstLed; thisPin <=LastLed; thisPin++) {
    SoftPWMSet(thisPin, 0);
    SoftPWMSetFadeTime(thisPin, fadeUp, fadeDown);
  }
}

void loop() {
  // Light all diodes for 0.2 seconds  
  if  (millis() <= 200) {
    for (int thisPin = 4; thisPin <= 11; thisPin++) { 
      SoftPWMSetPercent(thisPin, 100);
    }
  } 
  else {

    // loop from right to left:
    for (int thisPin = FirstLed; thisPin <= LastLedMinusOne; thisPin++) { 
      SoftPWMSetPercent(thisPin, 100);
      delay(timeron);
      SoftPWMSetPercent(thisPin, 0);
      delay(timeroff); 
    }

    // loop from left to right:
    for (int thisPin = LastLed; thisPin >= FirstLedPlusOne; thisPin--) { 
      SoftPWMSetPercent(thisPin, 100);
      delay(timeron);
      SoftPWMSetPercent(thisPin, 0);
      delay(timeroff);     
    }
  }
}



