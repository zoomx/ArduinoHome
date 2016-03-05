//DigitalPinsLoop
//Taken somewhere


int del=50; // sets a default delay time
int top = 13;
int bottom = 2;
int state = HIGH;
void setup() {
  Serial.begin(9600);
  Serial.println("DigitalPinsLoop");
  // initialize the digital pins as outputs:
  for (int i = bottom; i<=top ; i++) {
    pinMode(i, OUTPUT);
  } // end of for loop
}

void loop() {

  // Cylon Scanner
  for (int i = bottom; i<=top; i++) { 
    digitalWrite(i, state);
    delay(del);
    if(i < top) {
      digitalWrite(i, !state);
    }
  }
  for (int i = top; i>=bottom; i--) { // blink from LEDs 2 to 12
    digitalWrite(i, state);
    delay(del);
    if(i > bottom) {
      digitalWrite(i, !state);
    }
  }
}



