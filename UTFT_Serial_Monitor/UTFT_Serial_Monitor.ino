//2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//-
// This program- is a demo ozf how to use most of the functions
// of the library with a supported disp------lay modules.
//
// This demo was made for modules with a screen resolution
// of 480x272 pixels.
//
// This program requires the UT******FT library.
//

#include "Fonts.h"

#include "Calculator.h"
#include "Clock.h"
#include "SevenSegment.h"
#include "Keys.h"
#include "Terminal.h"
#include <avr/pgmspace.h>
// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next line for Arduino 2009/Uno
//UTFT myGLCD(ITDB32S,19,18,17,16);   // Remember to change the model parameter to suit your display module!


// Declare which fonts we will be using
extern uint8_t SmallerFont[];

// Uncomment the next line for Arduino 2009/Uno
//UTFT myGLCD(ITDB43,19,18,17,16);   // Remember to change the model parameter to suit your display module!
UTFT myGLCD(SSD1963_480, 5, 4, 3, 2, 9, 8, 7, 6);
//UTFT myGLCD(SSD1963_480,13,12,11,10,9,8,7,6);
//UTFT myGLCD(SSD1963_480,13,12,11,10);
//UTFT myGLCD(ILI9341_S4P,13,12,11,10,9,8,7,6);
//UTFT myGLCD(ILI9341_S4P,13,12,11,10);
//UTFT myGLCD(SSD1289,5,4,3,2,9,8,7,6);
// Uncomment the next line for Arduino Mega
//UTFT myGLCD(ITDB43,38,39,40,41);   // Remember to change the model parameter to suit your display module!
int LO = 8;
int HI = 9 ;
int set = 1;
int DATA = 6;
int CLK = 7;
int RESDATA = 8;
int currentrow = 1;
int seconds;
int displayTouch = 0;

Calculator* myCalculator = new Calculator();
Clock myClock = Clock(200, 120, 150);
/*
  SevenSegment myLEDA = SevenSegment(10,10,50,50);
  SevenSegment myLEDB = SevenSegment(110,10,50,50);
  SevenSegment myLEDC = SevenSegment(220,10,50,50);
  SevenSegment myLEDD = SevenSegment(330,10,50,50);
  SevenSegment myLEDE = SevenSegment(10,110,50,50);
  SevenSegment myLEDF = SevenSegment(110,110,50,50);
  SevenSegment myLEDG = SevenSegment(220,110,50,50);
*/

extern Keys theKeys;
extern Terminal theTerminal;

