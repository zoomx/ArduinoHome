#include <TVout.h>
#include <fontALL.h>
#include "blank.h"
#include "TVOlogo.h"
#include <avr/pgmspace.h>
#include "strings.h"
#include <EEPROM.h>
#include "images.h"
TVout TV;
//I hate using C so very very much
//I was getting some really odd issues and I had no idea why
// the solution was the RESET hack.
int width;
int height;
String* sidebar;
int sidebarlength;
boolean stillalive=false;
int eead = 42; //the address of the unix/still alive bit to flip






void setup() {
  pinMode(6,INPUT); //input and low doesn't reset, while output and low does.
  digitalWrite(6,LOW);
 
  stillalive = EEPROM.read(eead);
  EEPROM.write(eead, !stillalive); //flip the biy
  
  
  TV.begin(PAL,200,192);
  width= TV.hres();
  height = TV.vres();

 // stillalive=true;

  if(!stillalive){
    TV.select_font(font8x8);
    String sbt[] ={"ls","cat","ADT-TOOLS","ADT-COMPIL","chmod","iwconfig","ifconfig","gcc","ed","cd","mkdir","DooM","Tetris","chroot","win","airmon","sh","java","javac","chmod" }; 
    int sbl = 19; //you want to use sbt.length? NOPE! CHUCK TESTA! WERE USING C BITCH, YOU HAVE TO HARD CODE THE SIZE
	//DEAL WITH IT
    blankAndDrawMenu(sbt,sbl);
    
    pinMode(6,OUTPUT); //animations done so reset
    digitalWrite(6,LOW);
    

  }else{

    TV.select_font(font4x6);
    TV.set_offset(4,5); //indents all the print()'s by these many pixels. I added this to the library.
    drawOutlineClear();
    doAnim();
    pinMode(6,OUTPUT);
    digitalWrite(6,LOW);
//    
  }
}
void drawOutlineClear(){
  TV.bitmap(0,0,blank,0,0,0);
  TV.set_cursor(0,0); //doesn't affect offset
}
void loop(){}

String gs(int arrayNum){ //get string from strings.h
 return strcpy_P(buffer, (char*)pgm_read_word(&(string_table[arrayNum])));
}

void ni(int image){
 if(image == 1) TV.bitmap(134,113,one,0,0,0);
 if(image == 2) TV.bitmap(134,113,two,0,0,0);
 if(image == 3) TV.bitmap(134,113,thr,0,0,0);
 if(image == 4) TV.bitmap(134,113,fou,0,0,0);
 if(image == 5) TV.bitmap(134,113,fiv,0,0,0);
 if(image == 6) TV.bitmap(134,113,six,0,0,0);
 if(image == 7) TV.bitmap(134,113,sev,0,0,0);
 if(image == 8) TV.bitmap(134,113,eig,0,0,0);
 if(image == 9) TV.bitmap(134,113,nin,0,0,0);
 if(image == 10) TV.bitmap(134,113,ten,0,0,0);
 if(image == 11) TV.bitmap(134,113,ele,0,0,0);
 if(image == 12) TV.bitmap(134,113,twe,0,0,0);
 if(image == 13) TV.bitmap(134,113,thi,0,0,0);
 if(image == 14) TV.bitmap(134,113,fort,0,0,0);
 if(image == 15) TV.bitmap(134,113,fift,0,0,0);
 
}

