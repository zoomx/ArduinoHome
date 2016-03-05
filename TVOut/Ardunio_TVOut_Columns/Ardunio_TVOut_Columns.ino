/*
Created by: Winkleink 2012
Using the TVOut Library from http://code.google.com/p/arduino-tvout/

This is an Arduino Implementation of the classic game Columns using the TVout Library (Google is your friend)
Pieces drop 3 at a time
Cycle them in place
Move the piece left and right as it drops
Get 3 in a row, horizontal, vertical or diagonal
Pieces are removed and the pieces above drop
Keep going as long as you can

This program is provided with no warranty (sorry I have to add this)
If you do use it and find it kinda fun then I'd love and email to winkleink[at]gmail[dot]com

I learned to program on a VIC-20 in the 80's and other than adding ';' to the end of the lines
I really haven't upgraded my skills

This should mean the code is easy to read as it is very basic
But, what it also means is that the code is blunt in how it gets things done.

Pin 3 is left
Pin 2 is Right
Pin 1 is Rotate
All active High
http://winkleink.blogspot.it/2012/05/arduino-tvout-game-columns.html

Adaptation to Funduino Joystick Shield by Zoomz 2015 05 30
Button logic reversed
Doens't work properly
*/

// Include the TVOut library and Fonts
#include <TVout.h>
#include <fontALL.h>

// Include the block graphics
#include "blocks.h"

// Initialze TBOut with TV
TVout TV;

int Level = 1; // Levels 1 to 5
int ShowPreview = 1; // 1 Show Preview - 0 Don't Show Preview
int score = 0;
int i;  // General Loop Variable
byte a;  // General Loop Variable
byte b;  // General Loop Variable
int y;  // General Loop Variable

int BLPress = 0;  // Did Left Button Get Pressed
int BRPress = 0;  // Did Right Button Get Pressed
int BCPress = 0;  // Did Rotate button Get Pressed - R was taken so used C

int BLeft = 5;  // Left Buttom
int BRight = 3;  // Right Button
int BRotate = 2; // Rotate Button

byte MoveTest;   // Used when rearranging the board to signify that I had to move a piece down
byte PieceMove;  // Used when rearranging the board to signify finished rearranging

int Pieces[3];  // Array for the 3 pieces in play
int NewPieces[3]; // The next set of pieces - Used withe the Preview

int RotatePiece;  // Usecd when rotating the pieces to temporaily hold one piece
//   int Direction = +1;  // Direction for movement
int GameOver = 1;  // 1 is GameOver
int v;  // Vertical position on blocks in play

byte AllCells[78];  // Where the blocks on the board are stored
byte TestCells[78];  // Used for recoding the blocks that need to be remvoed

int Touch; // Is the falling block touching the bottom


