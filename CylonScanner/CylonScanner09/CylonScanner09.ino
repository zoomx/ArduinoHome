//CylonScanner09
//http://www.instructables.com/id/8-LED-Larson-Scanner-with-Arduino/

const int buttonPin = 2;
const int ledPin1 = 13;
int buttonState = 0;

int leds[] = {
  3, 4, 6, 7, 8, 9, 10, 11};
#define NUMBER_OF_LEDS (sizeof(leds)/sizeof(int))

boolean larson[][NUMBER_OF_LEDS] = {
  { 
    HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW    }
  ,
  { 
    LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW    }
  ,
  { 
    LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW    }
  ,
  { 
    LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW    }
  ,
  { 
    LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW    }
  ,
  { 
    LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW    }
  ,
  { 
    LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW    }
  ,
  { 
    LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH    }
  ,
  { 
    LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW    }
  ,
  { 
    LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW    }
  ,
  { 
    LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW    }
  ,
  { 
    LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW    }
  ,
  { 
    LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW    }
  ,
  { 
    LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW    }
  ,
};

#define FRAMES (sizeof(larson)/(sizeof(larson[0])))


int sensorPin = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("CylonScanner09");
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin, INPUT);
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    pinMode(leds[led], OUTPUT);
  }
}

void loop(){

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin1, HIGH);
  }
  else {

    long time = millis();

    for (int frame=0; frame<FRAMES; frame++) {
      for (int led=0; led<NUMBER_OF_LEDS; led++) {
        digitalWrite(leds[led], larson[frame][led]);
      }
      int sensorValue = map(analogRead(sensorPin), 0, 1023, 0, 1000);
      while (sensorValue >= (millis() - time)) {
        sensorValue = analogRead(sensorPin);
      }
      time = millis();
    }
  }

}


