/***********************************************************************
 * AMPM.cpp
 * 
 * Seven Segment Display Class for Arduion (for Oindicator)
 * by Evan J. Williams
 * July 21, 2020
 * GPL - General Purpose License
 * 
 * This is a class to draw Seven Segment Style numerals on the Oindicator display.
 * 
 * Segments are A through G
 * 
 * indicators use these Segments to form the number.
 * 
 */
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include "AMPMIndicator.h"
#include <math.h>
//#include "Keys.h"
//#include "Fonts.h"
#include <math.h>
#include <UTFT.h> 

/*
 * AMPM Default Constructor
 * 
 */
 AMPM::AMPM()
 {
 
 }
 /*
  * AMPM Copy Constructor
  */
AMPM::AMPM(const AMPM &indicator)
{
  left_x = indicator.left_x;
  top_y = indicator.top_y;
  indicator_height = indicator.indicator_height;
  indicator_width = indicator.indicator_width;
  line_width = indicator.line_width;
  right_x = indicator.right_x;
  bottom_y = indicator.bottom_y;
  half_y = indicator.half_y;
  half_x = indicator.half_x;
  color = indicator.color;
  blinkStatus = indicator.blinkStatus;
  blank = indicator.blank;
}
/*
 * AMPM indicator Constructor
 *    left_x: the leftmost position of the indicator
 *    top_Y: the top position of the indicator
 *    indicator_width: the width of the indicator
 *    indicator_height: the height of the indicator
 */
AMPM::AMPM(double left_x,double top_y,double indicator_width,double indicator_height)
{
  double right_x,bottom_y,line_width,line_height;
  this->left_x = left_x;
  this->top_y = top_y;
  this->indicator_height = indicator_height;
  this->indicator_width = indicator_width;
  // Compute the remainders
  right_x = left_x  + indicator_width;
  this->right_x = right_x;
  bottom_y = top_y + indicator_height;
  this->bottom_y = bottom_y;
  line_width = 2;
  this->line_width = line_width;
  this->half_y = top_y + (bottom_y - top_y) / 2;
  this->half_x = indicator_width / 2;
  // Set the initial color of the indicator to white.
  this->color = C_WHITE;
  this->blinkStatus = 0;
  this->blank = 0;
}
void AMPM::drawA()
{
  myGLCD.setColor(0,0,0);
  int top_y,left_x,width,height;

  top_y = this->top_y;
  left_x = this->left_x;
  width = this->indicator_width - 4 * this->line_width;
  height = this->indicator_height - 4 * this->line_width;
  
  myGLCD.fillRect(left_x,top_y,left_x+20-1,top_y+line_width);
  myGLCD.fillRect(left_x,top_y+20,left_x+20-1,top_y+20+line_width);
  myGLCD.fillRect(left_x,top_y,left_x+line_width,top_y+40-2);
  myGLCD.fillRect(left_x+20-1,top_y,left_x+20-1+line_width,top_y+40);

}
void AMPM::drawP()
{
  myGLCD.setColor(0,0,0);
  int top_y,left_x,width,height,line_width;

  line_width = this->line_width;

  top_y = this->half_y + 2 * this->line_width;
  left_x = this->left_x;
  width = this->indicator_width - 4 * this->line_width;
  height = this->indicator_height - 4 * this->line_width;

  myGLCD.fillRect(left_x,top_y,left_x+20,top_y+line_width);
  myGLCD.fillRect(left_x,top_y+20,left_x+20,top_y+20+line_width);
  myGLCD.fillRect(left_x,top_y,left_x+line_width,top_y+20);
  myGLCD.fillRect(left_x+20,top_y,left_x+20+line_width,top_y+40-2);
}
void AMPM::drawM(int toporbottom)
{
  myGLCD.setColor(0,0,0);
  int top_y,left_x,width,height;

  if (toporbottom == 0)
  {
      top_y = this->top_y;
  }
  else
  {
      top_y = this->half_y + 2 * this->line_width;
  }
  left_x = this->half_x + 2 *this->line_width - 10;
  width = this->indicator_width - 4 * this->line_width;
  height = this->indicator_height - 4 * this->line_width;

  myGLCD.fillRect(left_x,top_y,left_x+20,top_y+line_width);
  myGLCD.fillRect(left_x,top_y,left_x+line_width,top_y+40);
  myGLCD.fillRect(left_x+20-1,top_y,left_x+20-1+line_width,top_y+40);
  myGLCD.fillRect(left_x+10-1,top_y,left_x+10-1+line_width,top_y+20);

}
/*
 * AMPM::setWhiteColor()
 *  -- Sets the Pen Color to White
 */
void AMPM::setWhiteColor()
{
  this->color = C_WHITE;
}
/*
 * Function to blank '0' numeral for tens place of hours
 */
/*
 * AMPM::setWhiteColor()
 *  -- Sets the Pen Color to Black
 */
void AMPM::setBlackColor()
{
  this->color = C_BLACK;
}
/*
 * AMPM::drawindicator()
 *  -- Draws the numeric indicator passed in as:
 *  indicator - the indicator to draw (uses indicator_ constants)
 */
void AMPM::drawIndicator(int indicator)
{        
  this->indicatorValue = indicator;
  switch (indicator)
  {
    case indicator_AM:
      this->drawA();
      this->drawM(0);
      break;
    case indicator_PM:
      this->drawP();
      this->drawM(1);
      break;
    default:
      break;
  }
}
/*
 * AMPM::eraseindicator()
 *  -- Erases the indicator by drawing a '8' using the black pen.
 */
void AMPM::drawAM()
{
      this->drawA();
      this->drawM(0);  
}
void AMPM::drawPM()
{
      this->drawP();
      this->drawM(1);  
}
void AMPM::eraseIndicator()
{
     int top,left,bottom,right;

     top = this->top_y;
     left = this->left_x;

     myGLCD.setColor(255,255,255);
     myGLCD.fillRect(left-50,top,left+40,top+100);
     myGLCD.setColor(0,0,0);
}
void AMPM::setBlinkOn()
{
  this->blinkStatus = 1; 
}
void AMPM::setBlinkOff()
{
  this->blinkStatus = 0;
}
void AMPM::returnIndicator()
{
  return this->indicatorValue;
}
void AMPM::toggleIndicator()
{
  if (this->indicatorValue == 1)
  {
    this->indicatorValue = 0;
  }
  else
  {
    this->indicatorValue = 1;
  }
  this->eraseIndicator();
  this->drawIndicator(this->indicatorValue);
}
void AMPM::heartbeatCallback()
{
  if (this->blinkStatus == 1)
  {
    if (intHeartbeat != 0) // OFF
    {
        this->eraseIndicator();
    }
    else
    {
      this->eraseIndicator();
      this->drawIndicator(this->indicatorValue);
    }
  }
}