void setup() {

  pinMode(BLeft, INPUT); // Left Button Input
  pinMode(BRight, INPUT); // Right Button Input
  pinMode(BRotate, INPUT); // Rotate Button Input

  TV.begin(PAL, 120, 96);
  TV.select_font(font6x8);
  randomSeed(analogRead(0));

  //   Fill the board with SIXs to represent that it is empty.
  for (i = 0; i < 78; i++) {
    AllCells[i] = 6; //  6 Means empty square
    TestCells[i] = 6; // 6 Means empty square
  }

  TV.fill(0);  // Clear the screen to black

  // Start Text
  TV.println("\nColumns\n");
  TV.println("\nby Winkleink\n1 May 2012");
  TV.println ("\nLevel   - ");
  TV.println ("Preview - ");

  delay(1000);
  
  // Show Level
  TV.set_cursor(55, 55);
  TV.println (Level);

  // Show Preview
  TV.set_cursor(55, 65);
  TV.println ("ON ");


  //  Press ROTATE to start again
  int i = 0;
  while (i == 0) {
    // If I press Rotate Button Exit to the Game
    if (!digitalRead(BRotate)) {
      i = 1;
    }
    // If I press Left Level Up (to a max of 5)
    if (!digitalRead(BLeft)) {
      Level += 1;
      if (Level == 6) {
        Level = 1;
      }
      TV.set_cursor(45, 55);
      TV.print (Level);
    }


    // If I press Right Preview Toggle
    if (!digitalRead(BRight)) {
      if (ShowPreview == 1 ) {
        ShowPreview = 0;
        TV.set_cursor(55, 65);
        TV.print ("OFF");
      }
      else
      {
        ShowPreview = 1;
        TV.set_cursor(55, 65);
        TV.print ("ON ");
      }
    }

    TV.delay(300); // A short delay so that you can see the levels going up

  }

  // Pick the  first 3 new pieces to drop and put in NewPieces
  for (y = 0; y < 3 ; y++) {
    NewPieces[y] = random(6);
  }

  //  Press ROTATE to start again
  i = 0;
  while (i == 0) {
    if (!digitalRead(BRotate)) {
      i = 1;
    }
  }

  TV.fill(0);  // Clear the screen to black
  TV.draw_rect(0, 0, 38, 95, 1, 1); // Left Side marked out
  TV.draw_rect(81, 0, 38, 95, 1, 1); // Right side marked out
  TV.draw_rect(0, 91, 119, 5, 1, 1); // Across the bottom

  // Create a box on the right for the Preview if selected
  if (ShowPreview == 1) {
    TV.draw_rect(85, 7, 8, 25, 0, 0); // Draw a box on the right for the Preview
  }

  TV.draw_rect(0, 0, 40, 10, 0, 0); // Draw a box for the score


}

