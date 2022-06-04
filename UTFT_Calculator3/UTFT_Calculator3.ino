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

#include <UTFT.h> 
#include "Calculator.h"
#include <avr/pgmspace.h>
// Declare which fonts we will be using
extern uint8_t SmallFont[];
 
// Uncomment the next line for Arduino 2009/Uno 
//UTFT myGLCD(ITDB32S,19,18,17,16);   // Remember to change the model parameter to suit your display module!


// Declare which fonts we will be using
extern uint8_t SmallerFont[];

// Uncomment the next line for Arduino 2009/Uno
//UTFT myGLCD(ITDB43,19,18,17,16);   // Remember to change the model parameter to suit your display module!
UTFT myGLCD(SSD1963_480,5,4,3,2,9,8,7,6); 
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

Calculator* myCalculator = new Calculator(myGLCD);

void setup()
{
  DDRD = B11111111;  // Make Digital lines 0-7 Output
  DDRB = B11111111;  // Make Digital lines 8-13 Output
  digitalWrite(3,HIGH); // Set LCD_CS High
  digitalWrite(2,HIGH); // Set LCD_RESET High
  delayMicroseconds(100); // Wait 100 Microseconds
  digitalWrite(2,LOW);  // Put LCD_RESET Low
  delayMicroseconds(100); // For !00 Microseconds
  digitalWrite(2,HIGH); // Then bring LCD_RESET High
  digitalWrite(3,LOW); // and enable LCD_CS
   //Serial.begin(9600);
  //randomSeed(analogRead(0));
    pinMode(HI,OUTPUT);
  pinMode(LO,OUTPUT);
  pinMode(DATA,  OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(RESDATA, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
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
  paintCalculator();
  //digitalWrite(3,HIGH);
  delay(10);
  myGLCD.setColor(255,255,255);
  //digitalWrite(3,HIGH);
  //digitalWrite(2,HIGH);
//  myGLCD.setFont(SmallerFont);
  myGLCD.spistar();
}
void printHex(unsigned int x,char &c1,char &c2,char &c3,char &c4)
{
  unsigned int x1,x2,x3,x4;
  char zero = '0';
  char aaaa = 'A';
  char bbbb = 'Z';

  x1 = floor(x/4096);
  x = x - x1 * 4096;
  x2 = floor(x/256);
  x = x - x2 * 256;
  x3 = floor(x/16);
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
void printDec(unsigned int x,int r,int c)
{
  unsigned int x1,x2,x3,x4,x5;
  char c1,c2,c3,c4,c5;
  char zero = '0';
  char aaaa = 'A';

  x1 = x/10000;
  x = x - x1 * 10000;
  x2 = x/1000;
  x = x - x2 * 1000;
  x3 = x/100;
  x = x - x3 * 100;
  x4 = x/10;
  x5 = x - x4 * 10;
  

    c1 = zero + x1 + 2;
    c2 = zero + x2 + 2;
    c3 = zero + x3 + 2;
    c4 = zero + x4 + 2;
    c5 = zero + x5 + 2;

  delay(10);
  if (x1 != 0)
  {
    myGLCD.putChar(c1,r,c--);
  }
  delay(10);
  if (x2 != 0)
  {
    myGLCD.putChar(c2,r,c--);
  }
  delay(10);
  if (x3 != 0)
  {
    myGLCD.putChar(c3,r,c--);
  }
  delay(10);
  if (x4 != 0)
  {
      myGLCD.putChar(c4,r,c--);
  }
  delay(10);
  myGLCD.putChar(c5,r,c--);
  delay(10);
}
void getLargeChar(char currentKey,uint16_t theChar)
{
    uint16_t *ptr;
    int b;

    if (currentKey == 'Q')
    {
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = *(squareroot+k);    
      }
    }
    else if (currentKey == 'S')
    {
      b = 0;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }      
    }
    else if (currentKey == 'P')
    {
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = *(plusminus+k);    
      }
    }
    else if (currentKey == 'C' || currentKey == '=' || currentKey == '.')
    {
      b = currentKey - 0x20 - 2;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }      
    }
    else
    {
      b = currentKey - 0x20;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }
    }
}
void loop()
{
    int col1[5] = {KEY_CLEAR,KEY_SEVEN,KEY_FOUR,KEY_ONE,KEY_DECIMALPOINT};
    int col2[5] = {KEY_SPACE,KEY_EIGHT,KEY_FIVE,KEY_TWO,KEY_ZERO};
    int col3[5] = {KEY_SQUAREROOT,KEY_NINE,KEY_SIX,KEY_THREE,KEY_PLUSMINUS};
    int col4[5] = {KEY_DIVIDE,KEY_MULTIPLY,KEY_PLUS,KEY_MINUS,KEY_EQUAL};
    int keycol,keyrow;
    int *colptr;
    uint16_t *ptr;
    uint16_t theChar[16];
    int b;
      int calcState;
      int inputType;
      int inputKeystroke;
      char charKeystroke;
      char charType;
      char charState;

    
    
    int x,y;
    myGLCD.AD7843_On();
    x = myGLCD.AD7843_X();
    y = myGLCD.AD7843_Y();
    myGLCD.AD7843_Off();

    int xb,yb;

    xb = x; // - 0x100;
    yb = y; // - 0x100;

    int xc,yc;

    xc = xb; // - 0x35;
    yc = yb; // - 0x130;

    int xd,yd;

    xd = xc / 0x10;
    yd = yc / 0x10;

    xd = xc / 9;
    yd = yc / 8;

    yd = 272 - yd;
    yd = yd + 20;

    xd = xd * 9 / 8;

    int x1,y1,x2,y2;
    x1 = xd;
    y1 = yd;
    x2 = x1 + 3;
    y2 = y1 + 3;
    
//    myGLCD.drawVLine(x1,0,272);
/*
    char c1,c2,c3,c4;
    int row,col;
    row = 2;
    col = 6;
    printHex(x1,c1,c2,c3,c4);
    myGLCD.putChar(c4,row,col);
    delay(10);
    col++;
    myGLCD.putChar(c3,row,col);
    col++;
    myGLCD.putChar(c2,row,col);
    delay(10);
    col++;
    myGLCD.putChar(c1,row,col);
    
    //delay(10);
    row = 6;
    col = 12;
    delay(10);
    printHex(y1,c1,c2,c3,c4);
    myGLCD.putChar(c4,row,col);
    delay(10);
    col++;
    myGLCD.putChar(c3,row,col);
    col++;
    delay(10);
    myGLCD.putChar(c2,row,col);
     col++;
    delay(10);
    myGLCD.putChar(c1,row,col);
*/
     if (y1 > 0xFE75 && y1 < 0xFFA0)
     {
      keycol=1;
      colptr = col1;
     }
     else if (y1 > 0xFFA0 && y1 <= 0x0)
     {
      keycol=2;
      colptr = col2;
     }
     else if (y1 > 0x0 && y1 <= 0x0040)
     {
      keycol=3;
      colptr = col3;
     }
     else if (y1 > 0x0040 && y1 <= 0x0080)
     {
      keycol=4;
      colptr = col4;
     }
     else
     {
      keycol = 0;
     }

     if (x1 >= 0x00DB && x1 <= 0x010A)
     {
      keyrow = 0;
     }
     else if (x1 >= 0x010A && x1 <= 0x0135)
     {
      keyrow = 1;
     }
     else if (x1 >= 0x0135 && x1 <= 0x0156)
     {
      keyrow = 2;
     }
     else if (x1 >= 0x0156 && x1 <= 0x018A)
     {
      keyrow = 3;
     }
     else if (x1 >= 0x018A && x1 <= 0x0210)
     {
        keyrow = 4;
     }
     else
     {
        keyrow = 5;
     }

     int keypress;

     if (keyrow == 5 || keycol == 0) // press occurs outside the keypad
     {
      keypress = KEY_SPACE; // Print a space
     }
     else
     {
        keypress = *(colptr+keyrow);
     }

    myCalculator->putKeystroke(keypress);

    charKeystroke = keycodes[keypress];
    getLargeChar(charKeystroke,theChar);
    myGLCD.printLarge(theChar,20*myCalculator->getOutputRow(),9*20,0);

    if (keypress == KEY_CLEAR || myCalculator->getInputType() == C_CLEAR)
    {
      x1 = 10;
      y1 = 10;
      x2 = 200;
      y2 = 200;
      myGLCD.setColor(0,0,0);
      myGLCD.fillRect(x1,y1,x2,y2);
    }
    else if (keypress != KEY_SPACE)
    {
      calcState = myCalculator->getCalculatorState();

      inputType = myCalculator->getInputType();
      inputKeystroke = myCalculator->getKeystroke();
      charKeystroke = keycodes[inputKeystroke];
      charType = inputType + '0';
      charState = calcState + '0';

//      uint16_t theChar[16];
/*
      getLargeChar(charKeystroke,theChar);
      myGLCD.printLarge(theChar,20,40,0);
      getLargeChar(charType,theChar);
      myGLCD.printLarge(theChar,20,60,0);
      getLargeChar(charState,theChar);
      myGLCD.printLarge(theChar,20,80,0);
*/

      myCalculator->displayOperand(myCalculator->getOperandNo(),myCalculator->getOutputRow(),7,&myGLCD);
      if (myCalculator->getInputType() == C_EQUAL)
      {
        myCalculator->clearCalculator();
        myCalculator->setInputType(C_CLEAR);
      }
      delay(10);      
    }
}
void displayOutput(float value,int numberOfDigits,int numberOfPlaces)
{
  
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
  myGLCD.setColor(255,255,255);
  int b = 0;
  int a = 0;
  int i = 1;
  int j = 1;
  while(a < 20)
  {
    currentkey = calckeys[a];
    if (currentkey == 'Q')
    {
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = *(squareroot+k);    
      }
    }
    else if (currentkey == 'S')
    {
      b = 0;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }      
    }
    else if (currentkey == 'P')
    {
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = *(plusminus+k);    
      }
    }
    else if (currentkey == 'C' || currentkey == '=')
    {
      b = currentkey - 0x20 - 2;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }      
    }
    else
    {
      b = currentkey - 0x20;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }
    }
    myGLCD.printLarge(theChar,175+i*40,j*40,0);
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
