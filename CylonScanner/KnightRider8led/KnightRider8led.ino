//KnightRider8led
// http://blog.blinkenlight.net/experiments/basic-effects/knight-rider/#comment-51731

// Original code from Udo Klein @ http://blog.blinkenlight.net/experiments/basic-effects/knight-rider/

// I MODIFIED THIS EXAMPLE TO ONLY USE EIGHT (8) LED'S AND ALSO IN TERMS THAT I WAS MORE FAMILIAR WITH
// There are three (3) variations of this code Function_1,Function_2 and Function_3. 
// To try them all, just comment out the  two (2) that you do not 
// wish to use and use the third. The remaining code is to be used in all three (3) variants 
// (i.e. - pin declarations, setup, loop and PWM_Function)
// I have taken the "liberty" of changing the variable type uint8_t to byte and slightly
// changing the loop code to make it more familiar to beginners like myself



byte pin[] = { 4, 5, 6, 7, 8, 9, 10, 11 };
void setup() 
{
  Serial.begin(9600);
  Serial.println("KnightRider8led");
  for (byte i = 0; i < 8; i++)
  {
    pinMode(pin[i], OUTPUT);
  }
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Function_1 - pwm knightrider alternate directions
int brightness( byte led, byte pos)

{    
  switch (abs(led-pos))
  {
  case 0:     
    return 32;
  case 1:     
    return 16;
  case 2:     
    return 6;
  case 3:     
    return 2;
  default:    
    return 1;
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
// Function_2 -  Second variant
 byte brightness(byte led, byte pos) {
 	switch (min(abs(led-pos),abs(9-led-pos))) {
 		case 0: 	return 32;
 		case 1: 	return 16;
 		case 2: 	return 6;
 		case 3: 	return 2;
 		default:	return 1;
 	}
 }
 */
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
// Function_3 -  Third variant
 byte brightness(byte led, byte pos) 
 {
 	byte tmp = pos - abs(2*led-11)+2;
 	return (tmp>0? tmp+tmp>>1: 0);
 }
 */
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PWM_Function - THIS FUNCTION USED IN ALL VARIANTS
void pwm(byte pos) 
{
  for(byte times = 0; times < 10; times++)
  {
    for (byte pass = 0; pass < 32; pass++)
    {
      for (byte led = 0; led < 20; led++) 
      {
        digitalWrite(led, (brightness(led, pos) > pass));
      }
    }
  }
}

void loop() 
{
  static byte pos = 0;

  while(pos < 10)
  {
    pwm(pos);
    pos++;
  }

  while(pos > 0) {
    pos--;
    pwm(pos);
  }
}


