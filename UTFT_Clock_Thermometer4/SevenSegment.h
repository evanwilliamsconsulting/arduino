/***********************************************************************
 * SevenSegment.h
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
#include <avr/pgmspace.h>

#include <UTFT.h>
/*

SevenSegment.h

*/
// Define the Segments
#define SEGMENT_A 1
#define SEGMENT_B 2
#define SEGMENT_C 3
#define SEGMENT_D 4
#define SEGMENT_E 5
#define SEGMENT_F 6
#define SEGMENT_G 7
#define SEGMENT_DP 8

// Define the Digits
#define DIGIT_0 0
#define DIGIT_1 1
#define DIGIT_2 2
#define DIGIT_3 3
#define DIGIT_4 4
#define DIGIT_5 5
#define DIGIT_6 6
#define DIGIT_7 7
#define DIGIT_8 8
#define DIGIT_9 9

// Define the pen colors
#define C_BLACK 0
#define C_WHITE 1

extern UTFT myGLCD;
//extern Adafruit_SSD1306 display; // The Adafruit display should already be declared in the sketch
extern unsigned int intHeartbeat;

class SevenSegment
{
   private:
    double left_x; // The Left position of the numeral
    double top_y;  // The Top position of the numeral
    double digit_height; // The Height of the numeral
    double digit_width; // The Width of the numeral
    double line_width; // The line width of each Segment
    double right_x;  // The Right position of the numeral
    double bottom_y; // The Bottom position of the numeral
    double half_y; // Halfway up the numeral
    int color; // The Color, black or white, of the pen that we are using to draw.
    int blinkStatus;
    int digitValue;
    int blank;
   public:
    SevenSegment(); // The default constructor
    SevenSegment(const SevenSegment &digit); // The copy constructor
    SevenSegment(double left_x,double top_y,double digit_width,double digit_height);  // The Constructor
    void drawSegment(int Segment_no); // Draw a Segment in the numeral
	  void drawDigit(int digit); // Draw a digit of the numeral
    void eraseDigit(); // Erase the digit (switches color to black and writes an '8'
    void setWhiteColor(); // Set the color of the pen to White
    void setBlackColor(); // Set the color of the pen to Black.
    void setBlinkOn();
    void setBlinkOff();
    void blankZero(); // Ensures that the digit is blank if the value is '0'
    void underscoreOn();
    void underscoreOff();
    void incrementNumeral();
    void returnNumericValue();
    void heartbeatCallback();
};
