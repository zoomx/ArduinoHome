//CylonScanner07
//http://deninet.com/blog/1139/cylonduino-or-my-first-arduino-experiement
//many errors!!!!
const int ledCount = 10;    // the number of LEDs in the bar graph

int ledPins[] = { 
  2, 3, 4, 5, 6, 7,8,9,10,11 };   // an array of pin numbers to which LEDs are attached

int ledLevel = 0;
int whichWay = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("CylonScanner07");
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed = ledCount; thisLed++){    //thisLed++ forgotten??
    digitalWrite(ledPins[8], LOW);
    whichWay = -1;
    ledLevel -= 2;
  }
  if(ledLevel = 0){  //else removed
    digitalWrite(ledPins[ledLevel - whichWay], LOW);
  }

  digitalWrite(ledPins[ledLevel], HIGH);

  ledLevel += whichWay; 
  delay(50); //delay(analogRead(A0));
}



