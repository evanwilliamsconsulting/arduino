/***********************************************************************
 * SevenSegment.cpp
 * 
 * Seven Segment Display Class for Arduion (for Odigit)
 * by Evan J. Williams
 * July 21, 2020
 * GPL - General Purpose License
 * 
 * This is a class to draw Seven Segment Style numerals on the Odigit display.
 * 
 * Segments are A through G
 * 
 * Digits use these Segments to form the number.
 * 
 */
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include "SevenSegment.h"
#include <math.h>
//#include "Keys.h"
//#include "Fonts.h"
#include <math.h>
#include <UTFT.h> 

/*
 * SevenSegment Default Constructor
 * 
 */
 SevenSegment::SevenSegment()
 {
 
 }
 /*
  * SevenSegment Copy Constructor
  */
SevenSegment::SevenSegment(const SevenSegment &digit)
{
  left_x = digit.left_x;
  top_y = digit.top_y;
  digit_height = digit.digit_height;
  digit_width = digit.digit_width;
  line_width = digit.line_width;
  right_x = digit.right_x;
  bottom_y = digit.bottom_y;
  half_y = digit.half_y;
  color = digit.color;
  blinkStatus = digit.blinkStatus;
  blank = digit.blank;
}
/*
 * SevenSegment Digit Constructor
 *    left_x: the leftmost position of the digit
 *    top_Y: the top position of the digit
 *    digit_width: the width of the digit
 *    digit_height: the height of the digit
 */
SevenSegment::SevenSegment(double left_x,double top_y,double digit_width,double digit_height)
{
  double right_x,bottom_y,line_width,line_height;
  this->left_x = left_x;
  this->top_y = top_y;
  this->digit_height = digit_height;
  this->digit_width = digit_width;
  // Compute the remainders
  right_x = left_x  + digit_width;
  this->right_x = right_x;
  bottom_y = top_y + digit_height;
  this->bottom_y = bottom_y;
  line_width = 2;
  this->line_width = line_width;
  this->half_y = top_y + (bottom_y - top_y) / 2;
  // Set the initial color of the Digit to white.
  this->color = C_WHITE;
  this->blinkStatus = 0;
  this->blank = 0;
}
/*
 * SevenSegment::setWhiteColor()
 *  -- Sets the Pen Color to White
 */
void SevenSegment::setWhiteColor()
{
  this->color = C_WHITE;
}
/*
 * Function to blank '0' numeral for tens place of hours
 */
 void SevenSegment::blankZero()
 {
    this->blank = 1;
 }
/*
 * SevenSegment::setWhiteColor()
 *  -- Sets the Pen Color to Black
 */
void SevenSegment::setBlackColor()
{
  this->color = C_BLACK;
}
/*
 * SevenSegment::drawDigit()
 *  -- Draws the numeric digit passed in as:
 *  digit - the digit to draw (uses DIGIT_ constants)
 */
void SevenSegment::drawDigit(int digit)
{
  this->digitValue = digit;
  if (this->digitValue == 0 && this->blank == 1)
  {
    this->eraseDigit();
  }
  else
  {
    switch (digit)
    {
      case DIGIT_1:
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        break;
      case DIGIT_2:
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_G);
        this->drawSegment(SEGMENT_E);
        this->drawSegment(SEGMENT_F);
        break;
      case DIGIT_3:
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_G);
        this->drawSegment(SEGMENT_E);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        break;
      case DIGIT_4:
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_G);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        break;
      case DIGIT_5:
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_G);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_E);
        break;
      case DIGIT_6:
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_G);
        this->drawSegment(SEGMENT_F);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_E);
        break;
      case DIGIT_7:
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        break;
      case DIGIT_8:
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_E);
        this->drawSegment(SEGMENT_F);
        this->drawSegment(SEGMENT_G);
        break;
      case DIGIT_9:
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_G);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_C);
        break;
      case DIGIT_0:
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_E);
        this->drawSegment(SEGMENT_F);
        break;
      default:
        this->drawSegment(SEGMENT_A);
        this->drawSegment(SEGMENT_B);
        this->drawSegment(SEGMENT_C);
        this->drawSegment(SEGMENT_D);
        this->drawSegment(SEGMENT_E);
        this->drawSegment(SEGMENT_F);
        break;
    }
  }
}
/*
 * SevenSegment::eraseDigit()
 *  -- Erases the digit by drawing a '8' using the black pen.
 */

void SevenSegment::eraseDigit()
{
     int wid,heig;
     wid = 2 + this->right_x - this->left_x;
     heig = 2 + this->bottom_y - this->top_y;

     if (this->color == C_WHITE)
     {
         myGLCD.setColor(0,0,0);
     }
     else
     {
         myGLCD.setColor(255,255,255);
     }
     myGLCD.fillRect(this->left_x,this->top_y,this->left_x+wid,this->top_y+heig);
}
/*
 * SevenSegment::drawSegment()
 *  -- Draws a segment in the seven-segment display. Line width is set to '2'
 *  segment - the segment to draw using the SEGMENT_ constants
 */
void SevenSegment::drawSegment(int segment)
{
  int x1,y1,x2,y2;
  double left,top,bottom,right,half,line;
   double half_y;
  left = this->left_x;
  top = this->top_y;
  right = this->right_x;
  bottom = this->bottom_y;
  half = this->half_y;
  line = 2;
  switch (segment)
  {
    case SEGMENT_A:
      x1 = right;
      x2 = right + 2;
      y1 = top;
      y2 = half;
      break;
    case SEGMENT_C:
      x1 = left;
      x2 = left + 2;
      y1 = top;
      y2 = half;
      break;
    case SEGMENT_B:
      x1 = left;
      x2 = right;
      y1 = top;
      y2 = top + 2;
      break;
    case SEGMENT_G:
      x1 = left;
      x2 = right;
      y1 = half;
      y2 = half + 2;
      break;
    case SEGMENT_E:
      x1 = left;
      x2 = right;
      y1 = bottom;
      y2 = bottom + 2;
      break;
    case SEGMENT_F:
      x1 = right;
      x2 = right + 2;
      y1 = half;
      y2 = bottom;
      break;
    case SEGMENT_D:
      x1 = left;
      x2 = left + 2;
      y1 = half;
      y2 = bottom;
      break;
    case SEGMENT_DP:
      break;
  }
   int wid,heig;
   wid = x2 - x1;
   heig = y2 -y1;
   if (this->color == C_WHITE)
   {
      myGLCD.setColor(255,255,255);
      myGLCD.fillRect(x1,y1,x1 + wid,y1 + heig);
   }
   else
   {
      myGLCD.setColor(0,0,0);
      myGLCD.fillRect(x1,y1,x1 + wid,y1 + heig);    
   }
}
void SevenSegment::setBlinkOn()
{
  this->blinkStatus = 1; 
}
void SevenSegment::setBlinkOff()
{
  this->blinkStatus = 0;
}
void SevenSegment::heartbeatCallback()
{
  if (this->blinkStatus == 1)
  {
    if (intHeartbeat != 0) // OFF
    {
        this->eraseDigit();
    }
    else
    {
      this->drawDigit(this->digitValue);
    }
  }
}
