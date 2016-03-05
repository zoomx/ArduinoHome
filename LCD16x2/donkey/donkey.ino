// include the library code:
#include "config.h"
#include "gfx.h"
#include "sfx.h"
#include "NesController.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
NesController nes(NES_CLOCK, NES_LATCH, NES_SERIAL);
long timer = 0;
float rpt = 0;
float rpb = 2;
byte px = 2;
byte py = 0;
float dx = 0;
byte dy = 0;
float spd = 0.5;
float spdMin = 0.5;
float spdMax = 1.5;
boolean mute = false;
float score = 0;
int level = 1;
int lives = 3;
boolean donkeyHit = false;
int donkeyBeep = 0;

void setup() {
  // initialize LCD with loading text
  initLcd();
  // initialize sound
  pinMode(SOUND_PIN, OUTPUT);
  
  startGame();
}

void loop() {
  if (millis() - timer > 60) {
    timer = millis();

    handleControls();
    showRoad();
    showDonkey();
    showPlayer();
    showHud();
    updateScore();
    
    if (donkeyHit) lives--;
    if (lives <= 0) {
      gameOver();
    } else if (donkeyHit) {
      startLevel(level);
    } 
    
    if (score > 1000) {
      score -= 1000;
      startLevel(level + 1);
    }
    
    if (!SOUND_ENABLED) donkeyBeep = 0;
    if (donkeyBeep > 0) {
      tone(SOUND_PIN, 1000, 10);
      donkeyBeep--;
    }
  }
  if ((!mute) && SOUND_ENABLED && (donkeyBeep == 0)) tone(SOUND_PIN, spd * 500, 2);
}

/* GAME */

void playMusic(int melody[], int beats[], int length)
{
  if (!SOUND_ENABLED) return;
  for (int i = 0; i < length; i++) {
    int duration = 1000/beats[i];
    tone(SOUND_PIN, melody[i], duration);
    int pause = duration * 1.30;
    delay(pause);
    noTone(SOUND_PIN);
  }
}

void startGame()
{
   lcd.clear(); 
   lcd.write(byte(3));
   lcd.write(" DONKEY DODGE ");
   lcd.write(byte(4));
   String line = "  Press  START                  Author:P.Kratina                ard.darkyork.com";
   
   int pos = 0;
   int dir = 1;
   
   playMusic(sfx_melody_2, sfx_beats_2, sfx_length_2);

   timer = millis();
   
   while (true) {
     lcd.setCursor(0,1);
     lcd.print(line.substring(pos, pos + 16));
     if (millis() - timer > 2000) {
       pos += dir;
       if (pos % 32 == 0) {
         timer = millis();
         if (pos == 64 || pos == 0) {
           dir *= -1;
         }
       }
     }
     delay(60);
     nes.readData();
     if (nes.start) {
       startLevel(1);
       break;
     }
   }
}

void gameOver()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   GAME  OVER");
  lcd.setCursor(0,1);
  lcd.print("   SCORE ");
  lcd.print(int(score + level * 1000), DEC);
  
  playMusic(sfx_melody_3, sfx_beats_3, sfx_length_3);
  
  while (true) {
    nes.readData();
    if (nes.start) {
      break;
    }
    delay(100);
  }
  lives = 3;
  score = 0;
  startLevel(1);
}

void showDonkey()
{
  donkeyHit = (int(dx) == int(px) && int(dy) == int(py));
  if (dx < 13) {
    lcd.setCursor(dx, dy);
    lcd.write(byte(3));
  }
  
  dx -= spd;
  if (dx < 0) {
    dx = 16 + random(0,20);
    dy = random(0,2);
    score += 10 + spd * 10;
    donkeyBeep = 5;
  }
}

void startLevel(int lvl)
{
  donkeyBeep = 0;
  donkeyHit = false;
  level = lvl;
  px = 2;
  py = 0;
  dx = 0;
  dy = 0;
  spdMin = (45 + float(level) * 5) / 100;
  spd = spdMin;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    LEVEL ");
  lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("    LIVES ");
  lcd.print(lives);
  
  playMusic(sfx_melody_1, sfx_beats_1, sfx_length_1);
  
  delay(2000);
}

void updateScore()
{
  score += spd / 10;
}

void showHud()
{
  int s;
  // speed
  s = spd * 100;
  if (s < 10) {
    lcd.setCursor(15,0);
  } else if (s < 100) {
    lcd.setCursor(14,0);
  } else {
    lcd.setCursor(13,0);
  }
  lcd.print(s, DEC);
  // score
  s = score;
  if (s < 10) {
    lcd.setCursor(15,1);
  } else if (s < 100) {
    lcd.setCursor(14,1);
  } else if (s < 1000) {
    lcd.setCursor(13,1);
  } else {
    lcd.setCursor(12,1);
  }
  lcd.print(s, DEC);
}

void handleControls()
{
  nes.readData();
  if (nes.up && py == 1) py = 0;
  if (nes.down && py == 0) py = 1;
  if (nes.left && px > 0) px--;
  if (nes.right && px < 10) px++;
  if (nes.select) mute = !mute;
  if (nes.a && spd < spdMax) spd += 0.01;
  if (nes.b && spd > spdMin) spd -= 0.01;
}

void showRoad()
{
  int x;
  lcd.clear();
  lcd.setCursor(0,0);
  for (int i = 0; i < 4; i++) {
    x = i * 4 + rpt;
    if (x < 13) {
      lcd.setCursor(x, 0);
      lcd.write(byte(0));
    }
    x = i * 4 + rpb;
    if (x < 13) {
      lcd.setCursor(x, 1);
      lcd.write(byte(1));
    }
  }
  rpt -= spd;
  rpb -= spd;
  if (rpt < 0) rpt += 4;
  if (rpb < 0) rpb += 4;
}

void showPlayer()
{
  lcd.setCursor(px,py);
  lcd.write(byte(2));
}

/* INITIALIZATION FUNCTIONS */

void initLcd()
{
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();
  lcd.print("   Loading...");
  lcd.createChar(0, gfx0);
  lcd.createChar(1, gfx1);
  lcd.createChar(2, gfx2);
  lcd.createChar(3, gfx3);
  lcd.createChar(4, gfx4);
  lcd.createChar(5, gfx5);
  lcd.createChar(6, gfx6);
  lcd.createChar(7, gfx7);
}

/* MISC */

void showError(String msg)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Error:");
  lcd.setCursor(0,1);
  lcd.print(msg);
  
  while (true);
}


