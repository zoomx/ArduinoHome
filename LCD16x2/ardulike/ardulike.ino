#include <LiquidCrystal.h>
#include "Input.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

uint8_t position        = 0;
uint8_t level           = 0;

bool init_draw          = true;

char lcd_t_row[17];
char lcd_b_row[17];

void draw_player() {
  lcd_b_row[position % 16] = '@';
};

void draw_position() {
  snprintf(lcd_t_row, 17, "L:%dS:%d", level, position / 16);
}

void draw_terrain() {
  randomSeed(((position / 16 + 1) << 8) + level);

  for (uint8_t i = 0; i < 16; i++) {
    lcd_b_row[i] = ((random() % 4) == 0) ? 'T' : ' ';
  }

  lcd_b_row[16] = '\0';
};

void stairs_for_level(uint8_t level, uint8_t * up, uint8_t * down)
{
  randomSeed(level + 1);

  *up   = (uint8_t) random(256);
  *down = (uint8_t) random(256);

  while (*up == *down) { *down = (uint8_t) random(256); }
}

void draw_stairs() {
  uint8_t up   = 0;
  uint8_t down = 0;

  stairs_for_level(level, &up, &down);

  if (level > 0 && up >= (position / 16) * 16 && up < ((position / 16) + 1) * 16) {
    lcd_b_row[up % 16] = '<';
  }

  if (level < 255 && down >= (position / 16) * 16 && down < ((position / 16) + 1) * 16) {
    lcd_b_row[down % 16] = '>';
  }
}

void draw() {
  draw_position();
  draw_terrain();
  draw_stairs();
  draw_player();

  if (init_draw) {
    lcd.begin(16, 2);
    init_draw = false;
  } else {
    lcd.clear();
  }

  lcd.setCursor(0, 0);
  lcd.print(lcd_t_row);
  lcd.setCursor(0, 1);
  lcd.print(lcd_b_row);
};

void setup() {
  draw();
}

void loop() {
  uint8_t  up  = 0;
  uint8_t down = 0;

  bool changed = false;
  Button input = Input::get();

  stairs_for_level(level, &up, &down);

  if (input == ButtonLeft) {
    position -= 1;
    changed   = true;
  } else
  if (input == ButtonRight) {
    position += 1;
    changed   = true;
  } else
  if (input == ButtonDown && position == down && level < 255) {
    level   += 1;
    stairs_for_level(level, &up, &down);
    position = up;
    changed  = true;
  } else
  if (input == ButtonUp && position == up && level > 0) {
    level   -= 1;
    stairs_for_level(level, &up, &down);
    position = down;
    changed  = true;
  }

  if (changed) {
    draw();
  }

  delay(30);
}
