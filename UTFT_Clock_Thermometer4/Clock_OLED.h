/***********************************************************************
 * Clock_OLED.h
 * 
 * Clock Display Class for Arduion (for OLED)
 * by Evan J. Williams
 * July 24, 2020
 * GPL - General Purpose License
 * 
 * This is a class to draw and update a clock on the OLED display.
 * 
 */
#include <avr/pgmspace.h>
#include <UTFT.h>
#include "SevenSegment.h"
#include "AMPMIndicator.h"
#include "ds3231.h"
#include <math.h>


//extern Adafruit_SSD1306 display; // The Adafruit display should already be declared in the sketch
extern unsigned int intHeartbeat;
extern UTFT myGLCD;

class Clock_OLED
{
   private:
    double left_x; // The Left position of the clock
    double top_y;  // The Top position of the clock
    double right_x;  // The Right position of the clock
    double bottom_y; // The Bottom position of the clock
    double half_y; // Halfway up the clock
    double digit_width; // The Width of each digit
    double digit_height; // The Height of each digit


    SevenSegment segHr10,segHr1,segMin10,segMin1,segYr4,segYr3,segYr2,segYr1,segMth2,segMth1,segDay2,segDay1;
    AMPM indicatorAMPM;

    
    //SevenSegment myDigitA,myDigitB,myDigitC,myDigitD;
      struct ts t;
    double hr,mn,hr1,hr2,mn1,mn2,hrA_prev,hrB_prev,mnC_prev,mnD_prev,colonStatus;
    double alarmHr,alarmMn;
    double setHr,setMn,intHrA,intHrB,intMnC,intMnD,setMonth,setDay,setYear;
    int setAMPM;
    int alarmAMPM;
    double mYear,mDay,mMonth;
    int blinkMonth,blinkDay,blinkYear,blinkAMPM;
    double dtYear,dtMonth,dtDay;
    int amOrPm;
    int intMode;
    int dateChanged;
    int AMPMChanged;
   public:
    Clock_OLED(double left_x,double top_y,double digit_width,double digit_height);  // The Constructor
    readTime(); // Function to read the time from the DS3231
    void setTime();
    void printTime();
    void setAlarm();
    displayTime(); // Function to display the time.
    int getMode();
    int setClockTime();
    void heartbeatCallback();
    void incrementHours();
    void setHours();
    void incrementMinutes();
    void setMinutes();
    void normalOperation();
    void eraseAM();
    void erasePM();
    void displayAM();
    void displayPM();
    void blinkAMPMOn();
    void blinkAMPMOff();
    void blinkMonthOn();
    void blinkMonthOff();
    void eraseDateString();
    void eraseDateStringMonth();
    void eraseDateStringYear();
    void eraseDateStringDay();
    void displayDate();
    void blinkDayOn();
    void blinkDayOff();
    void blinkYearOn();
    void blinkYearOff();
    void toggleAMPM();
    void toggleAMPMAlarm();
    void setTimeOfDay();
    void setTimeOfAlarm();
    void displayDateString();
    void incrementMonth();
    void setMonthValue();
    void incrementDay();
    void setDayValue();
    void incrementYear();
    void setYearValue();
    void setStartVariables(); // Initiazes variables required to trigger redraw of screen elements.
    void setDateYear(double year);
    void setDateMonth(double month);
    void setDateDay(double day);
    // Functions for Setting and Operating the Alarm
    void setAlarmTime();
    int displayHours(int hour); /* set the hours value in the display and return 1 if the hours changed */
    void displayMinutes(double minutes,int hoursChanged);
};
