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
#include "Clock_OLED.h"
#include "Keys.h"
#include "Terminal.h"
#include <avr/pgmspace.h>
#include <Wire.h>
#include "ds3231.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>

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
int rowno;
int intValue;
int previousValue = 1;
int x, y;
int intReceiveCounter = 0;
int a = 0;
int lockInput;
//int intValue;
char b;
boolean start;
int count;
uint16_t theChar[16];
//int currentrow = 1;
int rrow = 12;
int ccol = 1;
// Variables for the Clock
uint8_t time[8];
unsigned int recv_size = 0;
unsigned long prev, interval = 5000;

int intHour, intMin;
int hrA_prev, hrB_prev, mnC_prev, mnD_prev;
unsigned int intHeartbeat = 0;

Calculator* myCalculator = new Calculator();
Clock myClock = Clock(200, 120, 150);

// Initialize the clock
Clock_OLED *myClockOLED = new Clock_OLED(2, 8, 14, 24);

SevenSegment myLEDA1 = SevenSegment(130,10,20,30);
SevenSegment myLEDA2 = SevenSegment(160,10,20,30);
SevenSegment myLEDA3 = SevenSegment(190,10,20,30);
SevenSegment myLEDA4 = SevenSegment(220,10,20,30);
SevenSegment myLEDA5 = SevenSegment(250,10,20,30);

SevenSegment myLEDB1 = SevenSegment(330,10,20,30);
SevenSegment myLEDB2 = SevenSegment(360,10,20,30);
SevenSegment myLEDB3 = SevenSegment(390,10,20,30);
SevenSegment myLEDB4 = SevenSegment(420,10,20,30);
SevenSegment myLEDB5 = SevenSegment(450,10,20,30);


extern Keys theKeys;
extern Terminal theTerminal;
char matrix[100];

char time_buff[100];
int TIME_BUFF_MAX=100;

int but1X = 400;
int but1Y = 50;

int butWidth = 25;
int xe, ye;

//uint8_t time[8];
//unsigned int recv_size = 0;
//unsigned long prev, interval = 5000;

int colonStatus;
//int hrA_prev, hrB_prev, mnC_prev, mnD_prev;
//unsigned int intHeartbeat = 0;
int intPushButtons = 0;
double dblTime;
int clockRefresh;
int intSetClockButton;
int intLeftButton;
int intRightButton;
int heartbeatRefresh;


