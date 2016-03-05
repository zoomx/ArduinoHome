//CylonScanner02
//https://raw.githubusercontent.com/lilspikey/arduino_sketches/master/larson/larson.ino
//http://www.psychicorigami.com/2012/11/01/a-quick-halloween-cylon-pumpkin-using-an-arduino-and-a-few-leds/

#define PIN_COUNT 6
#define UPDATE_DURATION 30

int pins[PIN_COUNT] = { 
  3, 5, 6, 9, 10, 11 };
int states[PIN_COUNT];
int current_pin = 0;
int dir = 1;
int update_count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("CylonScanner02");
  for ( int i = 0; i < PIN_COUNT; i++ ) {
    pinMode(pins[i], OUTPUT);
    states[i] = 0;
  }
}

void updatePins() {
  for ( int i = 0; i < PIN_COUNT; i++ ) {
    analogWrite(pins[i], states[i]);
  }
  delay(6);
}

void decay() {
  for ( int i = 0; i < PIN_COUNT; i++ ) {
    states[i] = (19*states[i]/20);
  }
}

void loop() {
  decay();
  states[current_pin] = 255 * update_count / UPDATE_DURATION;
  updatePins();

  update_count++;
  if ( update_count > UPDATE_DURATION ) {
    update_count = 0;
    current_pin += dir;
    if ( current_pin == 0 ) {
      dir = 1;
    }
    else if ( current_pin == (PIN_COUNT-1) ) {
      dir = -1;
    }
  }
}


