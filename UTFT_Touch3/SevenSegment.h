#include <avr/pgmspace.h>
#include <UTFT.h>
/*

SevenSegment.h

*/
#define SEGMENT_A 0
#define SEGMENT_B 1
#define SEGMENT_C 2
#define SEGMENT_D 3
#define SEGMENT_E 4
#define SEGMENT_F 5
#define SEGMENT_G 6
#define SEGMENT_DP 7

extern UTFT myGLCD;

class SevenSegment
{
   private:
    double left_x;
    double top_y;
    double led_height;
    double led_width;
    double line_width;
    double line_height;
    double right_x;
    double bottom_y;
    double half_y;
   public:
    SevenSegment(double left_x,double top_y,double led_height,double led_width);
    void drawSegment(int segment_no);
	  void drawDigit(int hex_digit_value);
    void eraseDigit();
};
