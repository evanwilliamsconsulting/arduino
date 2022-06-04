#include "Keys.h"
#include "Fonts.h"
#include <math.h>
#include <UTFT.h> 

Keys::Keys(double left_x,double top_y,double keys_height,double keys_width)
{
  double right_x,bottom_y,line_width,line_height;
  this->left_x = left_x;
  this->top_y = top_y;
  this->keys_height = keys_height;
  this->keys_width = keys_width;
  // Compute the remainders
  right_x = left_x  + keys_width;
  this->right_x = right_x;
  bottom_y = top_y + keys_height;
  this->bottom_y = bottom_y;
}
void Keys::drawKeyboard()
{
  int x1,y1,x2,y2;
  double left,top,bottom,right,half,line;

  left = this->left_x;
  top = this->top_y;
  right = this->right_x;
  bottom = this->bottom_y;

  line = 2;
  myGLCD.setColor(255,255,255);
  myGLCD.fillRect(left,top,right,bottom);
}
void Keys::drawRow(char *rowkey,int rowlen,int xpos,int ypos)
{
  double left_x,top_y,right_x,bottom_y,line_width,line_height;
  uint16_t *ptr;
  int b;
  char keycode;
  uint16_t theChar[16];

  left_x = this->left_x;
  top_y = this->top_y;

  xpos += left_x;
  ypos += top_y;

  for (int i=0;i<=rowlen;i++)
  {
     ptr = theChar;
     keycode = *rowkey++;
     if (keycode >= 'A')
     {
        b = keycode - 0x20 - 2;
     }
     else
     {
        b = keycode - 0x20;      
     }
     for (int k=0;k<16;k++)
     {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);         
     }
    myGLCD.printLarge(theChar,xpos,ypos,1);
    xpos -= 20;     
  }
}
  void Keys::putKey(char keycode)
  {
    double left_x,top_y,right_x,bottom_y,line_width,line_height;
    uint16_t *ptr;
    int b;
    int xpos,ypos;
    uint16_t theChar[16];

    int rowlen;
    char *rowarray;
    char row0[14] = {'`','0','1','2','3','4','5','6','7','8','9','0','-','='};
    char row1[13] = {'Q','W','E','R','T','Y','U','I','O','P','[',']','d'};
    char row2[11] = {'A','S','D','F','G','H','J','K','L',';','p'};
    char row3[10] = {'Z','X','C','V','B','N','M',',','.','/'};
    int done = 0;
    int offset = 0;
    while (offset <=3 && done == 0)
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
      while (offset2 < rowlen && done == 0)
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
              xpos = xpos - (20 * offset2);
              //myGLCD.setColor(255,0,0);
              //myGLCD.printChar(keycode,100,100,1);
              done = 1;
          }
          offset2 += 1;
      }
      offset += 1;
    }
  }
Keys theKeys = Keys(10,170,100,460);
 
