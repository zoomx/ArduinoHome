//KnightRider8ledTris
//http://blog.blinkenlight.net/experiments/basic-effects/knight-rider/#comment-48095
//http://blog.blinkenlight.net/experiments/basic-effects/knight-rider/#comment-48097
//http://pastebin.com/7Qwirhcz

//
//  <span class="skimlinks-unlinked">www.blinkenlight.net</span>
//
//  Copyright 2011 Udo Klein
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <span class="skimlinks-unlinked">http://www.gnu.org/licenses</span>/

//Mods by Hockeyrink for figuring out how da hek did Mr. Klein do this? - April 2014
//Little mods 2015-02-06 from 7 to 8 led zoomx
// 2015-04-25 Led away are zero brightness and not 3%

//Assign ring levels to appropriate I/O line
#define r1 11
#define r2 10
#define r3 9
#define r4 8
#define r5 7
#define r6 6
#define r7 5
#define r8 4
const int ledRings[] = {
  r1, r2, r3, r4, r5, r6, r7, r8};  //Set me up the list of pins to be used with the LEDs
int ringCount = 8; // Number of elements we're USING in array (0 to 7)


void setup()
{
  Serial.begin(9600);
  Serial.println("KnightRider8ledTris");
  for (int thisRing = 0; thisRing < ringCount; thisRing++) {
    pinMode(ledRings[thisRing], OUTPUT);
  }
}

byte brightness(const int led, const int pos) {  //Test each LED for distance from focused position. The further way it is, ramp the brightness down
  switch (abs(led-pos)) {
  case 0:     
    return 32;               // LED IS the Pos'n? Make it full bright (32/32)
  case 1:     
    return 16;               // 1 LED away from Pos'n? Make it 1/2 bright (16/32)
  case 2:     
    return 6;               // 2 LEDs away? 6/32 (19% bright)
  case 3:     
    return 1;               // 3 LEDs away? 1/32 on (3% bright)
  default:    
    return 0;               // Even further away? Just make it barely on (3%)
  }
}

void pulse_width_modulation(const byte position) {                  //Position is the present focused LED location
  for(byte times=0; times<40; ++times) {                     	   // Loop "times" higher for a slower action   Changed from 80 to 40
    for (byte brightLevel=0; brightLevel<32; ++brightLevel) {    // Start of "fake" PWM. Looping thru all 32 levels of 
      //brightness that are available, from off (0) to full on (32)
      for (int led=0; led<ringCount; ++led) {                   //Check each LED against this level of brightness. Supposed to be on?
        digitalWrite(ledRings[led], (brightness(led, position) > brightLevel)); //If tested value > brightLevel, turn it on
      }
    }
  }
}

void loop() {
  static int pos=0;

  while(pos<7) {
    pulse_width_modulation(pos);
    ++pos;
  }


  while(pos>0) {
    --pos;
    pulse_width_modulation(pos);
  }

}

/*
Let’s analyze the sketch.
 The underlying idea is that the glowing effect is some kind of cursor that has a position that moves back and forth.
 This is what the main loop takes care of.
 
 The brightness function will compute the desired brightness of an LED depending on the LED’s number and the position
 of the cursor.
 
 In between is the pulse_width_modulation. This function will cycle 10 times through 32 phases.
 For each phase it will cycle through all LEDs.
 Depending on any LED’s desired brightness and the phase it will switch the LED on and off.
 
 For example: Suppose the brightness function returns 16 for an LED.
 In this case the LED will be on for phase in 0..15 and off for phase in 16..31.
 Thus the LED would be on half of the time. Accordingly it will be visibly on but dimmer as an LED that is always on.
 */