void doAnim(){
//  int crash=0;
//  asm volatile ("  jmp 1338");  
//  long crasher[1];
//  for(;;){
//    crash++;
//    long crasher[crash];
//    for(int i=0; i<crash;i++){
//      crasher[i]=-142;
//    }
//  //crasher[random(0,crash)] = 123124;
//  }
//ps("^%*@(%@$ NG@IU^@(N^*@%GI@%^(@*)_(N^)@&*B$*$<&@M>$^@>:?<%^?@K^>@<^H@L#^><&>?&<(>(<*>><)<>(_<)()+>)>??>?&>#@<@><^@>$%<^?><&$><>?^&*><YU>?<YTU><$?><T>R<&W><$%&^L?<W%^:&KE>^U&<E^<?%^<&>#<&?>#%^&<?:@#%<&?>^&<#>< N<YU>?<DTY>U%^E>*",400,500); 
// ps("@@@@#%^$(^&@^&^YUN ^*#K^YB>^&HK<$%@#K^@JHG^IH@%IH*(IJ(HI)H)HK@#$^$()@$*%^(@)*$# %N %^MN<MVNMVM<<XM NCMXNMM<$@!M^%@#^N&MN*(M",500,2000);
  ps(gs(88),2000,0); //isn't this just ugly?
  ps(gs(89),2000,0);
  ps("",0,0);
  ps("",0,2600);
  ps(gs(0),2050,1600);
  ps(gs(1),2000,98);
  ps(gs(2),1800,800);
  ps(gs(3),2360,40);
  ps(gs(4),2710,1400);
  ni(1); //yup
  ps(gs(5),1760,1900);
  ps(gs(6),1570,200);
  pso(gs(7),750,100);
  ps(gs(8),710,1200);
  pso(gs(9),1550,0);
  ps(gs(10),1530,180);
  ni(6);
  ps(gs(11),1400,500);
  ni(1);
  ps(gs(12),1858,10);
  ps(gs(13),1782,200);
  ps(gs(14),1985,10);
  pso(gs(15),1200,0);
  ps(gs(16),400,160);
  ni(5);
  ps(gs(17),1600,0);
  ps(gs(18),1600,20);
  ni(1);
  ps(gs(19),1520,20);
  ps(gs(20),1500,1500);

  drawOutlineClear();
  ni(1);
  ps("Forms FORM-55551-5:",550,0);
  ps("Personnel File Addendum:",1100,0);
  ps("",0,660);
  ps("Dear <<Subject Name Here>>,",1100,200);
  ps("",0,710);
  ps(gs(21),1317,2168);
  pso(gs(22),597,0);
  pso(gs(23),550,0);
  pso(gs(24),906,0);
  ps(gs(25),1115,1225);
  pso(gs(26),650,0);
  pso(gs(27),1347,0);
  ni(8);
  pso(gs(28),488,0);
  ps(gs(29),998,0);
  pso(gs(30),325,0);
  pso(gs(31),488,0);
  ps(gs(32),557,1900);
  ni(3);
  ps(gs(33),1649,2122);
  ps(gs(34),1440,302);
  pso(gs(35),580,395); // in sync
  ni(11);
  ps(gs(36),882,1649);
  pso(gs(37),1400,0);
  ps(gs(38),1509,325);
  ni(9);
  ps(gs(39),1425,441);
  ps(gs(40),1867,0);
  ps(gs(41),1800,0);
  ps(gs(42),1920,0);
  ps(gs(43),1850,0);
  ni(3);
  ps(gs(44),1913,0);
  ni(5);
  ps(gs(45),1620,0);
  ni(1);
  ps(gs(46),1456,0);
  pso(gs(47),395,0);
  ps(gs(48),1440,1500);


  drawOutlineClear();
  ni(1);
  ps("Forms FORM-55551-6:",450,0);
  ps("Personnel File Addendum Addendum:",1310,0);
  ps("",0,660);
  ps("One last thing:",1150,0);
  ps("",0,5);
  pso(gs(49),1324,0);
  ps(gs(50),627,1788);
  pso(gs(51),534,0);
  pso(gs(52),1184,0);
  pso(gs(53),1022,0);
  pso(gs(54),232,0);
  ps(gs(55),882,1430);
  pso(gs(56),511,0);
  ps(gs(57),2672,0);
  ps(gs(58),1254,2052);
  pso(gs(59),511,0);
  ni(7);
  pso(gs(60),325,0);
  ps(gs(61),998,1883);
  ps(gs(62),1240,921);
  pso(gs(63),279,0);
  ps(gs(64),759,1393);
  pso(gs(65),1486,0);
  ps(gs(66),1765,0);
  ni(2);
  ps(gs(67),1904,418);
  ni(12);
  ps(gs(68),1427,0);
  ni(6);
  ps(gs(69),1790,0);
  ni(1);
  ps(gs(70),1495,0);
  ps(gs(71),2083,0);
  ni(5);
  ps(gs(72),1943,0);
  ni(3);
  ps(gs(73),1920,0);
  ni(1);
  ps(gs(74),1625,0);
  pso("still ",384,0);
  ps("alive.",1440,340);
  drawOutlineClear();
  
  ps("",0,0);
  ps("",0,0);
  ps("PS:",100,0);
  pso("And believe me I am",1425,0);
  ps(" still alive.",1038,900);
  ps("",0,0);
  ps("PPS:",298,0);
  ps("I'm doing Science and I'm",1204,0);
  ps("still alive.",1091,800);
  ps("",0,0);
  ps("PPPS",175,0);
  ps("I feel FANTASTIC and I'm",1404,0);
  ps("still alive.",1091,00);
  ps("",0,100);
  ps("FINAL THOUGHT",1154,0);
  ps("While you're dying I'll be",1279,0);
  ps("still alive.",1254,00);
  ps("",0,100);
  ps("FINAL THOUGHT PS:",829,0);
  ps("And when you're dead I will be",1234,0);
  ps("still alive.",1161,0);
  ps("",0,459);
  ps("",0,400);
  ps("STILL ALIVE",1184,2000);
  drawOutlineClear();


  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("10 hours later and I'm sick of this song",2000,1500);
  ps("You could almost say,",1000,1500);
  ps(".",0,500);
  ps("..",0,500);
  ps("...",0,500);
  ps("I wan't it gone.",1400,500); 
  ni(3);
  ps("YEEEAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",1500,2000);
  drawOutlineClear();
  
  
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("       ",100,50);
  ps("want to see this all crash?",2000,1500);
  ps("all it takes is a String with weird chars",1000,1500);
  ps("deploying in:",0,500);
  ps("3",0,500);
  ps("2",0,500);
  ps("1",0,500);
  ps("^%*@(%@$ NG@IU^@(N^*@%GI@%^(@*)_(N^)@&*B$*$<&@M>$^@>:?<%^?@K^>@<^H@L#^><&>?&<(>(<*>><)<>(_<)()+>)>??>?&>#@<@><^@>$%<^?><&$><>?^&*><YU>?<YTU><$?><T>R<&W><$%&^L?<W%^:&KE>^U&<E^<?%^<&>#<&?>#%^&<?:@#%<&?>^&<#>< N<YU>?<DTY>U%^E>*",100,0);
  asm volatile ("  jmp 140"); //lol not really 
 // ps("@@@@#%^$(^&@^&^YUN ^*#K^YB>^&HK<$%@#K^@JHG^IH@%IH*(IJ(HI)H)HK@#$^$()@$*%^(@)*$# %N %^MN<MVNMVM<<XM NCMXNMM<$@!M^%@#^N&MN*(M",500,2000);
  drawOutlineClear();
}

