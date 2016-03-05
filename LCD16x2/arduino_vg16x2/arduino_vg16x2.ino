/*****************************************************
  Author : Nakul Rao I
******************************************************/

#include <LiquidCrystal.h>
#include <PinChangeInt.h>

// Pin definitions for the buttons
#define UP1 A11
#define DOWN1 A12
#define RIGHT1 A13
#define LEFT1 A14
#define UP2 13
#define DOWN2 12
#define RIGHT2 11
#define LEFT2 10
#define SHOOT1 A15
#define SHOOT2 A10

LiquidCrystal lcd(43, 44, 45, 46, 47, 48);

// Define special characters for Spaceship, Missile, Obstacle and // Explosion

volatile unsigned char ship_pos_p1[2] = {0,0};
volatile unsigned char mis_pos_p1[2] = {(ship_pos_p1[0] - 1),ship_pos_p1[1]};
volatile unsigned char ship_pos_p2[2] = {15,1};
volatile unsigned char mis_pos_p2[2] = {(ship_pos_p2[0] - 1),ship_pos_p2[1]};
volatile unsigned char mis_p1 = 0;
volatile unsigned char mis_p2 = 0;
volatile unsigned char explosion_p1 = 0;
volatile unsigned char explosion_p2 = 0;

byte spaceship_p1[8] = { 
   0b11000 
  ,0b01100 
  ,0b00110 
  ,0b01111 
  ,0b01111 
  ,0b00110 
  ,0b01100
  ,0b11000}; 

byte spaceship_p2[8] = { 
   0b00011 
  ,0b00110 
  ,0b01100 
  ,0b11110 
  ,0b11110 
  ,0b01100 
  ,0b00110
  ,0b00011}; 

byte missile_p1[8] = { 
   0b00000 
  ,0b00000 
  ,0b00010 
  ,0b01111 
  ,0b01111 
  ,0b00010 
  ,0b00000
  ,0b00000}; 

byte missile_p2[8] = { 
   0b00000 
  ,0b00000 
  ,0b01000 
  ,0b11110 
  ,0b11110 
  ,0b01000 
  ,0b00000
  ,0b00000}; 

byte obstacle[8] = { 
   0b11111 
  ,0b11111 
  ,0b11111 
  ,0b11111 
  ,0b11111 
  ,0b11111 
  ,0b11111
  ,0b11111}; 

byte explode[8] = { 
   0b00100 
  ,0b10101 
  ,0b01110 
  ,0b11011 
  ,0b01110 
  ,0b10101 
  ,0b00000
  ,0b00100}; 


/* Define functions for shoot, up, down, left and right and other functions  */

// player1 shoot missile function
void shoot_p1(void){
  if(!((ship_pos_p1[0] == 0) && (ship_pos_p1[1] == 0)))
  if (mis_p1 < 1)
	    mis_p1++;
   delay(50);     
}

// player2 shoot missile function
void shoot_p2(void){
  if(!((ship_pos_p2[0] == 15) && (ship_pos_p2[1] == 1)))
	if (mis_p2 < 1)
	    mis_p2++;
   delay(50);     
}

// player1 move right function
void right(void){
	if(ship_pos_p1[1] < 1)
	   ship_pos_p1[1]++;
  delay(50);
}

// player1 move left function
void left(void){
	if(ship_pos_p1[1] > 0)
	   ship_pos_p1[1]--;
  delay(50);
}

// player1 move up function
void up(void){
  if(!((ship_pos_p1[0] == 5) && (ship_pos_p1[1] == 1)))
	if(ship_pos_p1[0] < 15)
	   ship_pos_p1[0]++;
  delay(50);
}

// player1 move down function
void down(void){
	if(ship_pos_p1[0]> 0)
	   ship_pos_p1[0]--;
  delay(50);
}

// player2 move right function
void right2(void){
	if(ship_pos_p2[1] > 0)
	   ship_pos_p2[1]--;
  delay(50);
}

// player2 move left function
void left2(void){
	if(ship_pos_p2[1] < 1)
	   ship_pos_p2[1]++;
  delay(50);
}

