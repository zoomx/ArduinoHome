/* Arduino Synth v 0.1
This is code for a sound synthesizer built with an Arduino.

Features
4 LEDs indicate 1 of 16 programs (voices) indicated by 4 LED's with binary encoding
Plays scales or tunes determined by arrays.
Cheap, fun, and you get to program it yourself.

So far there's not too much implemented to change the timbre of sounds and it outputs
square waves. There is a "phase control" though that changes the duty cycle of the square wave
which does a little something in this direction.

There are 3 pins resevered for a future R2R ladder for D-A conversion. Even a two-bit digital sine wave sounds
much mellower than a square wave, so this seems like promising future work.

http://playground.arduino.cc/Main/PbSynthCode
*/

#include <math.h>

#define outpin  4   // hook up this pin to audio out in series with a 1 uf cap and 1k resistor.
#define outpin1 5   // pins reserved for future 4 bit R2R 
#define outpin2 6
#define outpin3 7

// analog inputs, these number are for the analog pin inputs A0, A1 etc
// use 5 - 50k pots. Looking at the pot shaft,  with pot leads facing up, hook up left leads to +5V,
// middle terminals to A0, A1 etc, and right terminals to ground
#define pitchPot 0
#define modPot   1
#define speedPot 2
#define phasePot 3
#define jukePot  4

#define stopPin 8   // this is the "break" switch - to break out of long loops - enables retriggering scales, tunes etc
// one side of single pole pushbutton switch to pin 8, other side to ground

#define LEDbit0 10  // LED's for program selection indication - hook up LED with long lead 
#define LEDbit1 11  // facing the pin and a 1k series resistor to ground
#define LEDbit2 12
#define LEDbit3 13

int randomWalkLowRange;   // for random walk function
int randomWalkHighRange;

int val, runlevel;
volatile int encoder0PinA = 2;   // pins for A & B channel of the encoder
volatile int encoder0PinB = 3;   // hook up encoder middle terminal to ground
// hook up A &  B channels (end leads of encoder) to pins 2 & 3 with 1 uf (105) caps to ground
volatile unsigned int encoder0Pos = 0;
int n = LOW;

int ptime, range, strt, inc;
int   k,  x, dur, freq, t;
int i, j;
int sens, adder;

float ps, fpitch;         // variable for pow pitchShift routine

float noteval;
//note values
float A     = 14080;
float AS    = 14917.2;
float B     = 15804.3;
float C     = 16744;
float CS    = 17739.7;
float D     = 18794.5;
float DS    = 19912.1;
float E     = 21096.2;
float F     = 22350.6;
float FS    = 23679.6;
float G     = 25087.7;
float GS    = 26579.5;
float A22    = 28160;    //A2 changed in A22 A2 is Analog 2
float A2S   = 29834.5;
float B2    = 31608.5;
float C2    = 33488.1;
float C2S   = 35479.4;
float D2    = 37589.1;
float D2S   = 39824.3;
float E2    = 42192.3;
float F2    = 44701.2;
float F2S   = 47359.3;
float G2    = 50175.4;
float G2S   = 53159;
float A33    = 56320;    //A3 changed in A33 A3 is Analog 3
//rhythm values
int wh = 1024;
int h  = 512;
int dq = 448;
int q = 256;
int qt = 170;
int de = 192;
int e = 128;
int et = 85;
int dsx = 96;
int sx = 64;
int thx = 32;



float majScale[] = {
  A,  B,  CS,  D,  E,  FS,  GS,  A22,   B2,  C2S,  D2,  E2,  F2S,  G2S,  A33
};

float minScale[] = {
  A,  B,  C,  D,  E,  F,  GS,  A22,   B2,  C2,  D2,  E2,  F2,  G2S,  A33
};

float creme[] =  {    // make sure this array and the following one have same number of entries - bottom array is time values
  A,  CS,  D, CS,  D,  E,  CS,  D,   CS,  B,   A
};
float cremeDur[] = {
  q,  q,  qt, qt,  qt,  q,  q,  qt,   qt, qt,  q
};

void setup() {
  pinMode(outpin, OUTPUT);

  pinMode(9, OUTPUT);   //R2R pins to output
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);

  pinMode(LEDbit0, OUTPUT);
  pinMode(LEDbit1, OUTPUT);
  pinMode(LEDbit2, OUTPUT);
  pinMode(LEDbit3, OUTPUT);

  pinMode(stopPin, INPUT);
  digitalWrite(stopPin, HIGH);   // turn on pullups

  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);   // turn on pullups
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);   // turn on pullups

  attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  Serial.println("start");

  pinMode(outpin, INPUT); // turn off audio out
}


void loop() {


  runlevel = encoder0Pos;
  switch (runlevel) {
    case 0:

    case 1:
      doJoker1();
      break;
    case 2:
      doScale2();
      break;
    case 3:
      doArp3();
      break;
    case 4:
      doCreme4();
      break;
    case 5:
      doCreme5();
      break;
    case 6:
      doScale6();
      break;

  }
}

