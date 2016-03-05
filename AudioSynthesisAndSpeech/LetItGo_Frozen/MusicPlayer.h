/*
* FILENAME:	MusicPlayer.h
* AUTHOR:	Orlando S. Hoilett (library assembly)
*			eserra, Instructables User (for musical notes and tone frequencies), http://www.instructables.com/member/eserra/
* EMAIL:	orlandohoilett@gmail.com
* WEBSITE:	http://www.instructables.com/member/ohoilett/
* VERSION:	0.0


* AFFILIATIONS
* Calvary Engineering Family Group, USA
*	A group of electronics and science enthusiasts who enjoy building things


* DESCRIPTION
* This header file provides the function declarations for the library. The main
* function of the library is the playMelody() funciton that takes an input array
* of musical tones and plays the tones using the Arduino's tone() function.


* UPDATES
* Version 0.0
* 2015/01/06:2100>
*			Initialized code developed. Added use of constructor to easily
*			support and manager multiple music palyers.


* REFERENCES AND ACKNOWLEDGEMENTS
* I, Orlando Hoilett, wrote this library after seeing user: eserra's Instructable
* on "How to easily play music with buzzer on arduino (The imperial March - STAR
* WARS)." I was looking for a way to play a song on the Arduino and eserra's
* Instructable helped me do so. eserra put together the notes and their corresponding
* tone frequencies. I put together the constructors and class functions. Also,
* eserra original defined the tone frequencies as doubles. I changed these to integers
* (removing the decimal point) because the Arduino's tone() function does not take
* doubles as inputs.

* eserra'a Instructable can be viewed here http://www.instructables.com/id/How-to-easily-play-music-with-buzzer-on-arduino-Th/
* eserra's original document with the notes and tone frequencies can be viewed here http://tny.cz/d1a629c1


* DISCLAIMER
* This code is in the public domain. Please feel free to use, modify, distribute,
* etc. as needed, but please give reference to original author(s) as a courtesy to
* open source developing/-ers.
*
* If you find any bugs in the code, have any questions, or suggestions please
* feel free to contact me.

*/


#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "Arduino.h"


//http://tny.cz/d1a629c1
//http://www.instructables.com/id/How-to-easily-play-music-with-buzzer-on-arduino-Th/
#define	C0 16
#define	Db0	17
#define	D0	18
#define	Eb0	19
#define	E0	21
#define	F0	22
#define	Gb0	23
#define	G0	25
#define	Ab0	26
#define	LA0	28
#define	Bb0	29
#define	B0	31
#define	C1	33
#define	Db1	35
#define	D1	37
#define	Eb1	39
#define	E1	41
#define	F1	44
#define	Gb1	46
#define	G1	49
#define	Ab1	52
#define	LA1	55
#define	Bb1	58
#define	B1	62
#define	C2	65
#define	Db2	69
#define	D2	73
#define	Eb2	78
#define	E2	82
#define	F2	87
#define	Gb2	93
#define	G2	98
#define	Ab2	104
#define	LA2	110
#define	Bb2	117
#define	B2	123
#define	C3	131
#define	Db3	139
#define	D3	147
#define	Eb3	156
#define	E3	165
#define	F3	175
#define	Gb3	185
#define	G3	196
#define	Ab3	208
#define	LA3	220
#define	Bb3	233
#define	B3	247
#define	C4	262
#define	Db4	277
#define	D4	294
#define	Eb4	311
#define	E4	330
#define	F4	349
#define	Gb4	370
#define	G4	392
#define	Ab4	415
#define	LA4	440
#define	Bb4	466
#define	B4	494
#define	C5	523
#define	Db5	554
#define	D5	587
#define	Eb5	622
#define	E5	659
#define	F5	698
#define	Gb5	740
#define	G5	784
#define	Ab5	831
#define	LA5	880
#define	Bb5	932
#define	B5	988
#define	C6	1047
#define	Db6	1109
#define	D6	1175
#define	Eb6	1245
#define	E6	1319
#define	F6	1397
#define	Gb6	1480
#define	G6	1568
#define	Ab6	1661
#define	LA6	1760
#define	Bb6	1865
#define	B6	1976
#define	C7	2093
#define	Db7	2217
#define	D7	2349
#define	Eb7	2489
#define	E7	2637
#define	F7	2794
#define	Gb7	2960
#define	G7	3136
#define	Ab7	3322
#define	LA7	3520
#define	Bb7	3729
#define	B7	3951
#define	C8	4186
#define	Db8	4435
#define	D8	4699
#define	Eb8	4978

//DURATION OF THE NOTES
#define BPM 120 //BMP sets all other note durations
#define A 3*Q //1/4 + 1/2
#define H 2*Q //half 2/4
#define T W/3 //1/3
#define L Q+E //1/4 + 1/8
#define M Q+S //1/4 + 1/16
#define Q 60000/BPM //quarter 1/4 
#define E Q/2 //eighth 1/8
#define S Q/4 //sixteenth 1/16
#define W 4*Q //whole 4/4

const int defaultSpeaker = 9;


class MusicPlayer
{
  private:

    int speaker; //the output pin

  public:

    //Class Constructors
    MusicPlayer();
    MusicPlayer(int speaker);

    //play functions
    void playMelody(int notes[], unsigned int duration[], int songLength);
    void playMelody(int notes[], unsigned int duration[], int songLength,
                    int repetitions, unsigned long delayTime);

    int getSpeaker();

};

#endif