void setup()
{
  DDRD = B11111111;  // Make Digital lines 0-7 Output
  DDRB = B11111111;  // Make Digital lines 8-13 Output
  digitalWrite(3, HIGH); // Set LCD_CS High
  digitalWrite(2, HIGH); // Set LCD_RESET High
  delayMicroseconds(100); // Wait 100 Microseconds
  digitalWrite(2, LOW); // Put LCD_RESET Low
  delayMicroseconds(100); // For !00 Microseconds
  digitalWrite(2, HIGH); // Then bring LCD_RESET High
  digitalWrite(3, LOW); // and enable LCD_CS
  Serial.begin(115200);
  //randomSeed(analogRead(0));
  pinMode(HI, OUTPUT);
  pinMode(LO, OUTPUT);
  pinMode(DATA,  OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(RESDATA, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  //pinMode(3,OUTPUT);
  //digitalWrite(3,HIGH);
  //digitalWrite(HI,LOW);
  //digitalWrite(LO,LOW);
  //digitalWrite(CLK,HIGH);
  //digitalWrite(RESDATA,HIGH);
  //digitalWrite(2,HIGH);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  delay(10);
  //digitalWrite(2,HIGH);
  //  myClock.paintClock();
  //digitalWrite(3,HIGH);
  delay(10);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(0, 0, 479,271);
  //digitalWrite(3,HIGH);
  //digitalWrite(2,HIGH);
  //  myGLCD.setFont(SmallerFont);
  myGLCD.spistar();
  seconds = 0;
  theKeys.drawKeyboard();
  int rowlen0 = 13;
  char row0[rowlen0] = {'`', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='};
  theKeys.drawRow(row0, rowlen0, 370, 10);
  int rowlen1 = 12;
  char row1[rowlen1] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\'};
  theKeys.drawRow(row1, rowlen1, 360, 30);
  int rowlen2 = 10;
  char row2[rowlen2] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\''};
  theKeys.drawRow(row2, rowlen2, 350, 50);
  int rowlen3 = 9;
  char row3[rowlen3] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};
  theKeys.drawRow(row3, rowlen3, 340, 70);

  //  int rowlen =
  theTerminal.drawTerminalWindow();
  char textLine[6];
  textLine[0] = 'H';
  textLine[1] = 'E';
  textLine[2] = 'L';
  textLine[3] = 'L';
  textLine[4] = 'O';
  textLine[5] = 0;
  //theTerminal.putText(textLine,5);
  //theTerminal.putText(textLine,5);
  //theTerminal.putText("EVAN JAN WILLIAMS",7);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRect(50, 200, 60, 210);
  /*
    for (int i = 0; i < 7; i++)
    {
      myLEDA.drawSegment(i);
      myLEDB.drawSegment(i);
      myLEDC.drawSegment(i);
      myLEDD.drawSegment(i);
      myLEDE.drawSegment(i);
      myLEDF.drawSegment(i);
      myLEDG.drawSegment(i);
    }
  */
}
void printHex(unsigned int x, char &c1, char &c2, char &c3, char &c4)
{
  unsigned int x1, x2, x3, x4;
  char zero = '0';
  char aaaa = 'A';
  char bbbb = 'Z';

  x1 = floor(x / 4096);
  x = x - x1 * 4096;
  x2 = floor(x / 256);
  x = x - x2 * 256;
  x3 = floor(x / 16);
  x4 = x - x3 * 16;

  if (x1 <= 9)
  {
    c1 = zero + x1 + 2;
  }
  else if (x1 < 16)
  {
    c1 = aaaa + x1 - 10;
  }
  else
  {
    c1 = bbbb;
  }
  if (x2 <= 9)
  {
    c2 = zero + x2 + 2;
  }
  else if (x2 < 16)
  {
    c2 = aaaa + x2 - 10;
  }
  else
  {
    c2 = bbbb;
  }
  if (x3 <= 9)
  {
    c3 = zero + x3 + 2;
  }
  else if (x3 < 16)
  {
    c3 = aaaa + x3 - 10 ;
  }
  else
  {
    c3 = bbbb;
  }
  if (x4 <= 9)
  {
    c4 = zero + x4 + 2;
  }
  else if (x4 < 16)
  {
    c4 = aaaa + x4 - 10;
  }
  else
  {
    c4 = bbbb;
  }
}
void printDec(unsigned int x, int r, int c)
{
  unsigned int x1, x2, x3, x4, x5;
  char c1, c2, c3, c4, c5;
  char zero = '0';
  char aaaa = 'A';

  x1 = x / 10000;
  x = x - x1 * 10000;
  x2 = x / 1000;
  x = x - x2 * 1000;
  x3 = x / 100;
  x = x - x3 * 100;
  x4 = x / 10;
  x5 = x - x4 * 10;


  c1 = zero + x1 + 2;
  c2 = zero + x2 + 2;
  c3 = zero + x3 + 2;
  c4 = zero + x4 + 2;
  c5 = zero + x5 + 2;

  delay(10);
  if (x1 != 0)
  {
    myGLCD.putChar(c1, r, c--);
  }
  delay(10);
  if (x2 != 0)
  {
    myGLCD.putChar(c2, r, c--);
  }
  delay(10);
  if (x3 != 0)
  {
    myGLCD.putChar(c3, r, c--);
  }
  delay(10);
  if (x4 != 0)
  {
    myGLCD.putChar(c4, r, c--);
  }
  delay(10);
  myGLCD.putChar(c5, r, c--);
  delay(10);
}
void getLargeChar(char currentKey, uint16_t theChar)
{
  uint16_t *ptr;
  int b;

  if (currentKey == 'Q')
  {
    ptr = theChar;
    for (int k = 0; k < 16; k++)
    {
      *ptr++ = *(squareroot + k);
    }
  }
  else if (currentKey == 'S')
  {
    b = 0;

    ptr = theChar;
    for (int k = 0; k < 16; k++)
    {
      *ptr++ = pgm_read_word(largeFont + (b * 0x10) + k);
    }
  }
  else if (currentKey == 'P')
  {
    ptr = theChar;
    for (int k = 0; k < 16; k++)
    {
      *ptr++ = *(plusminus + k);
    }
  }
  else if (currentKey == 'C' || currentKey == '=' || currentKey == '.')
  {
    b = currentKey - 0x20 - 2;

    ptr = theChar;
    for (int k = 0; k < 16; k++)
    {
      *ptr++ = pgm_read_word(largeFont + (b * 0x10) + k);
    }
  }
  else
  {
    b = currentKey - 0x20;

    ptr = theChar;
    for (int k = 0; k < 16; k++)
    {
      *ptr++ = pgm_read_word(largeFont + (b * 0x10) + k);
    }
  }
}
void looptest()
{
  char textLine[6];
  textLine[0] = 'H';
  textLine[1] = 'E';
  textLine[2] = 'L';
  textLine[3] = 'L';
  textLine[4] = 'O';
  textLine[5] = 0;
  theTerminal.putText(textLine, 5);
  delay(1000);
}
void loop()
{
  int x, y;
  int i, j;
  char currentkey;
  char currentControl;
  uint16_t theChar[16];
  uint16_t *ptr;
  int b;

  //myGLCD.AD7843_On();
  //x = myGLCD.AD7843_X();
  //y = myGLCD.AD7843_Y();
  //myGLCD.AD7843_Off();

  // delay(10000);
  //paintTouch(x,y);
  /*
  currentkey = lookupChar(x, y);
  currentControl = lookupControl(x, y);
  if (currentControl != 0)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(50, 200, 60, 210);
    displayTouch = 1;
  }
  else if (currentkey != 0)
  {
    char buf[2];
    buf[0] = currentkey;
    buf[1] = 0;
    myGLCD.setColor(255, 0, 0);
    putKey(currentkey);
    //delay(10);
    myGLCD.setColor(255, 255, 255);
    //delay(10);
    theTerminal.putText(buf, 1);
    if (displayTouch == 1)
    {
      paintTouch(x, y);
    }
  }
  */
  
  char buf[200];
  char c;

  //buf[0] = 'A';
  //buf[1] = 0;

  //theTerminal.putText(buf,1);
  //delay(1);

  i = 0;
  while (Serial.available() > 0)
  {
    c = Serial.read();
    buf[i] = c;
    i++;
    //delay(1);
  }
  buf[i] = 0;
  theTerminal.putText(buf, i-1);
 
  delay(10);
}
void putKey(char keycode)
{
  double left_x, top_y, right_x, bottom_y, line_width, line_height;
  uint16_t *ptr;
  int b;
  int xpos, ypos;
  uint16_t theChar[16];

  int rowlen;
  char *rowarray;
  char row0[14] = {'`', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='};
  char row1[13] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 'd'};
  char row2[11] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', 'p'};
  char row3[10] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};
  int done = 0;
  int offset = 0;
  while (offset <= 3 && done == 0)
  {
    if (offset == 0)
    {
      rowlen = 14;
      xpos = 370;
      ypos = 10;
    }
    else if (offset == 1)
    {
      rowlen = 13;
      xpos = 360;
      ypos = 30;
    }
    else if (offset == 2)
    {
      rowlen = 11;
      xpos = 350;
      ypos = 50;
    }
    else
    {
      rowlen = 10;
      xpos = 340;
      ypos = 70;
    }
    int offset2 = 0;
    while (offset2 <= rowlen && done == 0)
    {
      char test;
      if (offset == 0)
      {
        test = row0[offset2];
      }
      else if (offset == 1)
      {
        test = row1[offset2];
      }
      else if (offset == 2)
      {
        test = row2[offset2];
      }
      else
      {
        test = row3[offset2];
      }
      if (keycode == test)
      {
        xpos = 150 + xpos - (20 * offset2);
        ypos += 210;
        myGLCD.setColor(255, 0, 0);
        //myGLCD.drawRect(xpos,ypos,xpos+10,ypos+10);
        //myGLCD.printChar(keycode,xpos,ypos,1);
        done = 1;
      }
      offset2 += 1;
    }
    offset += 1;
  }
}
void paintTouch(int x, int y)
{
  int keycol, keyrow, rowcount, rowoffset;
  char c1, c2, c3, c4;
  int row, col;
  int b;
  char keypress;
  int xd, yd;
  int x1, y1;
  int xe, ye;


  xd = x / 8;
  yd = y / 8;

  ye = 272 - yd;
  ye = ye + 60;

  xe = xd * 9 / 8;
  xe = xe - 25;

  x1 = xe;
  y1 = ye;


  x1 = x1 / 10;
  y1 = y1 / 10;

  x1 = int (x1 / 2);

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(xd, ye, xd + 10, ye + 10);
}
char lookupChar(int x, int y)
{
  char row0[14] = {'`', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='};
  char row1[13] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 'd'};
  char row2[11] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', 'p'};
  char row3[10] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};

  int keycol, keyrow, rowcount, rowoffset;
  char c1, c2, c3, c4;
  int row, col;
  int b;
  char keypress;
  int xd, yd;
  int x1, y1;
  int keyoffset;
  int rowlen[4];
  int rowlength;

  rowlen[0] = 13;
  rowlen[1] = 12;
  rowlen[2] = 10;
  rowlen[3] = 9;

  xd = x / 9;
  yd = y / 8;

  yd = 272 - yd;
  yd = yd + 20;

  xd = xd * 9 / 8;

  x1 = xd;
  y1 = yd;


  x1 = x1 / 10;
  y1 = y1 / 10;

  x1 = int (x1 / 2);
  int rownumber = -1;

  if (y1 >= 0x0c && y1 <= 0x0e)
  {
    rownumber = 0;
    rowlength = rowlen[0];
    rowoffset = 5;
    if (x1 >= rowoffset && x1 <= rowoffset + rowlength)
    {
      keyoffset = rowlength + rowoffset - x1;
      keypress = row0[keyoffset];
    }
    else
    {
      keyoffset = 0;
    }
  }
  else if (y1 >= 0x0f && y1 <= 0x11)
  {
    rownumber = 1;
    rowlength = rowlen[1];
    rowoffset = 6;
    if (x1 >= rowoffset && x1 <= rowoffset + rowlength)
    {
      keyoffset = rowlength + rowoffset - x1;
      keypress = row1[keyoffset];
    }
    else
    {
      keypress = 0;
    }
  }
  else if (y1 >= 0x12 && y1 <= 0x14)
  {
    rownumber = 2;
    rowlength = rowlen[2];
    rowoffset = 8;
    if (x1 >= rowoffset && x1 <= rowoffset + rowlength)
    {
      keyoffset = rowlength + rowoffset - x1;
      keypress = row2[keyoffset];
    }
    else
    {
      keypress = 0;
    }
  }
  else if (y1 >= 0x15 && y1 <= 0x17)
  {
    rownumber = 3;
    rowlength = rowlen[3];
    rowoffset = 10;
    if (x1 >= rowoffset && x1 <= rowoffset + rowlength)
    {
      keyoffset = rowlength + rowoffset - x1;
      keypress = row3[keyoffset];
    }
    else
    {
      keypress = 0;
    }
  }
  else
  {
    keypress = 0;
  }
  if (rownumber > 0)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(xd, yd, xd + 10, yd + 10);
  }
  return keypress;
}
char lookupControl(int x, int y)
{
  int keycol, keyrow, rowcount, rowoffset;
  char c1, c2, c3, c4;
  int row, col;
  int b;
  char keypress;
  int xd, yd;
  int x1, y1;
  int keyoffset;
  int rowlen[4];
  int rowlength;

  rowlen[0] = 1;

  xd = x / 9;
  yd = y / 8;

  yd = 272 - yd;
  yd = yd + 20;

  xd = xd * 9 / 8;

  x1 = xd;
  y1 = yd;


  x1 = x1 / 10;
  y1 = y1 / 10;

  x1 = int (x1 / 2);

  if (y1 >= 0x0c && y1 <= 0x0e)
  {
    keypress = 'A';
  }
  else
  {
    keypress = 0;
  }
  return keypress;
}

