Arduino Two-in-One Project
====================

If you're new to Arduino, read the [Getting Started with Arduino](http://arduino.cc/en/Guide/HomePage) guide.

## Hardware
- [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno)
- Photocell
- [Temperature Sensor (TMP36)](http://www.digikey.ca/product-detail/en/TMP36GT9Z/TMP36GT9Z-ND/820404)
- [2x16 character LCD module](http://www.newhavendisplay.com/nhd0216bzflybw-p-1117.html) ([datasheet](http://www.newhavendisplay.com/specs/NHD-0216BZ-FL-YBW.pdf))

## Description
This project has two functions. The first function displays photocell and temperature sensor data on the LCD. The second function is a simple game on the LCD with a single button as input. The goal of the game is to avoid the oncoming obstacles by timing your jumps correctly (press the button at the right time). The program starts in the game and will switch to displaying sensor information after a certain amount of idle time. Press the button once to switch back to the game.

## Setting Up
Install the LCD library by moving the "lcd" folder into your Arduino libraries directory. On Windows, the default is ```C:\Users\<User Name>\Documents\Arduino\libraries```

Connect the components according to the schematic twoinone.pdf

Upload the twoinone sketch to your Arduino Uno with the Arduino IDE and enjoy!