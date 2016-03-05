/*
TVout-Oscilloscope, v1.1

by wullschj (Juerg)
http://forum.arduino.cc/index.php?topic=64327

Lets you display the voltage on analog pin A0 on your TV using the TVout Library.

It displays the average, the minimal and the maximal voltage, and the sampling
frequency. 100 sample points are displayed.

The maximal sampling frequency is about 140kHz (on an Arduino Uno). Note that at higher
frequencies, the measurement is less accurate.

Add a button to digital pin 2 to scale the voltage range, and to digital pin 3
to scale the sample range.


v1.1: increased the max. sampling frequency from about 8kHz to about 140kHz.
(Code to read analog input fast is based on code by Anatoly Kuzmenko.)


(c) Juerg Wullschleger 2011.

http://creativecommons.org/licenses/by/3.0/

Canges by Zoomx 2015 06 02
Added link to the original Arduino forum topic
Changed to PAL

*/

#include <TVout.h>
#include <font4x6.h>

//input pins
const int scalePin = 2;
const int samplePin = 3;
// analog input pin is fixed to 0

// define the graph area
const int graphOffsetX = 18;
const int graphOffsetY = 94;
const int graphWidth = 100;
const int graphHeight = 86;

const int upperGraphLimit = graphOffsetY + 1;
const int lowerGraphLimit = graphOffsetY - graphHeight;

int scaleFactor = 1024 / graphHeight + 1;
int offset = 0;
int sampleSize = -4;
// if sampleSize <= 0, it denotes the sampling speed.

int minValue, maxValue, avgValue;
long startTime = 0, sampleTime = 0;

//used if sampleSize <=3 to draw faster
int data[graphWidth];
uint8_t dispY[graphWidth];

TVout TV;

void setup() {
  pinMode(scalePin, INPUT);
  pinMode(samplePin, INPUT);

  //init TV
  TV.begin(_PAL, 120, 96);
  TV.select_font(font4x6);

  clearGraph();
  drawScale();
}

void initADC(int speed) {
  // speed == 1: normal analogread.
  // speed in [-4,0]: faster (-4 is the fastest)

  ADCSRA = 0x87; //default
  if ( speed >= 1 ) ADCSRA = 0x87;   // turn on adc, freq  = 1/128,  125 kHz.
  if ( speed == 0 ) ADCSRA = 0x86;   // turn on adc, freq  = 1/64,   250 kHz.
  if ( speed == -1 ) ADCSRA = 0x85;   // turn on adc, freq  = 1/32,   500 kHz.
  if ( speed == -2 ) ADCSRA = 0x84;   // turn on adc, freq  = 1/16 ,    1 MHz.
  if ( speed == -3 ) ADCSRA = 0x83;   // turn on adc, freq  = 1/8,      2 MHz.
  if ( speed == -4 ) ADCSRA = 0x82;   // turn on adc, freq  = 1/4,      4 MHz.
  // does not seem to work:
  // if ( speed == -5 ) ADCSRA = 0x81;   // turn on adc, freq  = 1/2,      8 MHz.

  ADMUX = 0x40;
  ADCSRA |= (1 << ADSC);
  while (!(ADCSRA & 0x10));
}

void resetADC() {
  ADCSRA = 0x00;
}

void readFast(int speed) {
  // fills array with data on analog-pin 0.
  // speed >= 1: sample "speed" times and take the adverage.
  // speed in [-4,0]: read faster (-4 is the fastest)

  int * data_ptr = data; // pointer to array

  volatile char i = graphWidth; // iterator in array, init with array size
  volatile int val = 0, sum;

  initADC(speed);

  startTime = micros(); // set startTime here, to get a more accurate rate
  if (speed > 1) {
    ADCSRA |= (1 << ADSC); // start reading the first value
    do {
      sum = 0;
      for (int j = 0; j < speed; j++) {
        while (!(ADCSRA & 0x10)); // wait for output
        val = ADCL;  // read out low data bits
        val += (ADCH << 8); // read out high data bits
        ADCSRA |= (1 << ADSC); // already start reading the next value for more speed
        sum += val;
      }
      *data_ptr++ = sum / speed;
    } while (--i);
  } else {
    ADCSRA |= (1 << ADSC); // start reading the first value
    do {
      while (!(ADCSRA & 0x10));
      val = ADCL;
      val += (ADCH << 8);
      ADCSRA |= (1 << ADSC); // already start reading the next value for more speed
      *data_ptr++ = val;
    } while (--i);
  }
  resetADC();
}