// player2 move up function
void up2(void){
  if(!((ship_pos_p2[0] == 10) && (ship_pos_p2[1] == 0)))
	if(ship_pos_p2[0] > 0)
	   ship_pos_p2[0]--;
  delay(50);
}

// player2 move down function
void down2(void){
	if(ship_pos_p2[0] < 15)
	   ship_pos_p2[0]++;
  delay(50);
}

// spawn player1 spaceship
void spawn_p1(void){
  lcd.setCursor(ship_pos_p1[0],ship_pos_p1[1]);
  lcd.write(1);
}

// spawn player2 spaceship
void spawn_p2(void){
  lcd.setCursor(ship_pos_p2[0],ship_pos_p2[1]);
  lcd.write(2);
}

// draw obstacles on screen
void put_obstacle(void){
  lcd.setCursor(1,0);
  lcd.write(5);
  lcd.setCursor(14,1);
  lcd.write(5);
  lcd.setCursor(6,1);
  lcd.write(5);
  lcd.setCursor(9,0);
  lcd.write(5);
}

// draw spaceships on screen
void put_spaceships(void){
  lcd.setCursor(ship_pos_p1[0],ship_pos_p1[1]);
  lcd.write(1);
  lcd.setCursor(ship_pos_p2[0],ship_pos_p2[1]);
  lcd.write(2);
}

// draw player1 missile in screen
void put_missile_p1(void){
  if(mis_pos_p1[0] > 15)
    mis_p1 = 0;
  lcd.setCursor(mis_pos_p1[0],mis_pos_p1[1]);
  lcd.write(3);
  if(mis_pos_p1[0] < 16)
    mis_pos_p1[0]++;  
}

// draw player2 missile in screen
void put_missile_p2(void){
  if(mis_pos_p2[0] <= 0)
    mis_p2 = 0;
  lcd.setCursor(mis_pos_p2[0],mis_pos_p2[1]);
  lcd.write(4);
  if(mis_pos_p2[0] > 0 && mis_pos_p2[0] < 17)
    mis_pos_p2[0]--;  
}

// player1 explosion function
void put_explosion_p1(void){
  lcd.setCursor(ship_pos_p1[0],ship_pos_p1[1]);
  lcd.write(6);
  delay(300);
  ship_pos_p1[0] = 0;
  ship_pos_p1[1] = 0;
  explosion_p1 = 0;
}

// player2 explosion function
void put_explosion_p2(void){
  lcd.setCursor(ship_pos_p2[0],ship_pos_p2[1]);
  lcd.write(6);
  delay(300);
  ship_pos_p2[0] = 15;
  ship_pos_p2[1] = 1;
  explosion_p2 = 0;
}

// detect various collisions
void detect_collision(void){
  if((mis_pos_p1[0] == 1 && mis_pos_p1[1] == 0) || (mis_pos_p1[0] == 14 && mis_pos_p1[1] == 1))
    mis_p1 == 0;
  if((mis_pos_p2[0] == 1 && mis_pos_p2[1] == 0) || (mis_pos_p2[0] == 14 && mis_pos_p2[1] == 1))
    mis_p2 == 0;
    
  if(mis_pos_p1[0] == ship_pos_p2[0] && mis_pos_p1[1] == ship_pos_p2[1])
    explosion_p2 = 1;
  if(mis_pos_p2[0] == ship_pos_p1[0] && mis_pos_p2[1] == ship_pos_p1[1])
    explosion_p1 = 1;  
  
  if(ship_pos_p1[0] == 1 && ship_pos_p1[1] == 0)
  {
    ship_pos_p1[0] = 0;
    ship_pos_p1[1] = 0;
  }
  if(ship_pos_p2[0] == 14 && ship_pos_p2[1] == 1)
  {
    ship_pos_p2[0] = 15;
    ship_pos_p2[1] = 1;
  }
}

