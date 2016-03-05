#ifndef __ARDULIKE_INPUT_H__
#define __ARDULIKE_INPUT_H__

enum Button
{
  ButtonRight  = 0,
  ButtonUp     = 99,
  ButtonDown   = 254,
  ButtonLeft   = 407,
  ButtonSelect = 636,
  ButtonNone   = 1023,

  ButtonTreshold    = 10,
  ButtonTimePressed = 50,
  ButtonTimeHeld    = 300,
};

class Input {
  public:
    static Button get(void);

  private:
    static Button read(void);
    static uint32_t last_change_at;
    static Button   last_pressed;
};

#endif
