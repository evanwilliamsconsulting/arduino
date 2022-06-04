#include "Terminal.h"
#include <math.h>
#include <UTFT.h> 

Terminal::Terminal(double left_x,double top_y,double width_x,double height_y)
{
  double right_x,bottom_y;
  this->left_x = left_x;
  this->top_y = top_y;
  right_x = left_x + width_x;
  this->width_x = width_x;
  this->right_x = right_x;
  bottom_y = top_y + height_y;
  this->bottom_y = bottom_y;
  this->margin_x = 5;
  this->margin_y = 5;
  this->char_width = 10;
  this->char_height = 10;

  this->columns = width_x / char_width;
  this->rows = height_y / char_height;
  this->y = top_y + margin_y;
  this->x = right_x - char_width;
}
void Terminal::drawTerminalWindow()
{
  double left,top,bottom,right,line;

  left = this->left_x;
  top = this->top_y;
  right = this->right_x;
  bottom = this->bottom_y;

  this->y = this->top_y + this->margin_y;
  this->x = this->right_x - this->char_width;  

  line = 2;
  
  myGLCD.setColor(255,255,255);
  myGLCD.drawRect(left,top,right,bottom);
}
void Terminal::putChar(char d)
{
  int top,left,right,bottom,width_x;
  int margin_x,margin_y,char_width,char_height;
  int x,y;

    top = this->top_y;
    left = this->left_x;
    right = this->right_x;
    bottom = this->bottom_y;
    width_x = this->width_x;
    margin_x = this->margin_x;
    margin_y = this->margin_y;
    char_width = this->char_width;
    char_height = this->char_height;

    x = this->x;
    y = this->y;


  myGLCD.setColor(255,255,255);
  myGLCD.printChar(d,x,y,1);
}
void Terminal::putText(const char* textLine, int lenvar)
{
    int countChars;
    int countColumns;
    int countRows;
    int top,left,right,bottom;
    int margin_x,margin_y,char_width,char_height;
    int x,y;

    top = this->top_y;
    left = this->left_x;
    right = this->right_x;
    bottom = this->bottom_y;
    margin_x = this->margin_x;
    margin_y = this->margin_y;
    char_width = this->char_width;
    char_height = this->char_height;

    x = this->x;
    y = this->y;

    int i = 0;
    char *d = textLine;
    char c;
    c = *d++;
    int somevar = lenvar;
    while (somevar-- > 0)
    {
      myGLCD.setColor(255,255,255);
      myGLCD.printChar(c,x,y,1);
      x -= 10;
      if (x <= 10)
      {
        x = 460;
        y += 10;
        if (y > 150)
        {
          this->clearTerminalWindow();
          y = 15;
          x = 460;  
        }
      }
      c = *d++;
    }
    this->x = x;
    this->y = y;
}
void Terminal::resetTerminal()
{
  this->y = this->top_y + this->margin_y;
  this->x = this->right_x - this->char_width;  
}
void Terminal::clearTerminalWindow()
{
    double left,top,right,bottom,margin_x,margin_y;

    left = this->left_x;
    top = this->top_y;
    right = this->right_x;
    bottom = this->bottom_y;
    margin_x = this->margin_x - 2;
    margin_y = this->margin_y - 2;

    myGLCD.setColor(0,0,0);
    myGLCD.fillRect(left+margin_x,top+margin_y,right-margin_x,bottom-margin_y);
}

Terminal theTerminal = Terminal(10,10,460,150);
