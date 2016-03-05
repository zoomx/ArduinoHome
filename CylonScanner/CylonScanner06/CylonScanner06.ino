//CylonScanner06
//http://www.instructables.com/id/Arduino-Cylon-Scanning-Eye-2/
//https://github.com/snubs/Arduino/blob/master/Cylon1 (a copy)
int ledPins[] = {
  2,3,4,5,6,7,8,9,10,11,12 };                                              // make an array of the pin numbers
int pinCount = 11;                                                              // variable for number of LEDs
int timer = 10;                                                                      // delay in between LED on and off

void setup() {
  Serial.begin(9600);
  Serial.println("CylonScanner06");
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {    //for loop to setup all of the pins in the array ledPins
    pinMode(ledPins[thisPin], OUTPUT);
  }

}

void loop() {
  for(int thisPin = 0; thisPin < pinCount; thisPin++) {         //for loop to go through all LEDs in array and turn them on
    timer = analogRead(A0) / 2;                                             //and off until end of line in one direction
    digitalWrite(ledPins[thisPin], HIGH);
    digitalWrite(ledPins[thisPin] +1, HIGH);
    digitalWrite(ledPins[thisPin] + 2, HIGH);
    delay(timer);
    timer = analogRead(A0) / 2;                                 // Read the potentiometer value and divide by two to get delay
    digitalWrite(ledPins[thisPin], LOW);
    digitalWrite(ledPins[thisPin] + 1, LOW);
    digitalWrite(ledPins[thisPin] + 2, LOW);
    timer = analogRead(A0) / 2;

  }

  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {   //for loop to go through all LEDs again in opposite direction
    timer = analogRead(A0) / 2;
    digitalWrite(ledPins[thisPin], HIGH);
    digitalWrite(ledPins[thisPin] - 1, HIGH);
    digitalWrite(ledPins[thisPin] - 2, HIGH);
    delay(timer);
    timer = analogRead(A0) / 2;
    digitalWrite(ledPins[thisPin], LOW);
    digitalWrite(ledPins[thisPin] - 1 , LOW);
    digitalWrite(ledPins[thisPin] - 2, LOW);
    timer = analogRead(A0) / 2;
  }
}


