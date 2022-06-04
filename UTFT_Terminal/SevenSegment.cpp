#include "SevenSegment.h"

#include <math.h>
#include <UTFT.h> 

SevenSegment::SevenSegment(double left_x,double top_y,double led_height,double led_width)
{
  double right_x,bottom_y,line_width,line_height;
  this->left_x = left_x;
  this->top_y = top_y;
  this->led_height = led_height;
  this->led_width = led_width;
  // Compute the remainders
  right_x = left_x  + led_width;
  this->right_x = right_x;
  bottom_y = top_y + led_height;
  this->bottom_y = bottom_y;
  line_width = 0.10 * (right_x - left_x);
  line_height = line_width;
  this->line_width = line_width;
  this->line_height = line_height;
  this->half_y = top_y + (bottom_y - top_y) / 2;
}
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
  line = 20;
  myGLCD.setColor(255,255,255);
  switch (segment)
  {
    case SEGMENT_A:
      x1 = left;
      x2 = left + line;
      y1 = top;
      y2 = half;
      break;
    case SEGMENT_C:
      x1 = right - line;
      x2 = right;
      y1 = top;
      y2 = half;
    case SEGMENT_B:
      x1 = left;
      x2 = right;
      y1 = top;
      y2 = top + line;
      break;
    case SEGMENT_G:
      x1 = left;
      x2 = right;
      y1 = half;
      y2 = half + line;
      break;
    case SEGMENT_E:
      x1 = left;
      x2 = right;
      y1 = bottom - line;
      y2 = bottom;
      break;
    case SEGMENT_F:
      x1 = left;
      x2 = left + line;
      y1 = top;
      y2 = half;
      break;
    case SEGMENT_D:
      x2 = right;
      x1 = right - line;
      y1 = top;
      y2 = half;
      break;
    case SEGMENT_DP:
      break;
  }
   myGLCD.fillRect(x1,y1,x2,y1);
}
