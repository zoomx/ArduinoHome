//
// static_fading_8
// digital pins 2-9
// a streak that doesn't move (it's static)

// 
//                             11
//                             1098765432    
const word dimbits[] = { 0b0000001111111100,  // frame 1
                         0b0000000111111100,
                         0b0000000011111100, 
                         0b0000000001111100, 
                         0b0000000000011100, 
                         0b0000000000001100, 
                         0b0000000000000100, 
                         0b0000000000000100, 
                         0b0000000000000000,
                         0b0000000000000000,
                         0b0000000000000000,
                         0b0000000000000000};  // 167
                         
unsigned long duration = 0;
unsigned long times_out = 8000;  // frame's time out "speed"
                                 // 500 for way fast
                                 // 50000 for way slow
                        
int idx;
byte framepointer = 0;

void setup ()
{
  //pinMode(13,OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //PORTD &= 0b00000011;
  
}
void loop ()
{
  // framepointer limit == number of frames * 12
  // it's the total of words in the dimbits[] array 
  for (framepointer = 0; framepointer < 12; framepointer = (framepointer + 12))
  // 0-11,12-33,24-35,36-47,48-59,60-71,72-83,84-95,96-107,
  // 108-119,120-131,132-143,144-155,156-167
  {
    for(duration=0; duration<times_out; duration++)
    // times_out is the number of
    // frame repetitions
    {
      for(idx = framepointer; idx < (framepointer + 12); idx++)
      {
        commitPORTs();
      }
    }
  }
  framepointer = 0;
  //delay(500);
}

void commitPORTs ()
{
  PORTD = dimbits[idx];
  PORTB = dimbits[idx]/256;
}
    
