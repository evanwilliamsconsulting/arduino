/***********************************************************************
 * Clock_OLED.cpp
 * 
 * Clock //display Class for Arduion (for OLED)
 * by Evan J. Williams
 * July 24, 2020
 * GPL - General Purpose License
 * 
 * This is a class to draw and update a clock on the OLED //display.
 * 
 */
#include "Clock_OLED.h"

/*
 * SevenSegment Digit Constructor
 *    left_x: the leftmost position of the digit
 *    top_Y: the top position of the digit
 *    digit_width: the width of the digit
 *    digit_height: the height of the digit
 */
Clock_OLED::Clock_OLED(double left_x,double top_y,double digit_width,double digit_height)
{
  double right_x,bottom_y,line_width,line_height;
  this->left_x = left_x;
  this->top_y = top_y;
  this->digit_height = digit_height;
  this->digit_width = digit_width;
  // Compute the remainders
  right_x = left_x  + digit_width * 4;
  this->right_x = right_x;
  bottom_y = top_y + digit_height;
  this->bottom_y = bottom_y;
  this->half_y = top_y + (bottom_y - top_y) / 2;

  this->segHr10 = SevenSegment(300,100,50,80);
  this->segHr1 = SevenSegment(240,100,50,80);
  this->segMin10 = SevenSegment(170,100,50,80);
  this->segMin1 = SevenSegment(110,100,50,80);

  this->indicatorAMPM = AMPM(50,100,50,80);
  
  this->segYr4 = SevenSegment(160,200,15,25);
  this->segYr3 = SevenSegment(140,200,15,25);
  this->segYr2 = SevenSegment(120,200,15,25);
  this->segYr1 = SevenSegment(100,200,15,25);
  
  this->segMth2 = SevenSegment(260,200,15,25);
  this->segMth1 = SevenSegment(240,200,15,25);
  
  this->segDay2 = SevenSegment(210,200,15,25);
  this->segDay1 = SevenSegment(190,200,15,25);

  this->segHr10.setBlackColor();
  this->segHr1.setBlackColor();
  this->segMin10.setBlackColor();
  this->segMin1.setBlackColor();
  this->indicatorAMPM.setBlackColor();
  this->segYr4.setBlackColor();
  this->segYr3.setBlackColor();
  this->segYr2.setBlackColor();
  this->segYr1.setBlackColor();
  this->segMth1.setBlackColor();
  this->segMth2.setBlackColor();
  this->segDay2.setBlackColor();
  this->segDay1.setBlackColor();

//  this->myDigitA = SevenSegment(2,8,14,24);
//  this->myDigitB = SevenSegment(26,8,14,24);
//  this->myDigitC = SevenSegment(52,8,14,24);
//  this->myDigitD = SevenSegment(76,8,14,24);

// this->myDigitA.blankZero();
 this->setStartVariables();
 this->setYear = 2019;   // Start year out a 2019
}
// Initiazes variables required to trigger redraw of screen elements.
void Clock_OLED::setStartVariables()
{
 this->intMode = 0;
 this->hrA_prev = -1; // Start out by redrawing screen.
 this->hrB_prev = -1;
 this->dateChanged = 1; // Start out by drawing date.
 this->blinkDay = 0;
 this->blinkMonth = 0;
 this->blinkYear = 0; 
 this->AMPMChanged = -1;  // Did the AM PM setting changed.  Start out -1 to draw anyway.
 // Alarm setting defaults to 6AM.
 this->alarmHr = 6;
 this->alarmMn = 0;
 this->alarmAMPM = 0;
}
Clock_OLED::readTime()
{
    char buff[100];
    unsigned long now = millis();
    struct ts t1;
    int prevAMPM;
    DS3231_get(&t1);

    //snprintf(buff, BUFF_MAX, "%d.%02d.%02d %02d:%02d:%02d", t.year,t.mon, t.mday, t.hour, t.min, t.sec);
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
}
void Clock_OLED::setTime()
{
      struct ts tset;

    // TssmmhhWDDMMYYYY aka set time
    //T355720619112011
    tset.sec = 0;
    tset.min = this->setMn;
    // I thought that this should test for 0
    // But I guess that the toggle is 1 ahead.
    if (this->setAMPM == 1)
    {
      tset.hour = this->setHr;
    }
    else
    {
      tset.hour = this->setHr + 12;          
    }
    tset.wday = 1;
    tset.mday = this->setDay;
    tset.mon = this->setMonth;
    tset.year = this->setYear;
    DS3231_set(tset);
}
void Clock_OLED::setAlarm()
{
    // flags define what calendar component to be checked against the current time in order
    // to trigger the alarm - see datasheet
    // A1M1 (seconds) (0 to enable, 1 to disable)
    // A1M2 (minutes) (0 to enable, 1 to disable)
    // A1M3 (hour)    (0 to enable, 1 to disable) 
    // A1M4 (day)     (0 to enable, 1 to disable)
    // DY/DT          (dayofweek == 1/dayofmonth == 0)
    uint8_t flags[5] = { 0, 0, 0, 1, 1 };

    double alarmHour24;
    
    // set Alarm1
    if (this->alarmAMPM == 1)
    {
        alarmHour24 = this->alarmHr + 12;  
    }
    else
    {
      alarmHour24 = this->alarmHr;
    }
    DS3231_set_a1(0, this->alarmMn, alarmHour24, 0, flags);

    // activate Alarm1
    DS3231_set_creg(DS3231_CONTROL_INTCN | DS3231_CONTROL_A1IE);
}
int Clock_OLED::getMode()
{
  return this->intMode;
}
void Clock_OLED:: normalOperation()
{
  this->intMode= 0;
//  this->myDigitA.setBlinkOff();
//  this->myDigitB.setBlinkOff();
//  this->myDigitC.setBlinkOff();
//  this->myDigitD.setBlinkOff();
}
// Function for setting the Clock: First Step
int Clock_OLED::setClockTime()
{
  this->intMode = 1;
  this->segHr10.setBlinkOn();
  this->segHr1.setBlinkOn();
}
/* Function for Setting the Hours digits given a value for the hour. */
/* Returns integer to tell if hours changed */
int Clock_OLED::displayHours(int setHour)
{
    int hr1, hoursChanged;
    // Check to see if the tens place of hours is alrady //displayed.
    if (setHour < 10)
    {
       hr1 = setHour;
    }
    else
    {
        hr1 = setHour - 10;
    }
    this->segHr10.eraseDigit();
    if (setHour < 10)
    {
        this->segHr10.drawDigit(0);          
    }
    else
    {
        this->segHr10.drawDigit(1);
        hoursChanged = 1;
    }
    this->segHr1.eraseDigit();
    this->segHr1.drawDigit(hr1);
    hoursChanged = 1;
    
    return hoursChanged;
}
/* Function for Setting the Alarm: First Step */
void Clock_OLED::setAlarmTime()
{
  int hoursChanged;
  this->intMode = 7;
  // Erase Digits
//  this->myDigitA.eraseDigit();
//  this->myDigitB.eraseDigit();
//  this->myDigitC.eraseDigit();
//  this->myDigitD.eraseDigit();
  // Show Current Alarm Time
  // Check to see if the tens place of hours is alrady //displayed.
  hoursChanged = this->displayHours(this->alarmHr);  this->displayMinutes(this->alarmMn,hoursChanged);
  // Set AM or PM to AM
  if (this->alarmAMPM == 0)
  {
      this->erasePM();
      this->displayAM();
  }
  else
  {
     this->eraseAM();
     this->displayPM();
  }
  // Hours should blink because we are setting hours right now.

//  this->myDigitA.setBlinkOn();  // 2nd Hours Place should Blink
//  this->myDigitB.setBlinkOn();  // 1st Hours Place should Blink
//  this->myDigitC.setBlinkOff(); // Minutes should not blink
//  this->myDigitD.setBlinkOff(); // Minutes should not blink
  
  this->eraseDateString();  // Do not //display the date when we are setting the alarm
}
void Clock_OLED::incrementHours()
{
    int intHour;
    if (intMode == 7)
    {
      intHour = this->alarmHr;
    }
    else
    {
      intHour = this->setHr;
    }
    // Check to see if the tens place of hours is alrady //displayed.
    intHour += 1;
    if (intHour > 12)
    {
      intHour = 1;
    }
    if (intHour < 10)
    {
       this->intHrA = 0;
       this->intHrB = intHour;
    }
    else
    {
        this->intHrA = 1;
        this->intHrB = intHour - 10;
    }
    this->segHr10.eraseDigit();
    this->segHr1.eraseDigit();
    this->segHr10.drawDigit(this->intHrA);
    this->segHr1.drawDigit(this->intHrB);
    if (intMode == 7)
    {
      this->alarmHr = intHour;
    }
    else
    {
      this->setHr = intHour;
    }
}
void Clock_OLED::setHours()
{
   // Freeze setHr variable and move on to minutes.
   if (this->intMode == 1)
   {
      this->intMode = 2;
   }
   else
   {
      this->intMode = 8;
   }
   this->segHr10.setBlinkOff();
   this->segHr1.setBlinkOff();
   this->segHr10.eraseDigit();
   this->segHr1.eraseDigit();
   this->segHr10.drawDigit(this->intHrA);
   this->segHr1.drawDigit(this->intHrB);  
   this->segMin10.setBlinkOn();
   this->segMin1.setBlinkOn();
}
void Clock_OLED::incrementMinutes()
{
  int intMn;
  if (this->intMode == 2)
  {
    intMn = this->setMn;
  }
  else
  {
    intMn = this->alarmMn;
  }
  intMn += 1;
  if (intMn == 60)
  {
    intMn = 0;
  }
  // Redraw the minutes digits
  this->intMnD = fmod(intMn,10);
  this->intMnC = (intMn - fmod(intMn,10))/10;
  this->segMin10.eraseDigit();
  this->segMin1.eraseDigit();
  this->segMin10.drawDigit(this->intMnC);
  this->segMin1.drawDigit(this->intMnD);
  if (this->intMode == 2)
  {
    this->setMn = intMn; 
  }
  else
  {
    this->alarmMn = intMn;
  }
}
void Clock_OLED::setMinutes()
{
  int intMn;

  intMn = this->setMn;
  // Freeze setMn variable and move on to AM / PM
  if (this->intMode == 2)
  {
      if (this->amOrPm == 0)
      { 
          this->eraseAM();
          this->displayPM();
      }
      else
      {
          this->erasePM();
          this->displayAM();
      }
      // Set the latest value of AM or PM before entering Toggle AM / PM section.
      this->setAMPM = this->amOrPm;
      this->intMode= 3;
  }
  else
  {
    if (this->alarmAMPM == 0)
    {
      this->displayAM();
      this->erasePM();
      this->blinkAMPMOff();
    }
    else
    {
      this->displayPM();
      this->eraseAM();
      this->blinkAMPMOff();
    }
    this->intMode = 9;
  }
  this->segMin10.setBlinkOff();
  this->segMin1.setBlinkOff();
  this->intMnD = fmod(intMn,10);
  this->intMnC = (intMn - fmod(intMn,10))/10;
  this->segMin10.eraseDigit();
  this->segMin1.eraseDigit();
  this->segMin10.drawDigit(this->intMnC);
  this->segMin1.drawDigit(this->intMnD);
  this->indicatorAMPM.setBlinkOn();

}
Clock_OLED::displayTime()
{
     int hoursChanged;
     // //display the current setting for hours.  Only redraw if not already //displayed.
     hoursChanged = this->displayHours(this->hr);
      //this->displayMinutes(this->mn,hoursChanged);
      this->displayMinutes(this->mn,0);
      // Draw AM or PM
      this->blinkAMPM = 0;
      // Is it midnight? Then erase the current date and //display the new one.
      if (this->amOrPm == 0)
      {
        this->erasePM();
        this->displayAM();
        this->setAMPM = 1;
        this->amOrPm = 1;
      }
      else
      {
        this->eraseAM();
        this->displayPM();
        this->setAMPM = 0;
        this->amOrPm = 0;
      }
      //display.//display();
      // Put flashing color on
      if (this->colonStatus == 0)
      {
        //display.fillCircle(48,12,1,WHITE);
        //display.//display();
        //display.fillCircle(48,30,1,WHITE);
        //display.//display();
        this->colonStatus = 1;      
      }
      else
      {
        //display.fillCircle(48,12,1,BLACK);
        //display.//display();
        //display.fillCircle(48,30,1,BLACK);
        //display.//display();
        this->colonStatus = 0;
      }
      // //display Date
      
      this->eraseDateString();
      this->dateChanged = 0;
      this->setDateDay(this->mDay);
      this->setDateYear(this->mYear);
      this->setDateMonth(this->mMonth);
      this->displayDateString();
}
 void Clock_OLED::printTime()
{
    int row,col;
    uint16_t theChar[16];

    row = 400;
    col = 120;

    char buff[100];
    int BUFF_MAX = 100;

    struct ts t;
    DS3231_get(&t);
    delay(10);
    int hr,mn,yr,mth,day;
    int hrA,hrB,mnC,mnD;
    int yrA,yrB,yrC,yrD,mthA,mthB,dayA,dayB;

    this->segHr10.eraseDigit();
    this->segHr1.eraseDigit();
    this->segMin10.eraseDigit();
    this->segMin1.eraseDigit();

    this->segYr4.eraseDigit();
    this->segYr3.eraseDigit();
    this->segYr2.eraseDigit();
    this->segYr1.eraseDigit();
    this->segMth1.eraseDigit();
    this->segMth2.eraseDigit();
    this->segDay2.eraseDigit();
    this->segDay1.eraseDigit();


    hr = t.hour;
    mn = t.min;
    yr = t.year;
    mth = t.mon;
    day = t.mday;

    if (hr >= 10)
    {
      hrA = 1;
      hrB = hr - 10;
    }
    else
    {
      hrA = 0;
      hrB = hr;
    }
    mnC = (mn - fmod(mn, 10))/10;
    mnD = fmod(mn,10);
// 2Do:
/*
    yrA = (yr - fmod(yr, 1000))/1000;
    yrB = fmod(yr,1000);
    yrC = (
*/
  yrA = (yr - fmod(yr , 1000))/1000;
  yr = fmod(yr, 1000);
  yrB = (yr - fmod(yr, 100))/100;
  yr = fmod(yr, 100);
  yrC = (yr - fmod(yr, 10))/10;
  yr = fmod(yr,10);
  yrD = fmod(yr,1);

  mthA = (mth - fmod(mth, 10))/10;
  mthB = fmod(mth,10);

  dayA = (day - fmod(day, 10))/10;
  dayB = fmod(day,10);

    this->segYr4.drawDigit(yrA);
    this->segYr3.drawDigit(yrB);
    this->segYr2.drawDigit(yrC);
    this->segYr1.drawDigit(yrD);
    this->segMth2.drawDigit(mthA);
    this->segMth1.drawDigit(mthB);
    this->segDay2.drawDigit(dayA);
    this->segDay1.drawDigit(dayB);

    this->segHr10.drawDigit(hrA);
    this->segHr1.drawDigit(hrB);
    this->segMin10.drawDigit(mnC);
    this->segMin1.drawDigit(mnD);
    
    //printDec(hr,10 * 20,5 * 20);
    //printDec(mn,10 * 20,6 * 20);
//    printDec(yr,10 * 20,7 * 20);
 //   printDec(mth,10 * 20,8 * 20);
  //  printDec(dy,10 * 20,9 * 20);
    /*
    sprintf(buff, "%d.%02d.%02d %02d:%02d:%02d", t.year,t.mon, t.mday, t.hour, t.min, t.sec);
 
    char c;

    int i = 0;
    c = buff[i++];
    while (c != 0 && i < 20)
    {
      myGLCD.printChar(c,row,col,1);
      c = buff[i++];
      row -= 20;
    }
    */
    delay(1);  
}
void Clock_OLED::displayMinutes(double minutes,int hoursChanged)
{
     // Check to see if the tens place of minutes is already //displayed. 
     if (minutes < 10)
     {
        this->mn1 = 0;
        this->mn2 = minutes;
     }
     else
     {
        this->mn1 = (minutes - fmod(minutes,10))/10;
        this->mn2 = fmod(minutes,10);
     }
     this->segMin10.eraseDigit();
     this->segMin10.drawDigit(this->mn1);
     this->segMin1.eraseDigit();
     this->segMin1.drawDigit(this->mn2);
}
void Clock_OLED::eraseAM()
{
    this->indicatorAMPM.eraseIndicator();
}
void Clock_OLED::erasePM()
{
    this->indicatorAMPM.eraseIndicator();
}
void Clock_OLED::heartbeatCallback()
{
  this->segHr10.heartbeatCallback();
  this->segHr1.heartbeatCallback();
  this->segMin10.heartbeatCallback();
  this->segMin1.heartbeatCallback();

  this->indicatorAMPM.heartbeatCallback();
  
  this->segYr4.heartbeatCallback();
  this->segYr3.heartbeatCallback();
  this->segYr2.heartbeatCallback();
  this->segYr1.heartbeatCallback();
  
  this->segMth2.heartbeatCallback();
  this->segMth1.heartbeatCallback();
  
  this->segDay2.heartbeatCallback();
  this->segDay1.heartbeatCallback();

    if (intMode != 0)
    { 
      if (this->blinkDay == 1)
      {
        if (intHeartbeat)
        {
          this->eraseDateStringDay();
        }
        else
        {
          this->displayDateString();
        }
      }
      if (this->blinkMonth == 1)
      {
        if (intHeartbeat)
        {
          this->eraseDateStringMonth();
        }
        else
        {
          this->displayDateString();
        }
      }
      if (this->blinkYear == 1)
      {
        if (intHeartbeat)
        {
          this->eraseDateStringYear();
        }
        else
        {
          this->displayDateString();
        }
      }
      
    }
}
void Clock_OLED::blinkMonthOn()
{
  this->blinkMonth = 1;
}
void Clock_OLED::blinkMonthOff()
{
  this->blinkMonth = 0;
}
void Clock_OLED::blinkYearOn()
{
  this->blinkYear = 1;
}
void Clock_OLED::blinkYearOff()
{
  this->blinkYear = 0;
}
void Clock_OLED::blinkDayOn()
{
  this->blinkDay = 1;
}
void Clock_OLED::blinkDayOff()
{
  this->blinkDay = 0;
}
void Clock_OLED::displayAM()
{
    this->indicatorAMPM.drawIndicator(0);
}
void Clock_OLED::displayPM()
{
    this->indicatorAMPM.drawIndicator(1);
}
void Clock_OLED::blinkAMPMOn()
{
  this->blinkAMPM = 1;
}
void Clock_OLED::blinkAMPMOff()
{
  this->blinkAMPM = 0;
}
void Clock_OLED::eraseDateString()
{
    this->segYr4.eraseDigit();
    this->segYr3.eraseDigit();
    this->segYr2.eraseDigit();
    this->segYr1.eraseDigit();
    this->segMth1.eraseDigit();
    this->segMth2.eraseDigit();
    this->segDay2.eraseDigit();
    this->segDay1.eraseDigit(); 
}
void Clock_OLED::eraseDateStringMonth()
{
      //display.fillRect(1,44,20,16,BLACK);
      //display.//display();  
}
void Clock_OLED::eraseDateStringDay()
{
      //display.fillRect(25,44,30,16,BLACK);
      //display.//display();  
}
void Clock_OLED::eraseDateStringYear()
{
      //display.fillRect(60,44,60,16,BLACK);
      //display.//display();  
}
void Clock_OLED::toggleAMPM()
{
    
    if (this->amOrPm == 1)
    {
      this->setAMPM = 0;
      this->amOrPm = 0;
    }
    else
    {
      this->setAMPM = 1;
      this->amOrPm = 1;
    }
    this->indicatorAMPM.eraseIndicator();
    this->indicatorAMPM.drawIndicator(this->amOrPm);
}
void Clock_OLED::toggleAMPMAlarm()
{
    if (this->alarmAMPM == 1)
    {
      this->alarmAMPM = 0;
      this->erasePM();
      this->blinkAMPMOff();
      this->displayAM();
    }
    else
    {
      this->alarmAMPM = 1;
      this->eraseAM();
      this->blinkAMPMOff();
      this->displayPM();
    }
}
void Clock_OLED::setTimeOfDay()
{
  // Freeze setAMPM variable and move on to month
  this->indicatorAMPM.setBlinkOff();
  //this->blinkAMPMOff();
  //this->displayTime();
  // AM or PM should already be set.
  this->blinkMonthOn();
  this->intMode=4;  
  this->setTime();
}
void Clock_OLED::setTimeOfAlarm()
{
  this->setAlarm();
 // this->displayTime();
  this->displayDateString();
  this->intMode=0;  
}
void Clock_OLED::incrementMonth()
{
  int month;

  month = this->setMonth;

  month += 1;
  if (month == 13)
  {
    month = 1;
  }
  this->setMonth = month;
  this->dtMonth = month;
}
void Clock_OLED::setMonthValue()
{
  this->blinkMonthOff();
  this->blinkDayOn();
  this->eraseDateString();
  this->displayDateString();
  this->intMode = 5;
}
void Clock_OLED::incrementDay()
{
  int day;

  day = this->setDay;

  day += 1;
  if (day == 32)
  {
    day = 1;
  }
  this->setDay = day;
  this->dtDay = day;
  
}
void Clock_OLED::setDayValue()
{
  this->blinkDayOff();
  this->blinkYearOn();   
  this->eraseDateString();
  this->displayDateString();
  this->intMode = 6;
}
void Clock_OLED::incrementYear()
{
  int year;

  year = this->setYear;

  year += 1;

  if (year > 2030)
  {
    year = 2019;
  }


  this->setYear = year;
  this->dtYear = year;
}
void Clock_OLED::setYearValue()
{
  this->blinkYearOff();
  this->eraseDateString();
  this->setTime();
  this->setStartVariables();
  this->displayTime();
  this->intMode = 0;
}
void Clock_OLED::displayDateString()
{
        // //display Date
      double month,day,year;
      day = this->dtDay;
      month = this->dtMonth;
      year = this->dtYear;

          int row,col;
    uint16_t theChar[16];

    row = 400;
    col = 120;

    char buff[100];
    int BUFF_MAX = 100;

    struct ts t;
    DS3231_get(&t);
    delay(10);
    int hr,mn,yr,mth;
    int hrA,hrB,mnC,mnD;
    int yrA,yrB,yrC,yrD,mthA,mthB,dayA,dayB;

    this->segYr4.eraseDigit();
    this->segYr3.eraseDigit();
    this->segYr2.eraseDigit();
    this->segYr1.eraseDigit();
    this->segMth1.eraseDigit();
    this->segMth2.eraseDigit();
    this->segDay2.eraseDigit();
    this->segDay1.eraseDigit();


    yr = year;
    mth = month;
    day = day;

  yrA = (yr - fmod(yr , 1000))/1000;
  yr = fmod(yr, 1000);
  yrB = (yr - fmod(yr, 100))/100;
  yr = fmod(yr, 100);
  yrC = (yr - fmod(yr, 10))/10;
  yr = fmod(yr,10);
  yrD = yr;

  mthA = (mth - fmod(mth, 10))/10;
  mthB = fmod(mth,10);

  dayA = (day - fmod(day, 10))/10;
  dayB = fmod(day,10);

    this->segYr4.drawDigit(yrA);
    this->segYr3.drawDigit(yrB);
    this->segYr2.drawDigit(yrC);
    this->segYr1.drawDigit(yrD);
    this->segMth2.drawDigit(mthA);
    this->segMth1.drawDigit(mthB);
    this->segDay2.drawDigit(dayA);
    this->segDay1.drawDigit(dayB);
    
    delay(1);  
}
void Clock_OLED::setDateYear(double year)
{
   this->dtYear = year;
}
void Clock_OLED::setDateMonth(double month)
{
  this->dtMonth = month;
}
void Clock_OLED::setDateDay(double day)
{
  this->dtDay = day;
}
