//CylonScanner03
//http://www.hobbytronics.co.uk/arduino-tutorial4-cylon
/*
  Simple Cylon
 Cylon Eye sweep using 5 LEDs
 
 */

unsigned char upDown=1;	// start off going UP	
unsigned char cylon=0;  // determines which LED is on 0 to 4

void setup() {
  Serial.begin(9600);
  Serial.println("CylonScanner03");  
  // initialize the digital pins as outputs.
  DDRB = B00011111;  // sets Arduino port B pins 0 to 4 as outputs	   
}

void loop() {
  if(upDown==1){
    cylon++;
    if(cylon>=4) upDown=0;      // Reached max LED, next time we need to go down
  }
  else {
    cylon--;
    if(cylon==0) upDown=1;      // Reached min LED, next time we need to go up
  }
  PORTB = 1 << cylon;
  delay(150);              // wait for a second
}


