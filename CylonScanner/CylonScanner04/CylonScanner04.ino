//CylonScanner04
//http://wiki.lvl1.org/Cylon_LEDs

//code for Cylon - I am sure this could be more elegant!
//bpw 2/11/22

int pinled1 = 6; 
int pinled2 = 7; 
int pinled3 = 8;
int pinled4 = 9;
int pinled5 = 10;
int pinled6 = 11;
int pinled7 = 12;
int pinled8 = 13;
int t = 50; 
void setup() 
{
  Serial.begin(9600);
  Serial.println("CylonScanner04"); 
  pinMode(pinled1, OUTPUT);
  pinMode(pinled2, OUTPUT);
  pinMode(pinled3, OUTPUT);
  pinMode(pinled4, OUTPUT);
  pinMode(pinled5, OUTPUT);
  pinMode(pinled6, OUTPUT);
  pinMode(pinled7, OUTPUT);
  pinMode(pinled8, OUTPUT);
}

void loop() 
{
  digitalWrite(pinled1, HIGH); 
  delay(t); 
  digitalWrite(pinled2, HIGH);
  delay(t);
  digitalWrite(pinled1, LOW);
  delay(t);
  digitalWrite(pinled3, HIGH);
  delay(t);
  digitalWrite(pinled2, LOW);
  delay(t);
  digitalWrite(pinled4, HIGH);
  delay(t);
  digitalWrite(pinled3, LOW);
  delay(t);
  digitalWrite(pinled5, HIGH);
  delay(t);
  digitalWrite(pinled4, LOW);
  delay(t);
  digitalWrite(pinled6, HIGH);
  delay(t);
  digitalWrite(pinled5, LOW);
  delay(t);
  digitalWrite(pinled7, HIGH);
  delay(t);
  digitalWrite(pinled6, LOW);
  delay(t);
  digitalWrite(pinled8, HIGH);
  delay(t);
  digitalWrite(pinled7, LOW);
  delay(t);
  digitalWrite(pinled7, HIGH);
  delay(t);
  digitalWrite(pinled8, LOW);
  delay(t);
  digitalWrite(pinled6, HIGH);
  delay(t);
  digitalWrite(pinled7, LOW);
  delay(t);
  digitalWrite(pinled5, HIGH);
  delay(t);
  digitalWrite(pinled6, LOW);
  delay(t);
  digitalWrite(pinled4, HIGH);
  delay(t);
  digitalWrite(pinled5, LOW);
  delay(t);
  digitalWrite(pinled3, HIGH);
  delay(t); 
  digitalWrite(pinled4, LOW);
  delay(t);
  digitalWrite(pinled2, HIGH);
  delay(t);
  digitalWrite(pinled3, LOW);
  delay(t);
  digitalWrite(pinled1, HIGH);
  delay(t);
  digitalWrite(pinled2, LOW);
  delay(t);

}

