//CylonScanner08
//http://learn.proto-pic.com/?p=93
//some adaptions
int spd=100;                                  //Change this to change the scanning speed.
void setup()
{
  Serial.begin(9600);
  Serial.println("CylonScanner08");
  for (int outpin = 4; outpin < 13; outpin++)  //This sets pins 7 to 13 as outputs (Less typing this way)
  {					    //
    pinMode(outpin,OUTPUT);		   //
  }					   //
}
void loop()
{
  for (int strobe = 4; strobe < 13; strobe++)  //Turn on (then off) pins 7 to 12
  {
    digitalWrite(strobe,HIGH);
    delay(spd);
    digitalWrite(strobe,LOW);
  }
  for (int strobe = 12; strobe > 4; strobe--)  //Turn on (then off) pins 13 to 8
  {
    digitalWrite(strobe,HIGH);
    delay(spd);
    digitalWrite(strobe,LOW);
  }
}