void loop() {

  // Put cursor top left and print the score
  TV.set_cursor(0, 0);
  TV.print(score);

  // Pick the horizontal position the start the fall
  int  hpos = 2;

  // Set Pieces in Play to the New Pieces
  for (y = 0; y < 3 ; y++) {
    Pieces[y] = NewPieces[y];
  }

  // Pick the 3 new pieces to drop
  for (y = 0; y < 3 ; y++) {
    NewPieces[y] = random(6);
  }

  // Show Preview of next piece if ShoePreview is set to 1
  if (ShowPreview == 1) {

    // Draw the 3 Next Pieces over to the side
    for (y = 0; y < 3; y++) {
      //      TV.bitmap(86,10+(y*7),D);

      switch (NewPieces[y]) {
        case 0:
          TV.bitmap(86, 10 + (y * 7), C);
          break;

        case 1:
          TV.bitmap(86, 10 + (y * 7), D);
          break;

        case 2:
          TV.bitmap(86, 10 + (y * 7), E);
          break;

        case 3:
          TV.bitmap(86, 10 + (y * 7), H);
          break;

        case 4:
          TV.bitmap(86, 10 + (y * 7), V);
          break;

        case 5:
          TV.bitmap(86, 10 + (y * 7), X);
          break;
      }

    }
  }

  GameOver = 0;  // Set GameOver to 0 to show it is no over
  v  = -3;  //  Start at the top - just off screen so the pieces appear one by one rather than starting with 3 on the screen
  Touch = 0; // Not touching the bottom or another block


  // Main Loop for the Game
  // If I can drop more
  while  (Touch == 0) {

    // Call Function to draw all 3 the pieces at v (vertical) and hpos (horizonal) positions
    DrawPieces(v, hpos);

    // Code for movement
    // Give 3 opportunities to move and rotate per drop

    for (i = 0; i < 3; i++) {

      for (a = 0; a < 5 ; a++) {

        // If Press Left BLPress = 1
        if (!digitalRead(BLeft)) {
          BLPress = 1;
        }

        // If Press Right BRPress = 1
        if (!digitalRead(BRight)) {
          BRPress = 1;
        }

        // If Press Rotate BCPress = 1
        if (!digitalRead(BRotate)) {
          BCPress = 1;  // Had to use C (carousel) as R was taken
        }

        TV.delay((6 - Level) * 4);

      }
      // Delay set by Level.  The Higher the Level the faster the game is
      TV.delay((6 - Level) * 4);

      if (BLPress) { // If the Left Button has been pressed - Go Left

        if (hpos > 0) { // Am I all the way to the left - if not do something
          if (AllCells[((v + 2) * 6) + hpos - 1] == 6) { // Is there space to the left
            for (b = 0; b < 3; b++) {
              if ((v + b) > -1) { // If On the Screen
                TV.draw_rect(39 + (hpos * 7), ((v + b) * 7), 6, 6, 0, 0); // Clear the existing block
              }
            }
            hpos--;  // Move Blocks to the Left
          }
        }

        BLPress = 0;
      }

      if (BRPress) { // If the Right Button has been pressed - Go Right

        if (hpos < 5) { // Am I all the way to the left - if not do something
          if (AllCells[((v + 2) * 6) + hpos + 1] == 6) { // Is there space to the left
            for (b = 0; b < 3; b++) {
              if ((v + b) > -1) { // If On the Screen
                //        TV.println("L");
                TV.draw_rect(39 + (hpos * 7), ((v + b) * 7), 6, 6, 0, 0); // Clear the existing block
              }
            }
            hpos++;  // Move Blocks to the Left
          }
        }

        BRPress = 0;
      }

      if (BCPress) { // If the Rotate Button has been pressed - Rotate the 3 pieces

        RotatePiece = Pieces[2];
        Pieces[2] = Pieces[1];
        Pieces[1] = Pieces[0];
        Pieces[0] = RotatePiece;

        BCPress = 0;
      }

      // Draw the 3 Pieces
      DrawPieces(v, hpos);

    }

    v++ ;  // Increase Vertical by 1 - go down 1 block

    // Have I reached the bottom of the screen
    if (v == 11) {  // If Vertical position reaches the bottom set Touch to 1 to stop this loop
      Touch = 1;

      // Put the value of the piece into the AllCells Array that represents the Live pieces
      for (y = 0; y < 3; y++) {
        if ((((v - 1) * 6) + hpos + (y * 6)) > -1) { // Is the Block on the screen
          AllCells[(((v - 1) * 6) + hpos + (y * 6))] = Pieces[y];
        }
      }

    }
    // Have I dropeed on another piece - If I have set Touch to 1
    if (AllCells[(((v + 2) * 6) + hpos)] != 6) {
      Touch = 1;

      // If I'm touching another block is the piece in play on the screen
      // If not set GameOver to 1
      for (y = 0; y < 3; y++) {
        if ((((v - 1) * 6) + hpos + (y * 6)) > -1) { // Is the Block on the screen
          AllCells[(((v - 1) * 6) + hpos + (y * 6))] = Pieces[y];
        }
        else {
          GameOver = 1;
        }
      }
    }

    // If On the screen, draw a clear block above the current one
    if (Touch == 0  && (v - 1) > -1) { // If going to drop and we have gone down far enough
      TV.draw_rect(39 + (hpos * 7), (v - 1) * 7, 6, 6, 0, 0);
    }

    // If Touch == 1 then Check for Patterns as end for this piece
    if (Touch == 1) {

      // Short delay
      TV.delay((6 - Level) * 20);

      // Make TestCells match the screen AllCells    for (a = 0; a < 78; a++){
      TestCells[a] = AllCells[a];
    }

    // TestCells is used to check for 3s as you need to check the whole board at one time
    // Then move pieces down if 3s found
    // Then check the whole thing again so cannot use the onscreen pieces (AllCells)


    // Start Moving the Pieces (if needed)

    PieceMove = 0; // If 1 then I have finished moving pieces
    //  MoveTest = 0;
    // Check if any pieces have been removed (7) and move the column down 1 place
    // Start if PieceMove is = 0 then go through it again

    // 7 means a pieces that has been made blank.

    while (PieceMove == 0) {
      MoveTest = 0;  // If 1 then I have moved a piece

      // Check IF Horizontal 3
      for (a = 1; a < 5 ; a++) { // Loop for each column
        for (b = 0; b < 13; b++) { // Loop for each row
          int CurrentPiece = AllCells[a + (b * 6)];

          if (CurrentPiece != 6) { // Make sure not BLANK
            if (AllCells[a - 1 + (b * 6)] == CurrentPiece & AllCells[a + 1 + (b * 6)] == CurrentPiece) {
              TestCells[a - 1 + (b * 6)] = 7;
              TestCells[a + (b * 6)] = 7;
              TestCells[a + 1 + (b * 6)] = 7;
              score = score + 3;
            }
          }
        }
      }
      // Check IF Vertical 3
      for (a = 0; a < 6 ; a++) { // Loop for each column
        for (b = 1; b < 12; b++) { // Loop for each row
          int CurrentPiece = AllCells[a + (b * 6)];
          if (CurrentPiece != 6) { // Make sure not BLANK
            if (AllCells[a + ((b - 1) * 6)] == CurrentPiece & AllCells[a + ((b + 1) * 6)] == CurrentPiece) {
              TestCells[a + ((b - 1) * 6)] = 7;
              TestCells[a + (b * 6)] = 7;
              TestCells[a + ((b + 1) * 6)] = 7;
              score = score + 3;
            }
          }
        }
      }

      // Check IF Diagonal 3
      for (a = 1; a < 5 ; a++) { // Loop for each column
        for (b = 1; b < 12; b++) { // Loop for each row
          int CurrentPiece = AllCells[a + (b * 6)];

          if (CurrentPiece != 6) { // Make sure not BLANK
            // Check Diagonaal Left to Right
            if (AllCells[a - 1 + ((b - 1) * 6)] == CurrentPiece & AllCells[a + 1 + ((b + 1) * 6)] == CurrentPiece) {
              TestCells[a - 1 + ((b - 1) * 6)] = 7;
              TestCells[a + (b * 6)] = 7;
              TestCells[a + 1 + ((b + 1) * 6)] = 7;
              TV.draw_rect(39 + ((a - 1) * 7), ((b - 1) * 7), 6, 6, 0, 0);
              TV.draw_rect(39 + (a * 7), (b * 7), 6, 6, 0, 0);
              TV.draw_rect(39 + ((a + 1) * 7), ((b + 1) * 7), 6, 6, 0, 0);
              score = score + 3;
            }

            // Check Diagonaal Right to Left
            if (AllCells[a + 1 + ((b - 1) * 6)] == CurrentPiece & AllCells[a - 1 + ((b + 1) * 6)] == CurrentPiece) {
              TestCells[a + 1 + ((b - 1) * 6)] = 7;
              TestCells[a + (b * 6)] = 7;
              TestCells[a - 1 + ((b + 1) * 6)] = 7;
              TV.draw_rect(39 + ((a + 1) * 7), ((b - 1) * 7), 6, 6, 0, 0);
              TV.draw_rect(39 + (a * 7), (b * 7), 6, 6, 0, 0);
              TV.draw_rect(39 + ((a - 1) * 7), ((b + 1) * 7), 6, 6, 0, 0);
              score = score + 3;
              //          TV.println("Diag RL");
            }
          }
        }
      }

      // Start Check the columns once 3s have been removed
      for (a = 0; a < 6 ; a++) { // Loop for each column
        for (b = 12; b != 0 ; b--) { // Loop for each row - Start at the bottom and go UP
          if (TestCells[a + (b * 6)] == 7) { // If a piece has been removed - move pieces down
            //  Move pieces down if there's a gap
            for (i = b; i > 0; i--) {
              TestCells[a + (i * 6)] = TestCells[a + ((i - 1) * 6)];
            }
            TestCells[a] = 6;  // The top cell will always be blank (6), so just set it here
            MoveTest = 1;  // Means I did nove pieces
          }
        }
      }
      // End Check the columns once
      // End move pieces down once

      // Do the Redraw as we go through the checking
      for (a = 0; a < 6; a++) { // Columns
        for (b = 0; b < 13; b++) { // Rows
          DrawPiece(b, a, TestCells[a + (b * 6)]);
        }
      }

      TV.delay((6 - Level) * 60); // Another little delay

      //  If I get to the end of moving the pieces and nothing has been moved then set PieceMove to 1 to exit the WHILE loop
      if (MoveTest == 0) {
        PieceMove = 1; // There are no more 3s
      }

      // Are any of the cells different to the displayed version if Yes set MoveTest to 2
      // MoveTest = 2 means pieces have moved

      for (a = 0 ; a < 78; a ++) {
        if (AllCells[a] != TestCells[a]) {
          MoveTest = 2;
        }
      }

      // Pieces have fallen
      if (MoveTest == 2) {
        // Reset the Variable if a piece moved after doing a full move
        MoveTest = 0;
        PieceMove = 0;
        TV.delay((6 - Level) * 100); // Delay to see the pieces falling

        //  Set AllCells to TestCells and draw it again
        for (a = 0; a < 78; a++) {

          if (TestCells[a] == 7) {  // If 0 set to 6 which is what means Blank in ALlCells
            //  AllCells[a] = 6;
            AllCells[a] = TestCells[a];
          }
          else
          {
            AllCells[a] = TestCells[a];
          }
        }

        //  Do the Redraw
        for (a = 0; a < 6; a++) { // Columns
          for (b = 0; b < 13; b++) { // Rows
            DrawPiece(b, a, AllCells[a + (b * 6)]);
          }
        }


        // End of WHILE PieceMove
      }

      //  END of IF Touch == 1
      TV.delay((6 * Level) * 60); // Another little dealy

    }

  }

  //     Is it the end of the Game
  if (GameOver == 1 ) {
    Touch == 1;
    TV.draw_rect(20, 20, 80, 30, 1, 0); // White Box - Black Boarder for GAME OVER
    TV.set_cursor(35, 32);
    TV.println("GAME OVER");
    TV.draw_rect(2, 60, 115, 30, 1, 0); // White Box - Black Boarder for Press [ROTATE] Key
    TV.set_cursor(7, 73);
    TV.println("PRESS [ROTATE] Key");

    //  Set Score to 0 to reset
    score = 0;

    //  Press ROTATE to start again
    int x = 0;
    while (x == 0) {
      if (!digitalRead(BRotate)) {
        x = 1;
      }
    }

    // Set up the screen for a new game.
    TV.fill(0);  // Clear the screen to black
    TV.draw_rect(0, 0, 38, 95, 1, 1); // Left Side marked out
    TV.draw_rect(81, 0, 38, 95, 1, 1); // Right side marked out
    TV.draw_rect(0, 91, 119, 5, 1, 1); // Across the bottom

    TV.draw_rect(85, 7, 8, 25, 0, 0); // Draw a box on the right

    //   Fill the board with SIXs to represent that it is empty.
    for (i = 0; i < 78; i++) {
      AllCells[i] = 6; // Means empty square
      TestCells[i] = 6; // Means empty square
    }
  }
  TV.delay(50);
}

