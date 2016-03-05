/*
    DOTunio - an arduino game
    by Ronald Kaiser

    2013, july

    contact: raios DOT catodicos AT gmail DOT com
*/

#include <LiquidCrystal.h>

// global variables ---------------------------------------------
// low level variables
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int backlight = 13;
int button = 8;

// game variables
boolean started = false;
int score = 0;
int level = 0;
int threshold = 20; // points to pass a level


// useful functions ---------------------------------------------
boolean button_pressed() {
  return boolean(digitalRead(button));
}

int get_digits(int n) {
  int d = 1;
  int m = 10;
  while(n/m > 0) {
    m *= 10;
    d++;
  }
  return d;
}

void opening() {
  lcd.setCursor(0, 0);
  lcd.write("    {DOTuino}   ");
  lcd.setCursor(0, 1);
  lcd.write("* Press to start");
}

void game_over() {
   lcd.setCursor(0, 0);
   lcd.write("   GAME OVER   ");
   lcd.setCursor(0, 1);
   delay(3000);
}

void show_level(int n) {
  lcd.setCursor(0, 0);
  lcd.write("       I I       ");
  lcd.setCursor(0, 1);
  lcd.write("        U        ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   [LEVEL ");
  lcd.print(n, 10);
  lcd.print("]   ");
  lcd.setCursor(0, 1);
  delay(3000);
}


// setup ----------------------------------------------------------
void setup(){
  // starts serial printing for debugging
  Serial.begin(9600);
  
  pinMode(backlight, OUTPUT); 
  pinMode(button, INPUT);
  
  // turn on backlight
  digitalWrite(backlight, 500);
  
  // display with 16 (columns) x 2 (lines) 
  lcd.begin(16, 2);
  
  // clean screen
  lcd.clear();
}


// loop ------------------------------------------------------------
void loop(){
  lcd.clear();
    
  if (!started) {
    opening();
    
    while(true) {
      if (button_pressed()) {
        // sets started true for the next loop
        started = true;
        show_level(level);
        break;
      }
    }
    delay(100);
  }
  // game started
  else { 
     int pl = 0;    // player line
     int ec = 15;   // enemy column
     int el = 0;    // enemy line

     while(true) {
       lcd.clear();
                 
       // collision detection ---------------------------------------------
       if ((ec - (level+1)) <= 0 && (pl == el)) {
         game_over();
         level = 0;
         score = 0;
         started = false;
         break;
       }
              
       // position updates -------------------------------------------------       
       // new player position
       if (button_pressed()) {
         pl = pl == 0 ? 1 : 0;
       }
                     
       // new enemy position
       ec -= level + 1;
       
       // if enemy have just passed
       if (ec < 0) {
         score += 1;
         
         if ((score % threshold) == 0) {
           level += 1;
           show_level(level);
           break;
         }
         
         // put enemy again (right)
         ec = 17; 
                 
         // new enemy line
         el = random(0, 2);
       }
           
       // drawings ----------------------------------------------------------       
       // player
       lcd.setCursor(0, pl);
       lcd.write(">");
       
       // enemy
       lcd.setCursor(ec, el);
       lcd.write("<");

       // score
       lcd.setCursor(16 - get_digits(score), 0);     
       lcd.print(score, 10);  
       
       delay(200); 
     }
  }
  delay(500);
}