void ps(String txt, int linetime, int findelay){ //printslow. eclispe has made me too lazy to manually type out meaningfull names
  int mdelay = 0;
  if(txt.length() >0) mdelay = linetime/txt.length();
  else mdelay = linetime;


  for(int i =0; i<txt.length();i++){
    TV.print(txt.charAt(i));
    TV.print('_');
    if(!stillalive) TV.tone(800,1); ///////if in unix
    TV.delay(mdelay); 
    TV.write(8);
  }

  TV.println();
  while(findelay>1000){
    TV.delay(1000);
    findelay-=1000;
  }
  if(findelay>0)TV.delay(findelay);

}


void pso(String txt, int linetime, int findelay){ //no new line

  int mdelay = 0;
  if(txt.length() >0) mdelay = linetime/txt.length();
  else mdelay = linetime;

  //  TV.print('_'); //print cursor
  //  TV.delay(mdelay); 
  //  TV.write(8); //writse the ascii value of backspace. see vid_gen.cpp
  for(int i =0; i<txt.length();i++){
    TV.print(txt.charAt(i));
    TV.print('_');
    if(!stillalive) TV.tone(500,1);
    TV.delay(mdelay); 
    TV.write(8);
  }
  while(findelay>1000){
    TV.delay(1000);
    findelay-=1000;
  }
  if(findelay>0)TV.delay(findelay);
}

void blankAndDrawMenu(String sbtxt[],int sbtxtl){
  TV.fill(BLACK);
  TV.bitmap(0,0,TVOlogo,0,0,0);
  setHeaderText("/home/bob/bin/"); //my names bob IRL by the way. 
  setFooterText("Terminal"); // I just thought you should know that
  setSidebar(sbtxt,sbtxtl); //ITS 3AM, OK?
  drawTerminalAnim();      //CUT ME SOME SLACK
}

