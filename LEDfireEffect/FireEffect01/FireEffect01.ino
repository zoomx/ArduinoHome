// LED Fire Effect
//Taken somewhere
//Here?
//http://www.instructables.com/id/Realistic-Fire-Effect-with-Arduino-and-LEDs/
//Realistic Flickering Flame Effect with Arduino and LED's
//2015-02-05
const int ledPin1 = 9;  //in istructables 9 and 10 are swapped
const int ledPin2 = 10;
const int ledPin3 = 11;

void setup()
{
  Serial.begin(9600);
  Serial.println("FireEffect01");
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  analogWrite(ledPin1, random(120)+135);
  analogWrite(ledPin2, random(120)+135);
  analogWrite(ledPin3, random(120)+135);
  delay(random(100));
}


