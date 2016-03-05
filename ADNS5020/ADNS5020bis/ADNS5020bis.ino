// include the SPI library: 
#include <SPI.h> 
//http://www.wildcircuits.com/2013/03/optical-mouse-hacking.html
//ADNS5020bis
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
  Serial.println("ADNS5020bis");
  delay(1000);
  Serial.println("startup complete");
}

void loop(){
  unsigned int read_data;

  //enable ADNS
  digitalWrite(nReset,HIGH);
  delay(100);

  pixel_grab();
  //  delay(1000);  

  //  while(1){
  //    delay(100);
  //    Serial.println(String(squal()));
  //  }
  /*
  while(1){
   unsigned int motion = 0;
   //check for movement
   //read motion register, 0x02
   motion = ADNS_read(0x02);
   if(motion > 127){
   //there has been a motion!
   //print the x and y movements
   Serial.println("X:" + String(ADNS_read(0x03)) + " Y:" + String(ADNS_read(0x04)));
   }
   
   }
   */
}

unsigned int squal(){
  //squal is address 0x05
  return(ADNS_read(0x05));
}

void pixel_grab(){
  //address = 0x0b
  int xcount=0;
  int count=0;

  //reset the pixel grab counter
  ADNS_write(0x0B,0x00);

  Serial.println("");  
  for (count=0;count < 225; count++){
    if (count%15 == 14){
      Serial.println(String(ADNS_read(0x0B)));
    }
    else{
      Serial.print(String(ADNS_read(0x0B)) + ",");
    }
  }
  Serial.println("");
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


