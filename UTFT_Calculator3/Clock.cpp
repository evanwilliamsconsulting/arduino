//#include "Fonts.h"
#include "Clock.h"

#include <math.h>
#include <UTFT.h> 

Clock::Clock(UTFT myGLCD,int offset_x,int offset_y,int side_len)
{
  this->myGLCD = myGLCD;
  this->offset_x = offset_x;
  this->offset_y = offset_y;
  this->side_len = side_len;
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
  double offset_x,offset_y;
  offset_x = this->offset_x;
  offset_y = this->offset_y;
  side_len = this->side_len;
  r3 = side_len / 2;
  r4 = r3 - 10;
  r2 = r4 - 20;
  r = r2 -10;
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
      myGLCD.drawPixel(x3,y3);
      myGLCD.drawPixel(x4,y4);
      myGLCD.drawLine(x3,y3,x4,y4);
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
