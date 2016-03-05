#include "Arduino.h"
#include "NesController.h"

NesController::NesController(int clock_pin, int latch_pin, int serial_pin)
{
  up = down = left = right = select = start = a = b = false;
  
  _clock_pin = clock_pin;
  _latch_pin = latch_pin;
  _serial_pin = serial_pin;
  
  pinMode(_latch_pin,OUTPUT);
  pinMode(_clock_pin,OUTPUT);
  pinMode(_serial_pin,INPUT);
  
  digitalWrite(_latch_pin,HIGH);
  digitalWrite(_clock_pin,HIGH);
}

byte NesController::readData()
{
  data = 0;
  
  // ask for data
  digitalWrite(_latch_pin,LOW);
  digitalWrite(_clock_pin,LOW);

  digitalWrite(_latch_pin,HIGH);
  delayMicroseconds(2);
  digitalWrite(_latch_pin,LOW);

  // read data
  data = digitalRead(_serial_pin);
  
  for (int i = 1; i <= 7; i ++) {
    digitalWrite(_clock_pin,HIGH);
    delayMicroseconds(2);
    data <<= 1;
    data += digitalRead(_serial_pin) ;
    delayMicroseconds(4);
    digitalWrite(_clock_pin,LOW);
  }
  
  data = ~data;
  
  up = down = left = right = select = start = a = b = false;
  if (data & 0b00000001) right = true;
  if (data & 0b00000010) left = true;
  if (data & 0b00000100) down = true;
  if (data & 0b00001000) up = true;
  if (data & 0b00010000) start = true;
  if (data & 0b00100000) select = true;
  if (data & 0b01000000) b = true;
  if (data & 0b10000000) a = true;
  
  return data;
}