void waitFor(int speed, int threshold) {
  volatile int val = 0;

  initADC(speed);

  boolean wasLow = false;
  ADCSRA |= (1 << ADSC); // start reading first value
  for (int w = 0 ; w < 400 ; w++) {
    while (!(ADCSRA & 0x10));
    val = ADCL;
    val += (ADCH << 8);
    ADCSRA |= (1 << ADSC); // already start reading next value for more speed
    if (val < threshold) {
      wasLow = true;
    } else if ((val > threshold) && wasLow) {
      break;
    }
  }
  resetADC();
}

/* not used anymore

int readAnalog(){
// replaces analogRead(0)
// pretty slow because we init each time we use it.

  volatile int val = 0;

  initADC(1);

  ADCSRA |= (1<<ADSC);
  while(!(ADCSRA & 0x10));
  val = ADCL;
  val += (ADCH << 8);

  resetADC();

  return val;
}
*/

void drawPixel(int x, int y, char c) {
  if ((y > lowerGraphLimit) && (y < upperGraphLimit)) {
    TV.set_pixel(x, y, c);
  }
}

int val2y(int val) {
  return graphOffsetY - val / scaleFactor - offset;
}

void drawScale() {
  //delete old scale
  TV.draw_rect(0, lowerGraphLimit, graphOffsetX - 2, graphHeight + 1, 0, 0);

  for (int i = 0; i <= 20; i++) {
    int y = val2y(1024 * i / 20);
    drawPixel(graphOffsetX - 2, y, 1);
    if ((i % 2 != 0) && (scaleFactor < 8) && (y > lowerGraphLimit + 3) && (y < upperGraphLimit - 3)) {
      TV.print(graphOffsetX - 18, y - 3, i / 4.0, 2);
    }
    if (i % 2 == 0) {
      drawPixel(graphOffsetX - 3, y, 1);
      if ((i % 4 != 0) && (scaleFactor <= 8) && (y > lowerGraphLimit + 3) && (y < upperGraphLimit - 3)) {
        TV.print(graphOffsetX - 15, y - 3, i / 4.0, 1);
      }
    }
    if (i % 4 == 0) {
      drawPixel(graphOffsetX - 4, y, 1);
      drawPixel(graphOffsetX - 5, y, 1);
      if ((y > lowerGraphLimit + 3) && (y < upperGraphLimit - 3)) {
        TV.print(graphOffsetX - 9, y - 3, i / 4);
      }
    }
  }
}

void clearGraph() {
  TV.draw_rect(graphOffsetX - 1, graphOffsetY - graphHeight, graphWidth + 1, graphHeight + 1, 1, 0);
}

void drawData(int i, int val) {
  // we use dispY[i] to store the displayed pixel. so we only need to
  // erase that pixel, and not the whole column.
  int y = val2y(val);
  int x = i + graphOffsetX;
  drawPixel(x, dispY[i], 0);
  drawPixel(x, y, 1);
  dispY[i] = y;
}

void drawData(int i, int v1, int v2) {
  int u = val2y(v1);
  int v = val2y(v2);
  int x = i + graphOffsetX;
  TV.draw_column(x, graphOffsetY, graphOffsetY - graphHeight + 1, 0);
  u = min(max(u, lowerGraphLimit), upperGraphLimit);
  v = min(max(v, lowerGraphLimit), upperGraphLimit);
  TV.draw_column(x, u, v, 1);
}