void setup()
{
  // Initialize status of blinking colon to OFF.
//  colonStatus = 0;
  // Initialize previous values of all four digits to -1: not yet used.
  hrA_prev = -1;
  hrB_prev = -1;
  mnC_prev = -1;
  mnD_prev = -1;
  clockRefresh = 5;
  heartbeatRefresh = 4;
  intSetClockButton = 0;
  intLeftButton = 0;
  intRightButton = 0;

  DDRD = B11111111;  // Make Digital lines 0-7 Output
  DDRB = B11111111;  // Make Digital lines 8-13 Output
  digitalWrite(3, HIGH); // Set LCD_CS High
  digitalWrite(2, HIGH); // Set LCD_RESET High
  delayMicroseconds(100); // Wait 100 Microseconds
  digitalWrite(2, LOW); // Put LCD_RESET Low
  delayMicroseconds(100); // For !00 Microseconds
  digitalWrite(2, HIGH); // Then bring LCD_RESET High
  digitalWrite(3, LOW); // and enable LCD_CS
  Serial.begin(9600);
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
  //drawGrid();
  myGLCD.fillRect(0,0,479,271);
  //myGLCD.spistar();
  rowno = 1;
  /*
  //digitalWrite(3,HIGH);
  //digitalWrite(2,HIGH);
  //  myGLCD.setFont(SmallerFont);
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
  intValue = 1;
  previousValue = 1;
    // Initialize the clock
  Wire.begin();                // join i2c bus with as the master
//  DS3231_init(DS3231_CONTROL_INTCN);  // This is commented out because it didn't work.
//  DS3231_clear_a1f();   // Ditto
  Serial.println("READY");
  intReceiveCounter = 0;
  lockInput = 0;
  // Temperature
  myLEDA1.setBlackColor();
  myLEDA2.setBlackColor();
  myLEDA3.setBlackColor();
  myLEDA4.setBlackColor();
  myLEDA5.setBlackColor();
  myLEDA1.eraseDigit();
  myLEDA2.eraseDigit();
  myLEDA3.eraseDigit();
  myLEDA4.eraseDigit();
  myLEDA5.eraseDigit();
  myLEDB1.setBlackColor();
  myLEDB2.setBlackColor();
  myLEDB3.setBlackColor();
  myLEDB4.setBlackColor();
  myLEDB5.setBlackColor();
  myLEDB1.eraseDigit();
  myLEDB2.eraseDigit();
  myLEDB3.eraseDigit();
  myLEDB4.eraseDigit();
  myLEDB5.eraseDigit();
  // Buttons
  int xx1,yy1,xx2,yy2;
  xx1 = but1X;
  yy1 = but1Y;
  xx2 = xx1 + butWidth;
  yy2 = yy1 + butWidth;
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(xx1,yy1,xx2,yy2);
  myGLCD.spistar();
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
  int x1, x2, x3, x4, x5;
  char c1, c2, c3, c4, c5;
  char zero = '0';
  char aaaa = 'A';
  int alreadyPut = 0;
      int intValue;
    char b;
    boolean start;
    int count;
    uint16_t theChar[16];
    int currentrow = 1;
    int rrow = r;
    int ccol = c;


  x1 = (x - fmod(x , 10000))/10000;
  x = fmod(x, 10000);
  x2 = (x - fmod(x , 1000))/1000;
  x = fmod(x, 1000);
  x3 = (x - fmod(x, 100))/100;
  x = fmod(x, 100);
  //x = 99
  //fmod(x,10) = 9
  x4 = (x - fmod(x, 10))/10;
  // x4 = 9
  // x5 = 9
  x5 = fmod(x,10);


  c1 = zero + x1;
  c2 = zero + x2;
  c3 = zero + x3;
  c4 = zero + x4;
  c5 = zero + x5;

  delay(10);
          //getLargeChar(c1,theChar);
          //myGLCD.printLarge(theChar,rrow,ccol,1);
    //rrow -= 20;
          getLargeChar(c2,theChar);
          myGLCD.printLarge(theChar,rrow,ccol,1);
    rrow -= 20;
          getLargeChar(c3,theChar);
          myGLCD.printLarge(theChar,rrow,ccol,1);
    rrow -= 20;
          getLargeChar(c4,theChar);
          myGLCD.printLarge(theChar,rrow,ccol,1);
    rrow -= 20;
          getLargeChar(c5,theChar);
          myGLCD.printLarge(theChar,rrow,ccol,1);
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
void readTime()
{
    char buff[100];
    int BUFF_MAX = 100;
    unsigned long now = millis();
    struct ts t;
    int prevAMPM;
    DS3231_get(&t);
    delay(1);
    //snprintf(buff, BUFF_MAX, "%d.%02d.%02d %02d:%02d:%02d", t.year,t.mon, t.mday, t.hour, t.min, t.sec);
    //Serial.println(buff);
    //delay(1000);
    intHour = t.hour;
    intMin = t.min;
    //Serial.println(intHour);
    //Serial.println(intMin);
    //snprintf(time_buff, TIME_BUFF_MAX, "%d %d^", t.hour, t.min);
    //Serial.println(time_buff);
    //delay(1000);
    /*
    this->hr = t1.hour;
    this->mn = t1.min;

    prevAMPM = this->amOrPm;
    this->amOrPm = 0;
    if (this->hr >= 12)
    {
        this->hr = this->hr - 12;
        this->amOrPm = 1;
    }
    // The first time after initialation set AM/PM to be redrawn.
    if (this-AMPMChanged == -1)
    {
      this->AMPMChanged = 1;
    }
    else
    {
      if (this->amOrPm != prevAMPM)
      {
        this->AMPMChanged = 1;
      }
      else
      {
        this->AMPMChanged = 0;
      }
    }
    if (this->hr == 0)
    {
      this->hr = 12;
    }
    // Set the variables to be ready to change the time.
    if (intMode == 0)
    {
        this->setHr = this->hr;
        this->setMn = this->mn;
        this->setAMPM = this->amOrPm;
    }
    this->mYear = t1.year;
    this->mMonth = t1.mon;
    this->mDay = t1.mday;
     
    if (intMode == 0)
    {
      this->setMonth = this->mMonth;
      this->setYear = this->mYear;
      if (this->setYear < 2019)  //If just starting set Year to 2020.
      {
        this->setYear = 2020;
      }
      this->setDay = this->mDay;
    }
    */
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
void drawGrid()
{
  int i,j;
  int xoffset,yoffset;

  xoffset = 5;
  yoffset = 5;

  for (i=0;i<460;i=i+40)
  {
    for (j=0;j<260;j=j+40)
    {
      myGLCD.drawRect(i+xoffset,j+yoffset,i+xoffset+20,j+yoffset+20);
    }
  }
}
void loop()
{
    int intAlarmOn, intMode;
    double dblDelay;

    int xx1,xx2,yy1,yy2;
    uint16_t *ptr;
    int b;
    int a;
    int intValue;
    char matrix[100];
//    char b;
    boolean start;
    int count;

    start = false;
    count = 0;
    a = 0;
    char f;
    int intBreak = 0;

    int g,h;
    g = 10;
    h = 10;
/*
    Wire.beginTransmission(8);
    Wire.write(2);
    Wire.endTransmission();
    rrow = 12;
    ccol = 1;
    readtemp();
    Wire.beginTransmission(8);
    Wire.write(1);
    Wire.endTransmission();
    */
    Wire.requestFrom(8,1);
    int isTouched = 0;
    if (Wire.available() > 0)
    {
        isTouched = Wire.read();
    }
    if (isTouched == 1)
    {
        getTouch();
        paintTouch(x,y);
        isTouched = 0;
    }
    if (intSetClockButton == 0)
    {
      if ((xe > 350 && xe < 450) && (ye > 25 && ye < 75))
      {
        xx1 = 425;
        xx2 = 450;
        yy1 = 100;
        yy2 = 125;
        myGLCD.setColor(0,0,0);
        myGLCD.fillRect(xx1,yy1,xx2,yy2);
        xx1 = 375;
        xx2 = 400;
        yy1 = 100;
        yy2 = 125;
        myGLCD.fillRect(xx1,yy1,xx2,yy2);
        xx1 = but1X;
        yy1 = but1Y;
        xx2 = xx1 + butWidth;
        yy2 = yy1 + butWidth;
        myGLCD.setColor(255,255,255);
        myGLCD.fillRect(xx1,yy1,xx2,yy2);
        myClockOLED->setClockTime();
        intSetClockButton = 1;
      }
    }
    if (intLeftButton == 0 && intSetClockButton == 1)
    {
      if ((xe > 425 && xe < 450) && (ye > 100 && ye < 125))
      {
        intLeftButton = 1;
      }
    }
    if (intRightButton == 0 && intSetClockButton == 1)
    {
      if ((xe > 375 && xe < 400) && (ye > 100 && ye < 125))
      {
        intRightButton = 1;
      }
    }
    delay(1);
  intMode = myClockOLED->getMode();
  if (intMode == 0)
  {
    if (clockRefresh == 20)
    {
        myClockOLED->readTime();
        myClockOLED->displayTime();
        clockRefresh = 0;
    }
  }
  else if (intMode == 1)
  {
        if (intLeftButton == 1)
        {
          myClockOLED->incrementHours();
          intLeftButton = 0;
        }
        else if (intRightButton == 1)
        {
          myClockOLED->setHours();
          intRightButton = 0;
        }
  }
  else if (intMode == 2)
  {
        if (intLeftButton == 1)
        {
          myClockOLED->incrementMinutes();
          intLeftButton = 0;
        }
        else if (intRightButton == 1)
        {
          myClockOLED->setMinutes();
          intRightButton = 0;
        }
  }
  else if (intMode == 3)
  {
      if (intLeftButton == 1)
      {
          myClockOLED->toggleAMPM();
          intLeftButton = 0;
      }
      else if (intRightButton == 1)
      {
          myClockOLED->setTimeOfDay();
          intRightButton = 0;
      }
  }
  else if (intMode == 4)
  {
        if (intLeftButton == 1)
        {
          myClockOLED->incrementMonth();
          intLeftButton = 0;
        }
        else if (intRightButton == 1)
        {
          myClockOLED->setMonthValue();
          intRightButton = 0;
        }
  }
  else if (intMode == 5)
  {
        if (intLeftButton == 1)
        {
          myClockOLED->incrementDay();
          intLeftButton = 0;
        }
        else if (intRightButton == 1)
        {
          myClockOLED->setDayValue();
          intRightButton = 0;
        }
  }
  else if (intMode == 6)
  {
        if (intLeftButton == 1)
        {
          myClockOLED->incrementYear();
          intLeftButton = 0;
        }
        else if (intRightButton == 1)
        {
          myClockOLED->setYearValue();
          intRightButton = 0;
        }
  }
  else if (intMode == 7)
  {
    
  }
  clockRefresh += 1;
  intHeartbeat = !intHeartbeat; // toggles the Heartbeat
  if (heartbeatRefresh == 4)
  {
    heartbeatRefresh = 0;
    myClockOLED->heartbeatCallback();
  }
  else
  {
    heartbeatRefresh += 1;
  }
  delay(250);
}
void readtemp()
{
    int a;
    int intValue;
    char matrix[100];
    char b;
    boolean start;
    int count;
    uint16_t theChar[16];

    start = false;
    count = 0;
    a = 0;
    while (a < 100)
    {
       Wire.requestFrom(8,1);
       delay(1);
       if (Wire.available() > 0)
       {
          intValue = Wire.read();
          delay(1);
          matrix[a] = intValue;
          a++;
       }
       delay(1); 
    }
    myLEDA1.eraseDigit();
    myLEDA2.eraseDigit();
    myLEDA3.eraseDigit();
    myLEDA4.eraseDigit();
    myLEDA5.eraseDigit();
    myLEDB1.eraseDigit();
    myLEDB2.eraseDigit();
    myLEDB3.eraseDigit();
    myLEDB4.eraseDigit();
    myLEDB5.eraseDigit();
    for (int i = 0; i<a; i++)
    {
        b = matrix[i];
        count++;
        if (b == 0)
        {
          b = 'X';
        }
        if (b == '=')
        {
          ccol += 1;
          rrow = 12;
          if (ccol == 12)
          {
              ccol = 1;
          }
          start = false;
          count = 0;
        }
        if (b == 'C' || b == 'D' || b == 'E' || b == 'F')
        {
          start = true;
          count = 0;
          if (b == 'C')
          {
            ccol = 1;
          }
          if (b == 'D')
          {
            ccol = 2;
          }
          if (b == 'E')
          {
            ccol = 3;
          }
          if (b == 'F')
          {
            ccol = 4;
          }
        }
        if (start == true && count > 1)
        {
          b -= 2;
          //getLargeChar(b,theChar);
           //myGLCD.printLarge(theChar,20*rrow,ccol*20,1);
          if (ccol == 1)
          {
              if (rrow == 12)
              {
                myLEDA1.drawDigit(b); 
              }
              else if (rrow == 11)
              {
                myLEDA2.drawDigit(b);
              }
              else if (rrow == 10)
              {
                myLEDA3.drawDigit(b);
              }
              else if (rrow == 9)
              {
                myLEDA4.drawDigit(b);
              }
              else
              {
                myLEDA5.drawDigit(b);
              }
          }
          else if (ccol == 2)
          {
              if (rrow == 12)
              {
                myLEDB1.drawDigit(b); 
              }
              else if (rrow == 11)
              {
                myLEDB2.drawDigit(b);
              }
              else if (rrow == 10)
              {
                myLEDB3.drawDigit(b);
              }
              else if (rrow == 9)
              {
                myLEDB4.drawDigit(b);
              }
              else
              {
                myLEDB5.drawDigit(b);
              }
          }
          //myGLCD.printChar(b,rrow*13,ccol*13,1);
          delay(10);
          rrow -= 1;
          if (rrow == 1)
          {
            rrow = 12;
            ccol += 1;
            if (ccol == 12)
            {
               rrow = 12;
               ccol = 1;
            }
          }
        }
    }
    delay(1);
}
void showReadings()
{
    int intValue;
    char b;
    boolean start;
    int count;
    uint16_t theChar[16];
    int currentrow = 1;
    int rrow = 12;
    int ccol = 1;

    for (int i = 0; i<a; i++)
    {
        b = matrix[i];
       // Serial.print(b);
        count++;
        if (b == 0)
        {
          b = 'X';
        }
        if (b == '=')
        {
          ccol += 1;
          rrow = 12;
          if (ccol == 12)
          {
              ccol = 1;
          }
          start = false;
          count = 0;
        }
        if (b == 'C' || b == 'D' || b == 'E' || b == 'F')
        {
          start = true;
          count = 0;
          if (b == 'C')
          {
            ccol = 1;
          }
          if (b == 'D')
          {
            ccol = 2;
          }
          if (b == 'E')
          {
            ccol = 3;
          }
          if (b == 'F')
          {
            ccol = 4;
          }
        }
        if (start == true && count > 1)
        {
          b -= 2;
          getLargeChar(b,theChar);
          myGLCD.printLarge(theChar,20*rrow,ccol*20,1);

          //myGLCD.printChar(b,rrow*13,ccol*13,1);
          delay(10);
          rrow -= 1;
          if (rrow == 1)
          {
            rrow = 12;
            ccol = 1;
            
            ccol += 1;
            if (ccol == 12)
            {
               rrow = 12;
               ccol = 1;
            }
            
          }
        }
    }
}
void receiveEvent(int howMany)
{
  int b = 0;
  int a = 0;
  //Serial.println("RECEIVE");
    //Serial.println("SENSOR");
    while (Wire.available() > 0)
    {
          b = Wire.read();
          //Serial.print(b);
          matrix[a] = b;
          a++;
    }
    previousValue = 0;
}
void getTouch()
{
  int i, j;
  char currentkey;
  char currentControl;
  uint16_t theChar[16];
  uint16_t *ptr;
  int b;
/*
*/
   myGLCD.AD7843_On();
   x = myGLCD.AD7843_X();
   y = myGLCD.AD7843_Y();
   myGLCD.AD7843_Off();

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
  int x1, y1;
  float xd,yd;

  xd = x / 8;
  yd = y / 12.5;

  yd = yd - 20;
  ye = 272 - yd;
  //ye = ye + 60;

  xe = xd - 25;

  x1 = xe;
  y1 = ye;


  x1 = x1 / 10;
  y1 = y1 / 10;

  x1 = int (x1 / 2);

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(xe, ye, xe + 10, ye + 10);

  //printDec(xe,rowno,10);
  //printDec(ye,rowno,20);

  //rowno = rowno + 1;
  //if (rowno == 20)
  //{
   // rowno = 1;
  //}
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
