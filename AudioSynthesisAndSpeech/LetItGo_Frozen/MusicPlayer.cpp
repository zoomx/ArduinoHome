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
* This source file provides the function definitions for the library. The main
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


#include "MusicPlayer.h"

//CONSTRUCTORS
//*****************************************************************************

//MusicPlayer()
//Default Constructor
//Initializes the music player object with the default speaker pin set to pin 9.
MusicPlayer::MusicPlayer() : speaker(defaultSpeaker)
{
}


//MusicPlayer()
//Alternate Constructor
//Initializes the music player object with the input speaker pin.
MusicPlayer::MusicPlayer(int speaker) : speaker(speaker)
{
}

//*****************************************************************************


//void playMelody(int notes[], unsigned int duration[], int songLength)
//@param		notes[]: array with the musical notes for the tune
//@param		duration[]: array with the duration for each note
//@param		songLength: the number of notes in the notes[] array
//
//Plays the notes in the notes[] array with the given durations.
void MusicPlayer::playMelody(int notes[], unsigned int duration[], int songLength)
{
  for (int i = 0; i < songLength; i++)
  {
    tone(speaker, notes[i], duration[i]);
    delay(1 + duration[i]);
  }
}


//void playMelodyplayMelody(int notes[], unsigned int duration[], int songLength,
//	int repetitions, unsigned long delayTime)
//@param		notes[]: array with the musical notes for the tune
//@param		duration[]: array with the duration for each note
//@param		songLength: the number of notes in the notes[] array
//@param		repetitions: the number of times the song should repeat
//@param		delayTime: the time delay between the iterations of the song
//
//Plays the notes in the notes[] array with the given durations and given number
//of repetitions.
void MusicPlayer::playMelody(int notes[], unsigned int duration[], int songLength,
                             int repetitions, unsigned long delayTime)
{
  for (int j = 0; j < repetitions; j++)
  {
    for (int i = 0; i < songLength; i++)
    {
      tone(speaker, notes[i], duration[i]);
      delay(1 + duration[i]);
    }
    delay(delayTime);
  }
}


//int getSpeaker()
//@return		returns the pin the speaker is attached to
int MusicPlayer::getSpeaker()
{
  return speaker;
}
