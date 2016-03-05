//CylonScanner05
//http://outflux.net/projects/arduino/larson-scanner/LarsonScanner.pde
//http://www.outflux.net/blog/archives/2009/10/07/larson-scanner-on-arduino/
//Doesn't work because light_visible is not declared!!!
/*
larson-arduino.c
 The Larson Scanner for the Arduino
 v1.0
 
 Written by Windell Oskay, http://www.evilmadscientist.com/
 Modified by Kees Cook to run on ATmega for Arduino/DorkBoard http://dorkbotpdx.org/wiki/dorkboard
 
 Copyright 2009 Windell H. Oskay
 Copyright 2009 Kees Cook <kees@outflux.net>
 Distributed under the terms of the GNU General Public License, please see below.
 
 
 More information about the Larson Scanner project is at 
 http://www.evilmadscientist.com/article.php/larsonkit
 
 */

#define PIN_ON  HIGH
#define PIN_OFF LOW

void cylon(void)
{
#define LED_MAX 9
  uint8_t LEDs[LED_MAX];		// Storage for current LED values
  int8_t eyeLoc[5];		// List of which LED has each role, leading edge through tail.
  uint8_t LEDBright[4] = { 
    1U, 4U, 2U, 1U     };	// Relative brightness of scanning eye positions
  int8_t j, m;

  uint8_t position, loopcount, direction;
  uint8_t ILED, RLED, MLED;

  uint8_t delaytime;

  uint8_t pt, debounce, speedLevel;
  unsigned int debounce2, BrightMode;

  uint8_t LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8;

  uint8_t LEDpin[LED_MAX] = { 
    12, 11, 10, 9, 8, 7, 6, 5, 4     };

  for (j = 0; j < LED_MAX; j++) {
    pinMode(LEDpin[j], OUTPUT);     
  }

  debounce = 1;
  debounce2 = 1;
  loopcount = 254;
  delaytime = 0;

  direction = 0;
  position = 127;
  speedLevel = 2;		// Range: 1, 2, 3
  BrightMode = 1;

  for (;;)			// main loop
  {
    loopcount++;

    if (loopcount > delaytime) {
      loopcount = 0;

      position++;

      if (position == 128) {
        position = 0;

        if (direction == 0)
          direction = 1;
        else
          direction = 0;

        while (light_visible()) {
          for (j = 0; j < LED_MAX; j++) {
            digitalWrite(LEDpin[j], PIN_OFF);     
          }

          delay(300);
        }
      }

      if (direction == 0)	// Moving to right, as viewed from front.
      {
        ILED = (15 + position) >> 4;
        RLED = (15 + position) - (ILED << 4);
        MLED = 15 - RLED;
      } 
      else {
        ILED = (127 - position) >> 4;
        MLED = (127 - position) - (ILED << 4);
        RLED = 15 - MLED;
      }

      j = 0;
      while (j < 9) {
        LEDs[j] = 0;
        j++;
      }

      j = 0;
      while (j < 5) {

        if (direction == 0)
          m = ILED + (2 - j);	// e.g., eyeLoc[0] = ILED + 2; 
        else
          m = ILED + (j - 2);	// e.g., eyeLoc[0] = ILED - 2;

        if (m > 8)
          m -= (2 * (m - 8));

        if (m < 0)
          m *= -1;

        eyeLoc[j] = m;

        j++;
      }

      j = 0;		// For each of the eye parts...
      while (j < 4) {

        LEDs[eyeLoc[j]] += LEDBright[j] * RLED;
        LEDs[eyeLoc[j + 1]] += LEDBright[j] * MLED;

        j++;
      }

      LED0 = LEDs[0];
      LED1 = LEDs[1];
      LED2 = LEDs[2];
      LED3 = LEDs[3];
      LED4 = LEDs[4];
      LED5 = LEDs[5];
      LED6 = LEDs[6];
      LED7 = LEDs[7];
      LED8 = LEDs[8];
    }

    if (BrightMode == 0) {
#if 0
      j = 0;
      while (j < 60) {

        //Multiplexing routine: Each LED is on (1/9) of the time. 
        //  -> Use much less power.

        if (LED0 > j)
          PORTD = 4;
        else
          PORTD = 0;
        //              shortdelay();   


        if (LED1 > j)
          PORTD = 8;
        else
          PORTD = 0;

        if (LED2 > j)
          PORTD = 16;
        else
          PORTD = 0;

        if (LED3 > j)
          PORTD = 32;
        else
          PORTD = 0;

        if (LED4 > j)
          PORTD = 64;
        else
          PORTD = 0;


        if (LED5 > j) {
          PORTB = 17;
          PORTD = 0;
        } 
        else {
          PORTB = 16;
          PORTD = 0;
        }

        if (LED6 > j)
          PORTB = 18;
        else
          PORTB = 16;

        if (LED7 > j)
          PORTB = 20;
        else
          PORTB = 16;

        if (LED8 > j)
          PORTB = 24;
        else
          PORTB = 16;

        j++;
        if (speedLevel == 3)
          j++;
        PORTB = 16;
      }



#endif /* Brightmode == 0 */
    }

    else {


      int cow;
      /* The ATmega is too fast, so keep the PWM going a little longer */
      for (cow = 0; cow < 2; cow++ ) {

        j = 0;
        while (j < 60) {

          int i;

          for (i = 0; i < LED_MAX; i++) {
            digitalWrite(LEDpin[i], (LEDs[i] > j) ? PIN_ON : PIN_OFF);
          }

          j++;
          if (speedLevel == 3)
            j++;
        }
      }
    }

  }				//End main loop
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println("CylonScanner05");
}

void loop()
{
  cylon();
}



