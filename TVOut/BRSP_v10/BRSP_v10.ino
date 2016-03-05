/*
 BREAD SPREAD: http://www.team-arg.org/TEAM-arg/BRSP-downloads.html 

 By TEAM a.r.g.

 made on ARUINDO-JAM IV: http://www.arduino-jam.org
 
 2013 - JO3RI - Bart - David
 
 Modifications by Zoomx 30 05 2015
 For PAL and Funduino Joystick Shield
 Buttons logic is negate so digitalRead became !digitalRead
 */

//determine the game
#define GAME_ID 16

#include <avr/pgmspace.h>

#define PAUSE_BETWEEN_ACTIONS 80
#define PAUSE_BETWEEN_SWITCH  500

//define game states
#define GAME_SPLASH  0
#define GAME_INIT    1
#define GAME_PLAYING 2
#define GAME_OVER    3

// define spread state
#define SALAMI       1
#define CHEESE       2
#define JAM          3
#define SPRINKLES    4

#include <TVout.h>
#include "bitmap.h"
#include "stage.h"

TVout TV;

// Determines the state of the game
unsigned char game_state = 0;
unsigned char bread_spread = 0;
unsigned long next_action = 0;

// These are all getting a value in STATE_GAME_INIT
int life;
unsigned long score;
unsigned char level;
unsigned char sandwich;
boolean spreading;
boolean show_hide = 0;
char sandwich_type[] ={
  0,0,0,0,0,0,0,0};
int status_spread = 0;

// buttons
byte buttonPin0 = 2;
byte buttonPin1 = 3; //4;
byte buttonPin2 = 4; //8;
byte buttonPin3 = 5; //12;
int count0 = 1;

void setup() {
  TV.begin(PAL,128,96);
  TV.delay(3000);
  TV.clear_screen();
  TV.bitmap(16,40,made_at_bitmap);
  TV.delay(1000);
  TV.clear_screen();
  TV.bitmap(16,0,arduinojam_logo_bitmap);
  TV.delay(2000);
  TV.clear_screen();
  TV.bitmap(21,32,presented_by_bitmap);
  TV.delay(1000);
  TV.clear_screen();
  TV.bitmap(18,32,team_arg_bitmap);
  TV.delay(2000);
  TV.clear_screen();

  pinMode(buttonPin0,INPUT);
  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonPin3,INPUT);
}

void loop()
{  
  switch (game_state)
  {

    //******* MENU-specific events **************    

  case GAME_SPLASH:
    start_screen();
      if(!digitalRead(buttonPin0) || !digitalRead(buttonPin1) ||!digitalRead(buttonPin2) ||!digitalRead(buttonPin3))
      {
        game_state = GAME_INIT;
      }
    break;

    //******* Game-specific events **************
  case GAME_INIT:
    TV.clear_screen();
    score = 0;
    level = 1;
    life = 128;
    sandwich = 1;
    spreading = 0;
    game_state = GAME_PLAYING;
    for (byte i = 0; i<8; i++)
    {
      sandwich_type[i] = random(1, 5);
    }
    break;

  case GAME_PLAYING:
    stage_update();
    if (millis() >= next_action)
    {
      boolean pin2 = !digitalRead(buttonPin0);
      boolean pin4 = !digitalRead(buttonPin1);
      boolean pin8 = !digitalRead(buttonPin2);
      boolean pin12 = !digitalRead(buttonPin3);

      if(status_spread == 0)
      {
        if(pin2)
        {
          bread_spread = SALAMI;
          status_spread = 1;

        }
        else if(pin4)
        {
          bread_spread = CHEESE;
          status_spread = 1;
        }
        else if(pin8)
        {
          bread_spread = JAM;
          status_spread = 1;
        }
        else if(pin12)
        {
          bread_spread = SPRINKLES;
          status_spread = 1;
        }
      }
      if(pin2 == LOW && pin4 == LOW && pin8 == LOW && pin12 == LOW)
      {
        status_spread = 0;
      }

      next_action = millis() + PAUSE_BETWEEN_ACTIONS;
    }

    //check the players's life
    if (life < 0)
    {
      game_state = GAME_OVER;
      TV.clear_screen();
      TV.delay(500);
      game_over();
    }
    break;

  case GAME_OVER:
    if(!digitalRead(2) || !digitalRead(4) ||!digitalRead(8) ||!digitalRead(12))
      {
      TV.clear_screen();
      game_state = GAME_SPLASH;
      delay(1000);
    }
    break;
  }
}

//****************** Menu-specific functions
void start_screen()
{
  if (millis() >= next_action)
  { 
    switch (show_hide)
    {
    case false:
      TV.bitmap(2,0,breadspread_bitmap);
      draw_bread(28,24,0);
      TV.bitmap(35,38,smash_bitmap);
      TV.bitmap(40,56,your_bitmap);
      TV.bitmap(31,74,spread_bitmap);
      break;
    case true:
      draw_bread(28,24,0);
      break;
    }
    show_hide = !show_hide;
    next_action = millis() + PAUSE_BETWEEN_SWITCH;
  }
}

void game_over()
{  
  if (millis() >= next_action)
  {
    TV.bitmap(16,0,game_bitmap);
    TV.bitmap(70,0,over_bitmap);
    draw_bread(28,24,0);
    TV.bitmap(34,42,score_bitmap);
    score_draw(33,66);
  }
}







