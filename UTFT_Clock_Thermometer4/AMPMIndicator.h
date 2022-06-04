/***********************************************************************
 * SevenSegment.h
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
 * indicators use these Segments to form the number.f
 * 
 */
#include <avr/pgmspace.h>

#include <UTFT.h>
/*

AMPM.h

*/
#define indicator_AM 0
#define indicator_PM 1
// Define the pen colors
#define C_BLACK 0
#define C_WHITE 1

extern UTFT myGLCD;
//extern Adafruit_SSD1306 display; // The Adafruit display should already be declared in the sketch
extern unsigned int intHeartbeat;

class AMPM
{
   private:
    double left_x; // The Left position of the numeral
    double top_y;  // The Top position of the numeral
    double indicator_height; // The Height of the numeral
    double indicator_width; // The Width of the numeral
    double line_width; // The line width of each Segment
    double right_x;  // The Right position of the numeral
    double bottom_y; // The Bottom position of the numeral
    double half_y; // Halfway up the numeral
    double half_x; // Halfway of the width!
    int color; // The Color, black or white, of the pen that we are using to draw.
    int blinkStatus;
    int indicatorValue;
    int blank;
   public:
    AMPM(); // The default constructor
    AMPM(const AMPM &indicator); // The copy constructor
    AMPM(double left_x,double top_y,double indicator_width,double indicator_height);  // The Constructor
    void drawA(); // Draws an A in the Upper Left
    void drawP(); // Draws a P in the Lower left
    void drawM(int toporbottom); // Draws a M
    void drawAM();
    void drawPM();
	  void drawIndicator(int indicator); // Draw a indicator of the numeral
    void eraseIndicator(); // Erase the indicator (switches color to black and writes an '8'
    void setWhiteColor(); // Set the color of the pen to White
    void setBlackColor(); // Set the color of the pen to Black.
    void setBlinkOn();
    void setBlinkOff();
    void toggleIndicator();
    void returnIndicator();
    void heartbeatCallback();
};