// detect if any player has won
void winner(void){
 if(ship_pos_p1[0] == 9)
 {
   lcd.clear(); 
   lcd.setCursor(2,0);
   lcd.print("Player1 WINS");
   lcd.setCursor(3,1);
   lcd.print("GAME OVER");
   while(1){}
 }
 if(ship_pos_p2[0] == 6)
 {
   lcd.clear(); 
   lcd.setCursor(0,0);
   lcd.print("Player2 WINS");
   lcd.setCursor(0,1);
   lcd.print("GAME OVER");
   while(1){}
 }  
}

// draw all objects on screen
void lcd_render(void){
  detect_collision();
  lcd.clear();
  put_obstacle();
  put_spaceships();
  if (explosion_p1)
     put_explosion_p1();
  if (explosion_p2)
     put_explosion_p2();
  if(mis_p1 == 1)
    put_missile_p1();
  if(mis_p2 == 1)
    put_missile_p2();  
  detect_collision();
  put_obstacle();
  put_spaceships();
}

/**************************************************************************************/

void setup(){
  // Define external interrupts for all 10 buttons
  pinMode(UP1, INPUT); 
  digitalWrite(UP1, HIGH);
  PCintPort::attachInterrupt(UP1, &up, FALLING);
  
  pinMode(DOWN1, INPUT); 
  digitalWrite(DOWN1, HIGH);
  PCintPort::attachInterrupt(DOWN1, &down, FALLING);

  pinMode(RIGHT1, INPUT); 
  digitalWrite(RIGHT1, HIGH);
  PCintPort::attachInterrupt(RIGHT1, &right, FALLING);

  pinMode(LEFT1, INPUT); 
  digitalWrite(LEFT1, HIGH);
  PCintPort::attachInterrupt(LEFT1, &left, FALLING);
  
  pinMode(SHOOT1, INPUT); 
  digitalWrite(SHOOT1, HIGH);
  PCintPort::attachInterrupt(SHOOT1, &shoot_p1, FALLING);
  
  pinMode(UP2, INPUT); 
  digitalWrite(UP2, HIGH);
  PCintPort::attachInterrupt(UP2, &up2, FALLING);
  
  pinMode(DOWN2, INPUT); 
  digitalWrite(DOWN2, HIGH);
  PCintPort::attachInterrupt(DOWN2, &down2, FALLING);

  pinMode(RIGHT2, INPUT); 
  digitalWrite(RIGHT2, HIGH);
  PCintPort::attachInterrupt(RIGHT2, &right2, FALLING);

  pinMode(LEFT2, INPUT); 
  digitalWrite(LEFT2, HIGH);
  PCintPort::attachInterrupt(LEFT2, &left2, FALLING);
  
  pinMode(SHOOT2, INPUT); 
  digitalWrite(SHOOT2, HIGH);
  PCintPort::attachInterrupt(SHOOT2, &shoot_p2, FALLING);
  
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  // Start message
  lcd.setCursor(3,0);
  lcd.print("Beginning");
  lcd.setCursor(5,1);
  lcd.print("GAME");
  delay(5000);
  lcd.clear();
  
  // Create spaceships for player1 and player2
  lcd.createChar(1, spaceship_p1);
  lcd.createChar(2, spaceship_p2);  
  
  // Create missiles for player1 and player2
  lcd.createChar(3, missile_p1);
  lcd.createChar(4, missile_p2);

  // Create obstacle
  lcd.createChar(5, obstacle);
  
  //Create Explosion
  lcd.createChar(6, explode);  
  
  // Spawn player1 spaceship
  spawn_p1();
  
  // Spawn player2 spaceship
  spawn_p2();

  // Add obstacles
  put_obstacle();
  
  delay(3000);
}

void loop(){
  if(mis_p1 == 0)
  {
    mis_pos_p1[0] = (ship_pos_p1[0] + 1);
    mis_pos_p1[1] = ship_pos_p1[1];
  }

  if(mis_p2 == 0){
    mis_pos_p2[0] = (ship_pos_p2[0] - 1);
    mis_pos_p2[1] = ship_pos_p2[1];
  }

  lcd_render();
  winner();
  delay(100);
}

