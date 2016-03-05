/*
  lcd.h - Library for 2x16 character LCD (NHD-0216BZ-FL-YBW).
  Created by Tim Johns, August 15, 2014.
  Released into the public domain.
*/

#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

enum LCD_PINS {
	LCD_RS = 4,
	LCD_RW = 5,
	LCD_E = 6,
};

enum LCD_DATA_BUS {
	LCD_DB4 = 7,
	LCD_DB5 = 8,
	LCD_DB6 = 9,
	LCD_DB7 = 10,
};

void lcd_nybble(void);
void lcd_cmd(uint8_t);
void lcd_data(uint8_t);
void lcd_init(void);
void lcd_clear(void);
void lcd_clear1(void);
void lcd_clear2(void);
void lcd_write(const char *);
void lcd_write1(const char *);
void lcd_write2(const char *);
void lcd_cursor_off(void);
void lcd_cursor_on(void);

#endif
