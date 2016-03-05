#include <arduino.h>
#include <avr/pgmspace.h>
#include <TVout.h>
#include "stage.h"
#include "numbers_bitmaps.h"
#include "spread_bitmaps.h"

#define PAUSE_BETWEEN_LIFE_COUNT 500
#define PAUSE_BETWEEN_SPREADS 1000

extern TVout TV;
extern unsigned char level;
extern int life;
extern unsigned long score;
extern char sandwich_type[];
extern char sandwich;
extern unsigned char bread_spread;

extern boolean spreading;
unsigned long time_next_life = 0;
unsigned long time_next_spread = 0;
char level_number = 0;

const char spreading_count[] = {
  3,4,5,6,7,8,8,8};

int you = 0;
int you_count = 0;

void stage_update()
{
  level_draw();
  switch (spreading)
  {
  case 0:
    computer_spread_draw();
    break;
  case 1:
    player_spread_draw();
    life_draw();
    break;
  }

  TV.delay(1);
}

void level_draw()
{
  TV.bitmap(28,0,level_bitmap);
  char buf[10];
  itoa(level, buf, 10);
  char charLen = strlen(buf);
  char pad = 2-charLen;

  //draw 0 padding

  for (byte i=0; i< pad; i++)
  {
    TV.bitmap(76+(11*i),0,number_0_bitmap);
  }


  for (byte i=0; i< charLen; i++)
  {
    char digit = buf[i];
    if (digit <= 48)
    {
      digit = 0;
    } 
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }
    switch (digit)
    {
    case 0:
      TV.bitmap(76+(pad*11)+(11*i),0,number_0_bitmap);
      break;
    case 1:
      TV.bitmap(76+(pad*11)+(11*i),0,number_1_bitmap);
      break;
    case 2:
      TV.bitmap(76+(pad*11)+(11*i),0,number_2_bitmap);
      break;
    case 3:
      TV.bitmap(76+(pad*11)+(11*i),0,number_3_bitmap);
      break;
    case 4:
      TV.bitmap(76+(pad*11)+(11*i),0,number_4_bitmap);
      break;
    case 5:
      TV.bitmap(76+(pad*11)+(11*i),0,number_5_bitmap);
      break;
    case 6:
      TV.bitmap(76+(pad*11)+(11*i),0,number_6_bitmap);
      break;
    case 7:
      TV.bitmap(76+(pad*11)+(11*i),0,number_7_bitmap);
      break;
    case 8:
      TV.bitmap(76+(pad*11)+(11*i),0,number_8_bitmap);
      break;
    case 9:
      TV.bitmap(76+(pad*11)+(11*i),0,number_9_bitmap);
      break;
    }
  }
}

void life_draw()
{
  TV.draw_rect(0,94,128,2,0,0);
  TV.draw_rect(0,94,life,2,1,1);
  if (millis() >= time_next_life)
  {
    life--;
    time_next_life = millis() + PAUSE_BETWEEN_LIFE_COUNT ;
  }
}



void computer_spread_draw()
{
  if (millis() >= time_next_spread)
  {
    TV.bitmap(14,30,cpu_bitmap);
    for (byte i = 0; i< sandwich; i++)
    {
     TV.bitmap(0,18+(9*i),small_slice_bread_bitmap);
    }
    level_number = level %8;
    cpu_sandwich_draw();
    time_next_spread = millis() + PAUSE_BETWEEN_SPREADS ;
  }
}

void player_spread_draw()
{
  for (byte i = 0; i< sandwich; i++)
  {
    TV.bitmap(120,18+(9*i),small_slice_bread_bitmap);
  }
  TV.bitmap(104,30,you_bitmap);
  you_sandwich_draw(); 
}



void score_draw(int scoreX, int scoreY)
{
  char buf[10];
  itoa(score, buf, 10);
  char charLen = strlen(buf);
  char pad = 4-charLen;

  //draw 0 padding

  for (byte i=0; i< pad; i++)
  {
    TV.bitmap(scoreX+(11*i),scoreY,number_0_bitmap);
  }


  for (byte i=0; i< charLen; i++)
  {
    char digit = buf[i];
    if (digit <= 48)
    {
      digit = 0;
    } 
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }
    switch (digit)
    {
    case 0:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_0_bitmap);
      break;
    case 1:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_1_bitmap);
      break;
    case 2:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_2_bitmap);
      break;
    case 3:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_3_bitmap);
      break;
    case 4:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_4_bitmap);
      break;
    case 5:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_5_bitmap);
      break;
    case 6:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_6_bitmap);
      break;
    case 7:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_7_bitmap);
      break;
    case 8:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_8_bitmap);
      break;
    case 9:
      TV.bitmap(scoreX+(pad*11)+(11*i),scoreY,number_9_bitmap);
      break;
    }
    TV.bitmap(scoreX+(44),scoreY,number_0_bitmap);
  }
}

void cpu_sandwich_draw()
{
  int y;
  for (int i = 0; i<8; i++)
  {
    sandwich_type[i] = random(1, 5);
  }
  y = spreading_count[level_number-1]; // we know how many spreadings for this level and this sandwich
  draw_bread(28,18,0);
  TV.delay(500);
  for (int i = 0; i < y; i++)
  {
    draw_bread(28,18,sandwich_type[i]);
    TV.delay(500);
    draw_bread(28,18,0);
    TV.delay(500);
  }
  spreading = 1;
  you = 0;
  TV.clear_screen();
}

void you_sandwich_draw()
{
  if (you == 0)
  {
   draw_bread(28,18,0);
  }
  you = spreading_count[level_number-1]; // we know how many spreadings for this level and this sandwich


  if (bread_spread == sandwich_type[you_count])
  {
    score++;
    draw_bread(28,18,bread_spread);
    you_count++;
  }
  else if(bread_spread != 0)
  {
    life = life - 5;
    if (score != 0)
      {
        score--;
      }
  }
  bread_spread = 0;


  if (you_count >= you)
  {
    TV.delay(750);
    spreading = 0;
    sandwich++;
    if (sandwich >= 9)
    {
      sandwich = 1;
      level++;
      life = 128;
    }
    TV.clear_screen();
    you_count = 0;
  }
}

void draw_bread(int breadX, int breadY, int spreadtype)
{
  switch (spreadtype)
  {
    case 0:
      TV.bitmap(breadX,breadY,slice_bread_bitmap);
      break;
    case 1:
      TV.bitmap(breadX,breadY,salami_bitmap);
      break;
    case 2:
      TV.bitmap(breadX,breadY,cheese_bitmap);
      break;
    case 3:
      TV.bitmap(breadX,breadY,jam_bitmap);
      break;
    case 4:
      TV.bitmap(breadX,breadY,sprinkles_bitmap);
      break;
  }
}








