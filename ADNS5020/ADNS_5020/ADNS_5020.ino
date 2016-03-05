#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>

//http://frenki.net/2013/12/convert-optical-mouse-into-arduino-web-camera/

/*
byte arduinoMac[] = { 
 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 IPAddress arduinoIP(192, 168, 1, 177); // desired IP for Arduino
 unsigned int arduinoPort = 8888;      // port of Arduino
 
 IPAddress receiverIP(192, 168, 1, 102); // IP of udp packets receiver
 unsigned int receiverPort = 6000;      // port to listen on my PC
 
 EthernetUDP Udp;
 */
int SCLK = 5;
int SDIO = 6;
int NCS  = 7;

void setup() {
  Serial.begin(115200);
  //Ethernet.begin(arduinoMac,arduinoIP);
  //Udp.begin(arduinoPort);
  Serial.print("ADNS-5020-01");
  pinMode(SCLK, OUTPUT);
  pinMode(SDIO, OUTPUT);
  pinMode(NCS, OUTPUT);

  mouse_reset();
  delay(10);
}

void loop() {
  char img[225];
  for (int i=0;i<225;i++){
    img[i]=readLoc(0x0b);
    img[i] &= 0x7F;
    img[i]+=1;//if there is 0 value, part of udp package is lost
    Serial.print(img[i], DEC);
    Serial.print(",");
    delay(2);
  }  
  Serial.println();
  //Udp.beginPacket(receiverIP, receiverPort); //start udp packet
  //Udp.write(img); //write mouse data to udp packet
  //Udp.endPacket(); // end packet

  delay(500);
}

void mouse_reset(){
  // Initiate chip reset
  digitalWrite(NCS, LOW);
  pushbyte(0x3a);
  pushbyte(0x5a);
  digitalWrite(NCS, HIGH);
  delay(10);
  // Set 1000cpi resolution
  digitalWrite(NCS, LOW);
  pushbyte(0x0d);
  pushbyte(0x01);
  digitalWrite(NCS, HIGH);
}

unsigned int readLoc(uint8_t addr){
  unsigned int ret=0;
  digitalWrite(NCS, LOW);
  pushbyte(addr);
  ret=pullbyte();
  digitalWrite(NCS, HIGH);
  return(ret);
}

void pushbyte(uint8_t c){
  pinMode(SDIO, OUTPUT);
  for(unsigned int i=0x80;i;i=i>>1){
    digitalWrite(SCLK, LOW);
    digitalWrite(SDIO, c & i);
    digitalWrite(SCLK, HIGH);
  }
}

unsigned int pullbyte(){
  unsigned int ret=0;
  pinMode(SDIO, INPUT);
  for(unsigned int i=0x80; i>0; i>>=1) {
    digitalWrite(SCLK, LOW);
    ret |= i*digitalRead(SDIO);
    digitalWrite(SCLK, HIGH);
  }
  pinMode(SDIO, OUTPUT);
  return(ret);
}


