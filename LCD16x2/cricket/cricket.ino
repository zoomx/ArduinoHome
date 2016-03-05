//catch out  -> increase playerNumber untill 11 players not out increase ball.
//stamp out  -> increase playerNumber untill 11 players not out increase ball.
//bold out   -> increase playerNumber untill 11 players not out increase ball.
//leg by     -> increase playerNumber untill 11 players not out increase ball.
//single run -> increase run variable by one increase ball..
//two run    -> increase run variable by two increase ball.
//three run  -> increase run variable by two increase ball.
//four run   -> increase run variable by four increase ball..
//sixers     -> increase run variable by six increase ball..
//wide ball  -> increase run variable by one.

//game over conditions, all player out , all balls out.
//win condition runs > computer runs
//computer run is randomly between 10 - 40 easy
//computer run is randomly between 40 - 100 medium
// computer run is randomly between 100 - 120
#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 7, 10, 11, 12, 13);
int playerNumber = 1 ;//varry from 0- 11
int run = 0;
int ball = 1; //total number of balls given = 20;
int parameters ;// catchout, stampout, boldout, legby, singlerun, tworun, threerun, fourrun, six, wideball
int playGamePin = 45; //set this to switch pin number of arduino
int easyPin = 43;    
int hardPin = 44;
int mediumPin = 42;
int resetPin = 40;
int computerScore;
int flag = 0;
int flagCondn = 0;
boolean currentStatePlayGamePin = LOW;
boolean lastStatePlayGamePin = LOW;
boolean currentStateResetPin = LOW;
boolean lastStateResetPin = LOW;
boolean currentStateEasyPin = LOW;
boolean lastStateEasyPin = LOW;
boolean currentStateMediumPin = LOW;
boolean lastStateMediumPin = LOW;
boolean currentStateHardPin = LOW;
boolean lastStateHardPin = LOW;

void toss(){
	int a = random(0, 2);
	if(a == 0) print
}

void setup()
 {
  pinMode(playGamePin, INPUT);
  pinMode(resetPin, INPUT);
  pinMode(easyPin, INPUT);
  pinMode(mediumPin, INPUT);
  pinMode(hardPin, INPUT);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  welcomeNote();
 }

void boldOut()
 {
  playerNumber ++;
  ball++;
    lcd.setCursor(0, 0);
       

    lcd.print("BOLD!!  RUN:");
    lcd.print(run);
     lcd.print("                ");
    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.println(playerNumber-1);
    lcd.print("                ");

  Serial.println("BOLD!! ");
  Serial.println(run);

 }

void stampOut()
 {

  playerNumber ++;
  ball++;
     lcd.setCursor(0, 0);

    lcd.print("STUMPd! RUN:");
    lcd.print(run);
             lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.println(playerNumber-1);
            lcd.print("                ");

     Serial.println("Stump oUt!! ");
  Serial.println(run);
  //  printBoldOut(); write here only code to print boldOut
 }

void catchOut()
 {
  
  playerNumber ++;
  ball++;
     lcd.setCursor(0, 0);

    lcd.print("CAUGHT! RUN:");
    lcd.print(run);
             lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

     Serial.println("caught !! ");
  Serial.println(run);
  // lcd.print(run);
  // lcd.setCursor(0, 0);
  //print here catch out game over 
 }

void legby()
 {
  run++;
  ball++;
     lcd.setCursor(0, 0);

    lcd.print("LeGbY!!  RUN:");
    lcd.print(run);
             lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

     Serial.println("leg by!! ");
  Serial.println(run);
  // lcd.print(run);
  // lcd.setCursor(0, 0);
 }

void singlerun()
 {
  run++;
  ball++;
     lcd.setCursor(0, 0);

    lcd.print("1 Run!!  RUN:");
    lcd.print(run);
             lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

     Serial.println("1 run!! ");
  Serial.println(run);
  // lcd.print(run);
  // lcd.setCursor(0, 0);
 }

void tworun()
 {
  run += 2;
  ball ++;
   Serial.println("two run!! ");
  Serial.println(run);
    lcd.setCursor(0, 0);

    lcd.print("2 Run!!  RUN:");
    lcd.print(run);
            lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
        lcd.print("                ");

 }

void threerun()
 {
  run += 3;
  ball++;
    lcd.setCursor(0, 0);

    lcd.print("3 Run!! RUN:");
    lcd.print(run);
            lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

     Serial.println("3 run!! ");
  Serial.println(run);
 }

void fourrun ()
 {
  run += 4;
  ball++;
    lcd.setCursor(0, 0);

    lcd.print("4 Run!!  RUN:");
    lcd.print(run);
            lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

     Serial.println("4 run!! ");
  Serial.println(run);
  // lcd.print(run);
  // lcd.setCursor(0, 0);
 }

