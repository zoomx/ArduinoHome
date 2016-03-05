/*
Title: The Matrix effect with TV and Arduino
Author: Ali Kazi
Date Created: 12/10/2010
Description: The program utilizes the TVout library which gives 
a very efficient way to write programs for TV and arduino related projects. 
The library includes 4 different sizes of fonts to choose from namely;
4x6, 6x8, 8x8 and 8x8ext(units in pixels). I used the 8x8 font because it is easy on the eyes. 

The program uses 3 sets of arrays; the first two specify where to print on the screen 
using x & y values while the third one prints the characters themselves.

 This example code is in the public domain. 
 */

#include <TVout.h>
//#include <pollserial.h>
#include <fontALL.h>

unsigned char a;
int i=0;

TVout TV;
//pollserial pserial;
float d = 0.0;
unsigned char x[10];
unsigned char y[10];
unsigned char c[10];
int sensorPin = A0;
int voltagePin = 2;

void setup()  {
  randomSeed(analogRead(A1));
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  TV.begin(_PAL,142,104);
  TV.select_font(font8x8);
  //TV.set_hbi_hook(pserial.begin(57600));
  
  for(a=0;a<10;a++)
  {
    a=random(10);
    x[a]=8*random(16);
    y[a]=0;
    c[a]=random(33,180);
    if (c[a] > 127) {c[a] = 32;}
    }
}

void loop() {
  digitalWrite(voltagePin , HIGH);
  d = analogRead(sensorPin);    
    for(a=0;a<10;a++){
    if (random(100) < 45) {
      x[a]=8*random(16);
      y[a]=0;
      c[a]=random(33,180);
      if (c[a] > 127) {c[a] = 32;}
    }
    TV.print(x[a],y[a],c[a]);

         if(c[a]=='T'){TV.print_char(24,40,'T');}
    else if(c[a]=='H'){TV.print_char(32,40,'H');}
    else if(c[a]=='E'){TV.print_char(40,40,'E');}
    else if(c[a]==' '){TV.print_char(48,40,' ');}
    else if(c[a]=='M'){TV.print_char(56,40,'M');}
    else if(c[a]=='A'){TV.print_char(64,40,'A');
                       TV.print_char(72,40,'T');}
         if(c[a]=='R'){TV.print_char(80,40,'R');}
    else if(c[a]=='I'){TV.print_char(88,40,'I');}
    else if(c[a]=='X'){TV.print_char(96,40,'X');}
    if(y[a]>=94){y[a]=0;}
    else {y[a]+=8;}
    }
  delay(d/8);
}
