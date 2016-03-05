// include the SPI library: 
#include <SPI.h> 
//http://www.wildcircuits.com/2013/03/optical-mouse-hacking.html
//ADNS-5020 read registers
// setup pins 
int nReset = 8;   //3 on chip
int nCS = 9; //was 13   4 on chip

//SDIO 1   MISO 12
//SDOI    MOSI 11
//SCK 8   SCLK 13

void setup(){ 
  //set pin I/O direction 
  pinMode (nReset, OUTPUT); 
  pinMode (nCS, OUTPUT); 

  //put the device in reset not chip selected 
  digitalWrite(nReset,LOW); 
  digitalWrite(nCS,HIGH); 

  //initialize SPI 
  SPI.begin(); 
  SPI.setDataMode(SPI_MODE3); 
  //start a serial port for debugging 
  Serial.begin(115200);
  Serial.println("ADNS-5020 read registers");
  delay(1000); 
  Serial.println("startup complete"); 
} 

void loop(){ 
  unsigned int read_data; 

  delay(1000); 
  //enable ADNS 
  digitalWrite(nReset,HIGH); 

  //startup time 
  delay(1000); 

  //read and print a register map 
  Serial.println("ADNS-5020 Register Map"); 
  Serial.println("Addr 0x00 - Data " + String(ADNS_read(0x00))); 
  Serial.println("Addr 0x01 - Data " + String(ADNS_read(0x01))); 
  Serial.println("Addr 0x02 - Data " + String(ADNS_read(0x02))); 
  Serial.println("Addr 0x03 - Data " + String(ADNS_read(0x03))); 
  Serial.println("Addr 0x04 - Data " + String(ADNS_read(0x04))); 
  Serial.println("Addr 0x05 - Data " + String(ADNS_read(0x05))); 
  Serial.println("Addr 0x06 - Data " + String(ADNS_read(0x06))); 
  Serial.println("Addr 0x07 - Data " + String(ADNS_read(0x07))); 
  Serial.println("Addr 0x08 - Data " + String(ADNS_read(0x08))); 
  Serial.println("Addr 0x09 - Data " + String(ADNS_read(0x09))); 
  Serial.println("Addr 0x0A - Data " + String(ADNS_read(0x0A))); 
  delay(1000);   
} 

void ADNS_write(unsigned int address, unsigned int data){ 
  // take the CS pin low to select the chip: 
  digitalWrite(nCS,LOW); 
  //  send in the address and value via SPI: 
  SPI.transfer(address); 
  SPI.transfer(data); 
  // take the SS pin high to de-select the chip: 
  digitalWrite(nCS,HIGH);  
} 

unsigned int ADNS_read(unsigned int address){ 
  unsigned int data; 
  // take the CS pin low to select the chip: 
  digitalWrite(nCS,LOW); 
  //  send in the address and value via SPI: 
  SPI.transfer(address); 

  pinMode(MOSI, INPUT); 
  data = SPI.transfer(0x00); 
  pinMode(MOSI, OUTPUT); 
  // take the SS pin high to de-select the chip: 
  digitalWrite(nCS,HIGH);  
  return(data); 
} 



