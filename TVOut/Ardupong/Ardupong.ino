/*
ARDUPONG
By Ramon Imbao
https://github.com/ramonimbao/Ardupong

Some modificarions by Zoomx 2015 05 30
File renamed from Pong_2P.ino to Ardupong.ino
changed from NTSC to PAL
Works but stop on Game Over code must be changed
Adapted for Funduino Joystick Shield ->FJS

*/
#include <font4x6.h>
#include <font8x8.h>
#include <TVout.h>

/* INSTRUCTIONS
 
 * PLAYER 1:
 Connect a potentiometer
 /'''\/''''' PIN 3/5
 | R  |----- A0
 \___/\_____ GND
 
 * PLAYER 2:
 Connect a potentiometer
 /'''\/''''' PIN 3/5
 | R  |----- A1
 \___/\_____ GND
 
 
 Changed for Funduino Joystick Shield so these connections are not used
 
 * Connect PIN 11 to PIN 4
 (requires buzzer to be connected to PIN 4)
 
 * Connect the TV out circuit to Arduino
 
 */

TVout TV;

float p1_y = 38;
float p2_y = 38;

int p1_score = 0;
int p2_score = 0;

// start in the middle!
float ball_x = 64;
float ball_y = 48;

float bdx = 1; // 1 = leftward, -1 = rightward
float bdy = 1; // 1 = downward, -1 = upward

boolean firstTimeToPlay = true;
boolean gameOver = false;

int winner = 0;

const int MAX_SCORE = 10;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  // random seed
  randomSeed((analogRead(A0) * analogRead(A1)) + (analogRead(A0) / analogRead(A1)));
  bdx *= (random(100) > 50 ? -1 : 1);
  bdy *= (random(100) > 50 ? -1 : 1);

  /*
  Disabled since they are used for the paddle
  and not needed on FJS
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  */

  pinMode(11, OUTPUT);
  pinMode(4, INPUT);

  TV.begin(PAL); // (128x96 screen size)
  TV.select_font(font4x6);

  // Let's draw the playfield
  TV.draw_rect(0,0,127,95,WHITE);
}

void loop() {
  if (gameOver == false) {
    // Handle P1 input
    p1_y = (float)analogRead(A0)/670 * 74;   //was 1023 but in FJS max is about 670
    // Handle P2 input
    p2_y = (float)analogRead(A1)/670 * 74;

    // Handle ball movement and collision
    ball_x += bdx;
    ball_y += bdy;
    if (ball_y <= 1) {
      bdy *= -1.05; 
    }
    if (ball_y >= 96) {
      bdy *= -1.05;
    }
    if (ball_x <= 3) { 
      if (ball_y >= p1_y && ball_y <= p1_y + 20) { // hit P1
        bdx *= -1.05;
      }
      else if (ball_x <= 1) { // hit P1's goal
        ball_x = 64; // reset the 
        ball_y = 48; //   ball
        bdx = (random(100) > 50 ? -1 : 1); // set a new random direction
        bdy = (random(100) > 50 ? -1 : 1); //   for the ball
        p2_score++;
        TV.tone(880, 1000);
        if (p2_score == MAX_SCORE) {
          winner = 1;
          gameOver = true; 
        }
        delay(1500);
      }
    }
    if (ball_x >= 124) { 
      if (ball_y >= p2_y && ball_y <= p2_y + 20) { // hit P2
        bdx *= -1.05;
      }
      else if (ball_x >= 126) { // hit P2's goal
        ball_x = 64; // reset the
        ball_y = 48; //   ball
        bdx = (random(100) > 50 ? -1 : 1); // set a new random direction
        bdy = (random(100) > 50 ? -1 : 1); //   for the ball
        p1_score++;
        TV.tone(880, 1000);
        if (p1_score == MAX_SCORE) {
          winner = 1;
          gameOver = true; 
        }
        delay(1500);
      }
    }

    // Clear the entire screen!
    TV.draw_rect(1,1,125,93,BLACK,BLACK);
    // Draw divider in the middle
    for (int _y = 1; _y <= 96; _y += 16) {
      TV.draw_rect(64, 1+_y, 1, 8, WHITE);
    }  

    // Draw the ball
    TV.draw_circle(ball_x, ball_y, 1, WHITE, WHITE);

    // Draw player 1 and his score
    TV.draw_rect(1, (int)p1_y, 1, 20, WHITE);
    TV.print(32, 4, p1_score);

    // Draw player 2
    TV.draw_rect(125, (int)p2_y, 1, 20, WHITE);
    TV.print(96, 4, p2_score);

    if (firstTimeToPlay) {
      TV.select_font(font8x8);
      TV.print(40, 47, "READY?");
      TV.select_font(font4x6);
      delay(5000);

      firstTimeToPlay = false;
    }
  }

  else if (gameOver == true) {
    TV.select_font(font8x8);
    TV.print(30, 47, "GAME OVER");
  }

  delay(1000/240);
}
