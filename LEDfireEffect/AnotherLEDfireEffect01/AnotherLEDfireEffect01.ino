//Another LED fire effects
//Random on intensity and delay!
//http://arduino.cc/forum/index.php/topic,56596.0.html

int ledPin1 = 6;
int ledPin2 = 7;
int ledPin3 = 8;
int ledPin4 = 9;
int ledPin5 = 10;
int ledPin6 = 11;
int ledPin7 = 12;

void setup()
{
  Serial.begin(9600);
  Serial.println("AnotherLEDfireEffect01");
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
}
void loop() {
  int Rand=random(100)+140;
  for(int lp= ledPin1;lp<= ledPin7;lp++){
    analogWrite(lp, Rand);

  } // end FOR
  delay(random(110));

}// end LOOP