void drawTerminalAnim(){
  TV.select_font(font6x8);
  TV.set_cursor(0,32);
  TV.set_offset(50,0);
  ps("inbound telnet session: ",300,1000);
  ps("---usr:CaveJ connected--",300,2000);
  ps("           ",300,500);
 
  ps("chmod 777 ./GLADoS",2000,1000);
  ps("chroot GLADoS /bin/bash",1500,400); //no, i don't know how to use chroot. want to fight about it?
  ps("loading...",400,800);
  ps("--------------------",200,100);
  ps("Welcome to Aperture",400,100); 
  ps("shower curtains Inc!",400,100); 
  ps("--------------------",200,2000);
  pso("Dialing primary",300,300); //as seen on shitty debit machines
  ps("....",2000,0);
  ps("Connected at 1200 baud",300,2000); //aahh the good old days
  pso("GLaD@APSCI$ ",100,1500);
  ps("win.exe",500,1000); //olol
//  ps("****$LO4gFMM%RTOGJMGRLGJOERJGORJGLERGJOERGMLDFGMAEORGJFGMAOKL#K^)IOKHTRLMAERLMTOP$#KLRMG LKDMFGOJARTMREOTJGOBMRE YKOP%JA[OFGJML:EAMROGKAERGKERALGMROGJARTPARGMLORJEG",100,0);
//  ps("****$LO4gFMM%RTOGJMGRLGJOERJGORJGLERGJOERGMLDFGMAEORGJFGMAOKL#K^)IOKHTRLMAERLMTOP$#KLRMG LKDMFGOJARTMREOTJGOBMRE YKOP%JA[OFGJML:EAMROGKAERGKERALGMROGJARTPARGMLORJEG",100,0);
//  ps("****$LO4gFMM%RTOGJMGRLGJOERJGORJGLERGJOERGMLDFGMAEORGJFGMAOKL#K^)IOKHTRLMAERLMTOP$#KLRMG LKDMFGOJARTMREOTJGOBMRE YKOP%JA[OFGJML:EAMROGKAERGKERALGMROGJARTPARGMLORJEG",100,0);
//  ps("****$LO4gFMM%RTOGJMGRLGJOERJGORJGLERGJOERGMLDFGMAEORGJFGMAOKL#K^)IOKHTRLMAERLMTOP$#KLRMG LKDMFGOJARTMREOTJGOBMRE YKOP%JA[OFGJML:EAMROGKAERGKERALGMROGJARTPARGMLORJEG",100,0);
//  ps("****$LO4gFMM%RTOGJMGRLGJOERJGORJGLERGJOERGMLDFGMAEORGJFGMAOKL#K^)IOKHTRLMAERLMTOP$#KLRMG LKDMFGOJARTMREOTJGOBMRE YKOP%JA[OFGJML:EAMROGKAERGKERALGMROGJARTPARGMLORJEG",100,0);
 ps("Launching Windows ME 3",300,100);
 ps("SPF 45 AMD64 with Gnome 4",300,100); //trollin trollin trollin
}

void setSidebar(String txta[], int arraySize){
  TV.select_font(font4x6);
  for(int i=0; i<arraySize;i++){
    int x = 0;
    int y = (i*8)+18;
    TV.set_cursor(x,y);
    TV.tone(500,10);
    print(txta[i]);
    TV.delay(50);

  }
  TV.select_font(font8x8ext);
}

void setFooterText(String txt){
  int mid = (41+(width-1))/2;
  int cursx = mid-((txt.length()/2)*8);
  TV.set_cursor(cursx,15);
  print(txt);


}


void setHeaderText(String txt){
  TV.set_cursor(16,3);
  print(txt);


}

void print(String txt){ //yeah... i wrote the unix and still alive thigs at separate times then glues them together.
  char foo[txt.length()+1];
  txt.toCharArray(foo, txt.length()+1);
  TV.println(foo); //i wrote all these comments at 3am, so if they dont make any sense than...yeah... suck it up and COMPILE HARDER
}





// oh and look up JerzycowCode on Google Play. 

//unless you have an IPhone
//if that's the case, then go away, you arent wanted in this source.









