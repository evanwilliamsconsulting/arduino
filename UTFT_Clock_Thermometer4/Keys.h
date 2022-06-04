#include <avr/pgmspace.h>
#include <UTFT.h>

extern UTFT myGLCD;

class Keys
{
   private:
    double left_x;
    double top_y;
    double right_x;
    double bottom_y;
    double keys_width;
    double keys_height;

   public:
    Keys(double left_x,double top_y,double keys_height,double keys_width);
    void drawKeyboard();
    void drawRow(char* rowkey,int rowlen,int x_offset,int y_offset);
    void putKey(char keycode);
};
