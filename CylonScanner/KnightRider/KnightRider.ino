//KnightRider
//http://blog.blinkenlight.net/experiments/basic-effects/knight-rider/

//
//  www.blinkenlight.net
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
//  along with this program. If not, see http://www.gnu.org/licenses/

#define FirstLed 4
#define LastLed 12      //LastLed+1

void setup() {
  Serial.begin(9600);
  Serial.println("KnightRider");
  for (uint8_t pin=FirstLed; pin<LastLed; ++pin) {  //was 0 and 20
    pinMode(pin, OUTPUT);
  }
}

uint8_t brightness(const int8_t led, const int8_t pos) {    
  switch (abs(led-pos)) {
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

void pulse_width_modulation(const uint8_t pos) {
  for(uint8_t times=0; times<10; ++times) {
    for (uint8_t pass=0; pass<32; ++pass) {
      for (int8_t led=FirstLed; led<LastLed; ++led) {
        digitalWrite(led, (brightness(led, pos) > pass));
      }
    }
  }
}

void loop() {
  static uint8_t pos=0;

  while(pos<LastLed) {
    pulse_width_modulation(pos);
    ++pos;
  }

  while(pos>FirstLed) {
    --pos;
    pulse_width_modulation(pos);
  }
}