//TV.delay(50);

// End of LOOP() Function
//}


// Function to draw all the Pieces in the playing area
void DrawPieces(int v, int hpos) {
  // Loop for each of the pieces to be display after doing the move
  for (y = 0;  y < 3; y++) {
    if (v + y > -1) { // Check of the piece is on the screen
      DrawPiece(v + y, hpos, Pieces[y]);
    }
  }
}

// Function to Draw a single piece
void DrawPiece(int v, int hpos, int Piece) {
  switch (Piece) {
    case 0:
      TV.bitmap(39 + (hpos * 7), (v * 7), C);
      break;

    case 1:
      TV.bitmap(39 + (hpos * 7), (v * 7), D);
      break;

    case 2:
      TV.bitmap(39 + (hpos * 7), (v * 7), E);
      break;

    case 3:
      TV.bitmap(39 + (hpos * 7), (v * 7), H);
      break;

    case 4:
      TV.bitmap(39 + (hpos * 7), (v * 7), V);
      break;

    case 5:
      TV.bitmap(39 + (hpos * 7), (v * 7), X);
      break;

    case 6:
      TV.draw_rect(39 + (hpos * 7), (v * 7), 6, 6, 0, 0);
      break;

    case 7:
      TV.draw_rect(39 + (hpos * 7), (v * 7), 6, 6, 0, 0);
      break;

  }
}