//*******************************************************
void doJoker1() {
  sens = analogRead(pitchPot);
  //sens =500;  // hardwire for testing
  adder = max((sens / 5), 1);

  for (x = sens; x <= (sens + (analogRead(speedPot) * 5)) ; x += analogRead(jukePot)) {
    if ( digitalRead(stopPin) == 0) {
      break;
    }
    noteval = x;    // transpose scale up 12 tones - pow function generates transpostion
    dur = 100;
    freqout((int)noteval, sens / 47);

    // delay(10);
  }
  delay(analogRead(modPot));
}
// endJoker1 ****************************************************
/*void arp2(){
 sens = analogRead(pitchPot);
 range = abs(512 - sens) * 4.0;
 strt =  sens * 1;
 inc=abs(512 - sens);
 if (inc == 0){
 inc = 1;
 }

 for (x=strt; ( x > (strt / 4)) && (x < (inc * 30)); x* = (1 + ((sens - 512) / 1023.00))){
 noteval = x;    // transpose scale up 12 tones - pow function generates transpostion
 dur = 100;
 freqout((int)noteval, inc);

 //   if ((abs(sens - analogRead(0))) > 2){ break;}
 }
 delay(analogRead(modPot);
 }  */

// end  ***************************************************

void doScale2() {
  ps = ((float)analogRead(jukePot)) * 24.0 / 1023.0;         // choose new transpose interval every loop
  for (x = 0; x <= 15; x++) {
    if ( digitalRead(stopPin) == 0) {
      break;
    }
    noteval = (majScale[x] / (float)(analogRead(pitchPot))) * pow(2, ps);   // transpose scale up 12 tones - pow function generates transpostion
    dur = analogRead(speedPot);
    freqout((int)noteval, dur);

    delay(analogRead(modPot));
  }
}

/****************************************************/

void doArp3() {
  Serial.println("arp");

  fpitch = (float)analogRead(pitchPot) / 64;
  Serial.print("fpitch = ");
  Serial.println(fpitch, DEC);
  if (fpitch == 0) {
    fpitch = 1;
  }
  strt = pow(2, fpitch);
  Serial.print("strt = ");
  Serial.println(strt, DEC);

  for (x = strt; x <= strt * 4; strt = (strt * ( 1 + ((float)analogRead(jukePot) / 1023)))) {
    if ( digitalRead(stopPin) == 0) {
      break;
    }
    dur = analogRead(speedPot);
    freqout(strt, dur);
    delay(analogRead(modPot));
  }
}
/****************************************************/
void doCreme4() {
  randomWalkLowRange = 0;
  randomWalkHighRange = 10;

  i = randomWalk(analogRead(speedPot) / 32);
  noteval = creme[i] / ((float)analogRead(pitchPot));
  dur = ((cremeDur[i] * (float)analogRead(jukePot)) / 64.0);
  freqout(noteval, dur);
  delay(analogRead(modPot));
}
/****************************************************/

void doCreme5() {
  int LowRange = 0;
  int HighRange = 10;

  for (x = 0; x <= HighRange; x++) {

    if ( digitalRead(stopPin) == 0) {
      break;
    }

    noteval = creme[x] * 2 / ((float)analogRead(pitchPot));
    dur = ((cremeDur[x] * (float)analogRead(speedPot)) / 64.0);
    freqout(noteval, dur);
    delay(analogRead(modPot));
  }
}
/****************************************************/

void doScale6() {
  int LowRange = 0;
  int HighRange = 14;

  for (x = 0; x <= HighRange; x++) {

    if ( digitalRead(stopPin) == 0) {
      break;
    }

    noteval = minScale[x] * 2 / ((float)analogRead(pitchPot));
    dur = (4 * analogRead(speedPot));
    freqout(noteval, dur);
    delay(analogRead(modPot));
  }
}

int randomWalk(int moveSize) {
  static int  place;     // variable to store value in random walk - declared static so that it stores
  // values in between function calls, but no other functions can mess with its value

  place = place + (random(-moveSize, moveSize + 1));

  if (place < randomWalkLowRange) {                   // check lower and upper limits
    place = place + (randomWalkLowRange - place);     // reflect number back in positive direction
  }
  else if (place > randomWalkHighRange) {
    place = place - (place - randomWalkHighRange);     // reflect number back in negative direction
  }

  return place;
}




void freqout(int freq, int t)
{
  //calculate 1/2 period in us
  unsigned int cycles;
  long  i, hperiod;
  long highPeriod, lowPeriod;
  int phase;

  t = max(t, 1);                               // check to prevent 0 time
  hperiod = (500000 / freq) - 7;             // subtract 7 us to make up for digitalWrite overhead - determined empirically
  phase = analogRead(phasePot);
  highPeriod = hperiod *  phase / 1023;
  lowPeriod =  ((hperiod * (1023 - phase)) / 1023) - 1;  // - 1 to make up for fractional microsecond in digitaWrite overhead
  // calculate cycles
  cycles = ((long)freq * (long)t) / 1000;    // calculate cycles

  if (highPeriod <= 0 || lowPeriod <= 0) {
    pinMode(outpin, INPUT);
    return;
  }

  pinMode(outpin, OUTPUT);                   // turn on output pin


  for (i = 0; i <= cycles; i++) {          // play note for t ms
    digitalWrite(outpin, HIGH);
    delayMicroseconds(highPeriod);
    digitalWrite(outpin, LOW);
    delayMicroseconds(lowPeriod);
  }
  pinMode(outpin, INPUT);                // shut off pin to avoid noise from other operations
}

void doEncoder() {
  if (digitalRead(encoder0PinA) == HIGH) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = (encoder0Pos - 1 ) % 16;
    }
    else {
      encoder0Pos = (encoder0Pos + 1 ) % 16;
    }
  }
  else
  {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = (encoder0Pos + 1 ) % 16;
    }
    else {
      encoder0Pos = (encoder0Pos - 1 ) % 16;
    }

  }
  PORTB = PORTB & (B000011);  // clear out LED bits
  PORTB = PORTB | (encoder0Pos << 2);  // light up channel LED's
  //  Serial.print (encoder0Pos, DEC);
  //  Serial.print ("/");
}