void paintCalculator()
{
  //char calckeys[] = {"C","CE","SQUAREROOT","/","7","8","9","*","4","5","6"."-","1","2","3","+","0",".","PLUSMINUS","="};
  char calckeys[20];
  calckeys[16] = '*';
  calckeys[17] = '+';
  calckeys[18] = '-';
  calckeys[19] = '=';
  calckeys[12] = '6';
  calckeys[13] = '3';
  calckeys[14] = 'P';
  calckeys[15] = '/';
  calckeys[8] = '2';
  calckeys[9] = '0';
  calckeys[10] = 'Q';
  calckeys[11] = '9';
  calckeys[4] = '.';
  calckeys[5] = 'S';
  calckeys[6] = '8';
  calckeys[7] = '5';
  calckeys[0] = 'C';
  calckeys[1] = '7';
  calckeys[2] = '4';
  calckeys[3] = '1';

  char currentkey;
  uint16_t theChar[16];
  uint16_t *ptr;
  //digitalWrite(1,0);
  int buf[478];
  int x, x2;
  int y, y2;
  int r;

  // Clear the screen and draw the frame
  myGLCD.clrScr();
  //  myGLCD.setFont(SmallerFont);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 479, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 258, 479, 271);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  delay(1000);
  myGLCD.setColor(255, 255, 255);
  int b = 0;
  int a = 0;
  int i = 1;
  int j = 1;
  while (a < 20)
  {
    currentkey = calckeys[a];
    if (currentkey == 'Q')
    {
      ptr = theChar;
      for (int k = 0; k < 16; k++)
      {
        *ptr++ = *(squareroot + k);
      }
    }
    else if (currentkey == 'S')
    {
      b = 0;

      ptr = theChar;
      for (int k = 0; k < 16; k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b * 0x10) + k);
      }
    }
    else if (currentkey == 'P')
    {
      ptr = theChar;
      for (int k = 0; k < 16; k++)
      {
        *ptr++ = *(plusminus + k);
      }
    }
    else if (currentkey == 'C' || currentkey == '=')
    {
      b = currentkey - 0x20 - 2;

      ptr = theChar;
      for (int k = 0; k < 16; k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b * 0x10) + k);
      }
    }
    else
    {
      b = currentkey - 0x20;

      ptr = theChar;
      for (int k = 0; k < 16; k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b * 0x10) + k);
      }
    }
    myGLCD.printLarge(theChar, 175 + i * 40, j * 40, 0);
    i += 1;
    if (i == 6)
    {
      j += 1;
      i = 1;
    }
    a += 1;
  }
  delay(10);
}
