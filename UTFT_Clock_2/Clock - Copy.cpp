#include "Clock.h"

#include <math.h>
#include <UTFT.h> 

Clock::Clock(double offset_x,double offset_y,double side_len)
{
  this->center_x = offset_x;
  this->center_y = offset_y;
  this->side_len = side_len;
  this->hours = 0;
  this->minutes = 0;
  this->seconds = 0;
}
void Clock::drawSecondHand(double seconds)
{
  this->seconds = seconds;
  double clock_deg = seconds * 5;
  myGLCD.setColor(255,255,255);
  this->drawHand(0,clock_deg);
}
void Clock::drawMinutesHand(double minutes)
{
  this->minutes = minutes;
  double clock_deg = minutes * 5;
  myGLCD.setColor(255,255,255);
  this->drawHand(1,clock_deg);
}
void Clock::drawHoursHand(double hours)
{
  this->hours = hours;
  double clock_deg = hours * 30;
  myGLCD.setColor(255,255,255);
  this->drawHand(2,clock_deg);
}
void Clock::eraseHands()
{
  myGLCD.setColor(0,0,0);
  double hours,minutes,seconds,degrees_hours,degrees_minutes,degrees_seconds;
  hours = this->hours;
  degrees_hours = hours * 30;
  minutes = this->minutes;
  degrees_minutes = minutes * 5;
  seconds = this->seconds;
  degrees_seconds = seconds * 5;
  this->drawHand(0,degrees_seconds);
  this->drawHand(1,degrees_minutes);
  this->drawHand(2,degrees_hours);
}
void Clock::drawHand(int hand, double clock_deg)
{
  float pi = 3.1415;
  int xsec,ysec;
  float increment = pi / 180;
  float rad = clock_deg * increment;
  float rsec = 90;
  int r,r2,r3,r4;
  double x3,y3,x4,y4,x5,y5;
  double offset_x,offset_y,side_len;
  double x1,x2,y1,y2;
  offset_x = this->center_x;
  offset_y = this->center_y;
  side_len = this->side_len;
  r3 = side_len / 2;
  r4 = r3 - 20;
  r2 = r4 - 30;
  r = r2 - 30;
  
  if (hand == 0)
  {
	  r2 = r4 - 20;
  }
  else if (hand == 1)
  {
	  r2 = r4 - 25;
  }
  else
  {
	  r2 = r4 - 30;
  }
  xsec = offset_x + r2 * sin(rad);
  ysec = offset_y + r2 * cos(rad);
  if (offset_x > xsec)
  {
    if (offset_y > ysec)
    {
        x1 = offset_x;
        x2 = xsec;
        y1 = offset_y;
        y2 = ysec;
    }
    else
    {
       x1 = offset_x;
       x2 = xsec;
       y1 = offset_y;
       y2 = ysec;
    }
  }
  else
  {
    if (offset_y > ysec)
    {
        x2 = xsec;
        x1 = offset_x;
        y2 = ysec;
        y1 = offset_y;
    }
    else
    {
      x1 = xsec;
      x2 = offset_x;
      y1 = ysec;
      y2 = offset_y;
    }
  }
  myGLCD.drawLine(x1,y1,x2,y2);
}
void Clock::paintClock()
{
  int x1,y1,y2;
  int r,r2,r3,r4;
  int oclock = 6;
  byte c1,c2;
  float rad;
  float pi = 3.1415;
  double x3,y3,x4,y4,x5,y5;
  double offset_x,offset_y,side_len;

  offset_x = this->center_x;
  offset_y = this->center_y;
  side_len = this->side_len;
  r3 = side_len / 2;
  r4 = r3 - 20;
  r2 = r4 - 30;
  r = r2 - 30;
  float increment = pi / 6;
  
  myGLCD.setColor(255,255,255);
  rad = 0;
  while (rad < 2 * pi)
  {
      x3 = offset_x + r * sin(rad);
      y3 = offset_y + r * cos(rad);
      x4 = offset_x + r2 * sin(rad);
      y4 = offset_y + r2 * cos(rad);
      x5 = offset_x + r4 * sin(rad);
      y5 = offset_y + r4 * cos(rad);
      rad = rad + increment;
      //myGLCD.drawPixel(x3,y3);
      //myGLCD.drawPixel(x4,y4);
      //myGLCD.drawLine(x3,y3,x4,y4);
     // myGLCD.drawLine(x4,y4,x3,y3);
     if (oclock < 10)
     {
      c1 = '0' + oclock + 2;
      myGLCD.printChar(c1,x5,y5,2);
     }
     else
     {
      c1 = '0' + oclock - 10 + 2;
      c2 = '1'+2;
      myGLCD.printChar(c2,x5,y5,2);
      myGLCD.printChar(c1,x5-10,y5,2);
     }
     if (oclock == 12)
     {
         oclock = 1;
     }
     else
     {
         oclock += 1;
     }
  }
  increment = pi / 160;
  rad = 0;
  while (rad < 2 * pi)
  {
      x3 = offset_x + r3 * sin(rad);
      y3 = offset_y + r3 * cos(rad);
      rad = rad + increment;
      myGLCD.drawPixel(x3,y3);    
  }
}
