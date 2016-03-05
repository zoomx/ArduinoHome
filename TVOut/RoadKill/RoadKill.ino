/***********
* RoadKill *
************

by JThr3e

https://github.com/JThr3e/RoadKill-Game

A simple game on the arduino using the TVOut library.

Pins 7 and 9 on the board are used for video output.
Pin 2 is used for button input.

Some modifications for PAL and Funduino Joystick Shield
by Zoomx 2015 05 30
Button logic reversed
*/
#include <fontALL.h>
#include <TVout.h>

boolean gameOver = false;
boolean gameStart = true;
int score = 0;
int BirdX = 50;
int BirdY = 50;
int BirdAcc = 0;
int Car1x = 120;
int Car2x = 200;
int Car3x = 280;
int Car1y = 0;
int Car2y = 50;
int Car3y = 0;
int Hres;
int Vres;
TVout TV;
int pushButton = 2;

void setup()  {
  Serial.begin(9600);
  Serial.println("RoadKill on TV");
  TV.begin(PAL,120,96);
  TV.select_font(font6x8);
  Hres = TV.hres();
  Vres = TV.vres();
  pinMode(pushButton, INPUT);
}

void printGame()
{
  TV.print(score);
  TV.draw_circle(BirdX,BirdY,2,WHITE);
  if(Car1x<120) TV.draw_rect(Car1x,Car1y,10,10,WHITE);
  if(Car2x<120) TV.draw_rect(Car2x,Car2y,10,10,WHITE);
  if(Car3x<120) TV.draw_rect(Car3x,Car3y,10,10,WHITE);
}

int readButon()
{
  int buttonState = !digitalRead(pushButton);
  Serial.println(buttonState);
  return buttonState;
}

void birdAct(int buttonState)
{
  if(buttonState == 1 && BirdY>5) BirdY--;
  else
  {
    if(buttonState == 0 && BirdY<90) BirdY++;
  }
}

void carKontrol()
{
  Car1x-=2;
  Car2x-=2;
  Car3x-=2;
  if(Car1x<0)
  {
    Car1x = 280;
    Car1y = random(0,88);
    score++;
  }
  if(Car2x<0)
  {
    Car2x = 280;
    Car2y = random(0,88);
    score++;
  }
  if(Car3x<0)
  {
    Car3x = 280;
    Car3y = random(0,88);
    score++;
  }
}
void checkForGO()
{
  if((BirdX<Car1x+10 && BirdX>Car1x-3) && (BirdY<Car1y+13 && BirdY>Car1y-3) || (BirdX<Car2x+10 && BirdX>Car2x-3) && (BirdY<Car2y+13 && BirdY>Car2y-3) || (BirdX<Car3x+10 && BirdX>Car3x-3) && (BirdY<Car3y+13 && BirdY>Car3y-3))
  {
    gameOver = true;
    delay(1000);
  }
}

void loop()
{
  if(gameStart)
  {
    TV.print("...-=ROADKILL=-...\n\nWELCOME TO ROADKILL\n\nUSE BUTTON TO\nDODGE CARS, GL!\n\nPRESS BUTTON\nTO START!");
    while(readButon() != 1){}
    gameStart = false;
  }
  if(!gameOver)
  {
    printGame();
    int bState = readButon();
    birdAct(bState);
    carKontrol();
    checkForGO();
    TV.delay_frame(1);
    TV.clear_screen();
    
  }
  else
  {
    TV.println("...-=ROADKILL=-...");
    TV.println("\n     GAMEOVER     ");
    TV.print("\nScore: ");
    TV.print(score);
    TV.print("\n\nPress Button\nFor New Game!");
    TV.delay_frame(1);
    while(readButon() != 1){}
    BirdX = 50;
    BirdY = 50;
    BirdAcc = 0;
    Car1x = 120;
    Car2x = 200;
    Car3x = 280;
    Car1y = 0;
    Car2y = 50;
    Car3y = 0;
    score = 0;
    gameOver = false;
  }
}




