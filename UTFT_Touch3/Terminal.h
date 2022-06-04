#include <avr/pgmspace.h>
#include <UTFT.h>
/*

Terminal.h

*/

extern UTFT myGLCD;

class Terminal
{
   private:
    double left_x;
    double top_y;
    double right_x;
    double bottom_y;
    double width_x;
    int margin_x;
    int margin_y;
    int char_width;
    int char_height;
    int rows;
    int columns;
    int x,y;
   public:
    Terminal(double left_x,double top_y,double width_x,double height_y);
    void drawTerminalWindow();
    void putText(const char* textLine,int lenvar);
    void putChar(char d);
    void clearTerminalWindow();
    void resetTerminal();
};