void changeScaleFactor() {
  int i = 1;
  while (i < scaleFactor)
    i = i * 2;
  scaleFactor = i / 2;
  if (scaleFactor == 0) {
    scaleFactor = 1024 / graphHeight + 1;
  }
  offset = graphHeight / 2 - avgValue / scaleFactor;

  // we need: 0/scaleFactor + offset >= 0 and 1024/scaleFactor + offset <= graphHeight
  offset = max(graphHeight - 1024 / scaleFactor, offset);
  offset = min(0, offset);

  drawScale();
  clearGraph();
}

void changeSampleSize() {
  if (sampleSize < 5)
    sampleSize = sampleSize + 1;
  else
    //sampleSize = sampleSize * 2;
    sampleSize = sampleSize * 8 / 5;
  if (sampleSize > 300) {
    sampleSize = -4;
  }
  sampleTime = 0;
  clearGraph();
}

boolean scaleButtonPressed = false, sampleButtonPressed = false;
boolean checkButtons() {
  if (digitalRead(scalePin) == HIGH) {
    scaleButtonPressed = true;
  } else {
    if (scaleButtonPressed) {
      changeScaleFactor();
      scaleButtonPressed = false;
      return true;
    }
  }
  if (digitalRead(samplePin) == HIGH) {
    sampleButtonPressed = true;
  } else {
    if (sampleButtonPressed) {
      changeSampleSize();
      sampleButtonPressed = false;
      return true;
    }
  }
  return false;
}

float val2volts(int val) {
  return val * 5 / 1024.0;
}

void printVolts() {
  TV.print(2, 2, val2volts(avgValue), 2);
  TV.print("V (");
  TV.print(val2volts(minValue), 2);
  TV.print("V-");
  TV.print(val2volts(maxValue), 2);
  TV.print("V)");
}

void printSampleRate() {
  long x = graphWidth;
  x = x * 1000000 / sampleTime;
  if (x > 9999) {
    TV.print(85, 2, x / 1000);
    TV.print("kHz  ");
  } else {
    TV.print(85, 2, x);
    TV.print("Hz ");
  }
  //TV.print(sampleSize);
  //TV.print("  ");
}

void loop() {
  checkButtons();

  waitFor(sampleSize, avgValue);

  minValue = 1024; maxValue = 0;
  long sum = 0;
  int i = 0;
  startTime = micros();
  while (i < graphWidth) {
    if (sampleSize <= 3) {
      //for small sampleSize, sample first and then draw
      readFast(sampleSize);
      if (sampleTime > 0)
        sampleTime = (19 * sampleTime + micros() - startTime) / 20;
      else
        sampleTime = micros() - startTime;
      i = 0;
      while (i < graphWidth) {
        int val = data[i];
        minValue = min(minValue, val);
        maxValue = max(maxValue, val);
        if (sampleSize > 0)
          sum = sum + sampleSize * val;
        else
          sum = sum + val;
        drawData(i, val);
        i++;
      }
    } else {
      //for large samleSize, do sample and draw at the same time.
      int minV = 1024, maxV = 0;
      volatile int val = 0;

      initADC(1);

      ADCSRA |= (1 << ADSC); // start reading first value
      for (int j = 0; j < sampleSize; j++) {

        while (!(ADCSRA & 0x10));
        val = ADCL;
        val += (ADCH << 8);
        ADCSRA |= (1 << ADSC); // already start reading next value for more speed

        minV = min(minV, val);
        maxV = max(maxV, val);
        sum = sum + val;
      }

      resetADC();

      drawData(i, minV, maxV);
      minValue = min(minValue, minV);
      maxValue = max(maxValue, maxV);
      i++;

      if (checkButtons()) {
        //button has been pressed. reset values.
        i = 0;
        startTime  = micros();
        minValue = 1024; maxValue = 0;
        sum = 0;
      }
      if (i == graphWidth) {
        if (sampleTime > 0)
          sampleTime = (9 * sampleTime + micros() - startTime) / 10;
        else
          sampleTime = micros() - startTime;
      }
    }
  }

  if (sampleSize > 0)
    avgValue =  sum / (graphWidth * sampleSize);
  else
    avgValue =  sum / graphWidth;

  printVolts();
  printSampleRate();
}


