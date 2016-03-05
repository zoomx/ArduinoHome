Donkey Godge game for Arduino
=============================

Simple but cool game for your Arduino, NES controller and 1602 LCD display! You drive a car on road full of donkeys, you can only hit 3 before your car is totaled, how far can you get?

Read this before usage: 
-----------------------

You will need:
- 16x2 LDC display, compatible with LiquidCrystal library
- Nintendo Entertainment System (NES) Controller
- piezoelectric buzzer (optional)

Before use, please see config.h file and modify pin configurations!

NES Controller's connector pin diagram:

	|-------\
	| 1 2 3  \
	| 4 5 6 7 |
	|---------|

    1-2 [unused]
	3 - +5V
	4 - SERIAL
	5 - LATCH
	6 - CLOCK
	7 - GND