void six()
 {
  run += 6;
  ball++;
    lcd.setCursor(0, 0);

    lcd.print("6 Run!!  RUN:");
    lcd.print(run);
            lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print("  Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

     Serial.println("SIX!! ");
  Serial.println(run);
  // lcd.print(run);
  // lcd.setCursor(0, 0);
 }

void wideball()
 {
  run++;
    lcd.setCursor(0, 0);

    lcd.print("WIDE!!  RUN:");
    lcd.print(run);
            lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print(" Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

   Serial.println("wide!! ");
  Serial.println(run);
  // lcd.setCursor(0, 0);
 }

void noball()
 {
  run++;
    lcd.setCursor(0, 0);

    lcd.print("NOBALL!! RUN:");
    lcd.print(run);
            lcd.print("                ");

    lcd.setCursor(0, 1);

    lcd.print("Trgt:");
    lcd.print(computerScore);
    lcd.print(" Wkt:");
    lcd.print(playerNumber-1);
            lcd.print("                ");

   Serial.println("wide!! ");
  Serial.println(run);
  // lcd.setCursor(0, 0);
 }

void resetGame()
 {

  welcomeNote();

  run = 0; 
  playerNumber = 1;
  ball = 1;
  flag = 0;
  flagCondn = 0;
  // lcd.print(run);
  // lcd.setCursor(0, 0);
 }

bool gameOverCondition()
 {
  if((ball > 20) || (playerNumber > 11))
    return true;
 return false;
 }  

void printWin()
 
 {
  lcd.setCursor(0, 0);
  lcd.print("YOu WoN By :    ");
  lcd.setCursor(0, 1);
  lcd.print(12 - playerNumber);
  lcd.print("  WICKETSsssssssss");
  Serial.print("YOU WIN by : ");
  Serial.println(12 - playerNumber);
 }
 
void printLoose(){
  lcd.setCursor(0, 0);
  lcd.print("YOu LoSt By :    ");
  lcd.setCursor(0, 1);
  lcd.print(computerScore - run);
  lcd.print("  Runsssssssssssssssssssssss");
  Serial.print("YOU loSt by : ");
  Serial.println(computerScore - run);
 }

void welcomeNote()
 {
  lcd.setCursor(0, 0);
    lcd.println("***NiMbLe '15***");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.println("****BY ECLUB****");
    lcd.setCursor(0, 1);
    lcd.println("***E-CRICKET****");
    lcd.setCursor(0, 0);
    delay(1000);
 }

void loop(){

  lcd.noCursor();
 currentStatePlayGamePin = digitalRead(playGamePin);
 currentStateResetPin = digitalRead(resetPin);
 currentStateEasyPin = digitalRead(easyPin);
 currentStateMediumPin = digitalRead(mediumPin);
 currentStateHardPin = digitalRead(hardPin);

  if(currentStatePlayGamePin == HIGH && lastStatePlayGamePin == LOW && ball < 21 && playerNumber < 12 && flagCondn == 0){ //set constrained on player number and balls.
    delay(1); 
    // Serial.println("inside game pin");
    Serial.println("value of ball = ");
        Serial.println(ball);

    int a = random(0, 11);
    Serial.print("value of a = ");
        Serial.println(a);
        Serial.print("players =  ");
        Serial.println(playerNumber);
   
    if(a == 0)      boldOut(); 
    else if(a == 1) catchOut();
    else if(a == 2) stampOut(); // catchout, stampout, boldout, legby, singlerun, tworun, threerun, fourrun, six, wideball
    else if(a == 3) legby();
    else if(a == 4) singlerun();
    else if(a == 5) tworun();
    else if(a == 6) threerun();
    else if(a == 7) fourrun();
    else if(a == 8) six();
    else if(a == 9) wideball(); //subtract ball in function
    else if(a == 10) noball();
  }
        lastStatePlayGamePin = currentStatePlayGamePin;

  if(currentStateResetPin == HIGH && lastStateResetPin == LOW ) { resetGame(); delay(1); }// this will erase all on screen set run, playernumber, run, and display some cool stuff 
  lastStateResetPin = currentStateResetPin;
  if(currentStateEasyPin == HIGH && lastStateEasyPin == LOW && flag == 0) {
    Serial.print("inside easy");
    computerScore = random(10, 40);
    Serial.print("computer score");
    lcd.setCursor(0, 0);
    lcd.print("Comp Playing .... .... ...");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    for(int i=0; i<16; i++){
      lcd.setCursor(i, 1);
        lcd.print("....");
        delay(350);
        lcd.print("    ");
        delay(125);
    }
    lcd.setCursor(0,0);
    lcd.print("Target Score :  ");
        lcd.setCursor(0,1);

    lcd.print(computerScore);
    lcd.print("                ");
    Serial.println(computerScore); delay(1);
    flag++; 
  }
  lastStateEasyPin = currentStateEasyPin;
  if(currentStateMediumPin == HIGH && lastStateMediumPin ==LOW && flag == 0) { 
    Serial.print("inside medium");
    computerScore = random(50, 80);
    Serial.print("computer score");
    lcd.setCursor(0, 0);
    lcd.print("Comp Playing .... .... ...");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    for(int i=0; i<16; i++){
      lcd.setCursor(i, 1);
        lcd.print("....");
        delay(350);
        lcd.print("    ");
        delay(125);
    }
    lcd.setCursor(0,0);
    lcd.print("Target Score :  ");
        lcd.setCursor(0,1);

    lcd.print(computerScore);
    lcd.print("                ");
    Serial.println(computerScore);
     delay(1); 
     flag++; 
  }
 lastStateMediumPin = currentStateMediumPin;
  if(currentStateHardPin == HIGH && lastStateHardPin == LOW && flag == 0){ 
  Serial.print("inside hard");
  computerScore = random(100, 120);
  Serial.print("computer score : ");
  lcd.setCursor(0, 0);
    lcd.print("Comp Playing .... .... ...");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    for(int i=0; i<16; i++){
      lcd.setCursor(i, 1);
        lcd.print("....");
        delay(350);
        lcd.print("    ");
        delay(125);
    }
    lcd.setCursor(0,0);
    lcd.print("Target Score :  ");
        lcd.setCursor(0,1);

    lcd.print(computerScore);
    lcd.print("                ");
  Serial.println(computerScore);
  delay(1); flag++; 
 }
 lastStateHardPin = currentStateHardPin;
 
 if(run > computerScore && flagCondn == 0)
 {
    flagCondn = 1; 
    printWin();
 }
 
 else if( gameOverCondition() == true && flagCondn == 0)
 {
    flagCondn = 1;
    printLoose();
 }

}
