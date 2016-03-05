#include <Arduino.h>
#include "Input.h"

uint32_t Input::last_change_at = 0;
Button   Input::last_pressed   = ButtonNone;

Button Input::read(void)
{
  uint16_t reading = analogRead(A0);

  if (abs(reading - ButtonNone) < ButtonTreshold) {
    return ButtonNone;
  } else
  if (abs(reading - ButtonRight) < ButtonTreshold) {
    return ButtonRight;
  } else
  if (abs(reading - ButtonLeft) < ButtonTreshold) {
    return ButtonLeft;
  } else
  if (abs(reading - ButtonDown) < ButtonTreshold) {
    return ButtonDown;
  } else
  if (abs(reading - ButtonUp) < ButtonTreshold) {
    return ButtonUp;
  } else
  if (abs(reading - ButtonSelect) < ButtonTreshold) {
    return ButtonSelect;
  }

  return ButtonNone;
}

Button Input::get(void)
{
  uint32_t now             = millis();
  Button   current_pressed = read();

  if ( (now - last_change_at) > ButtonTimePressed && current_pressed != last_pressed) {
    last_change_at = now;
    last_pressed   = current_pressed;
    return current_pressed;
  } else
  if ( (now - last_change_at) > ButtonTimeHeld && current_pressed == last_pressed) {
    last_change_at = now;
    last_pressed   = current_pressed;
    return current_pressed;
  } else {
    return ButtonNone;
  }
}
