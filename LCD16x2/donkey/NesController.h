/** 
 * NES Controller class
 * 
 * Author: Petr Kratina <petr.kratina@gmail.com>
 * Version: 1.0
 * Date: 2014-01-28
 * Licence: Public domain
 */

#ifndef NesController_h
#define NesController_h

#include "Arduino.h"

class NesController
{
  public:
    NesController(int clock_pin, int latch_pin, int serial_pin);
    byte readData();
    byte data;
    boolean start;
    boolean select;
    boolean a;
    boolean b;
    boolean up;
    boolean down;
    boolean left;
    boolean right;
  private:
    int _clock_pin;
    int _latch_pin;
    int _serial_pin;
};

#endif
