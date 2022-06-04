#include <avr/pgmspace.h>
#include <UTFT.h>
/*

Clock.h

*/
const int CLOCK_HAND_SECOND=0;
const int CLOCK_HAND_MINUTE=1;
const int CLOCK_HAND_HOUR=2;

extern UTFT myGLCD;

class Clock
{
   private:
    double center_x;
	double center_y;
	double side_len;
	double seconds;
	double minutes;
	double hours;
   public:
    Clock(double offset_x,double offset_y,double side_len);
	void paintClock();
    void drawHand(int type,double clock_deg);
    void drawSecondHand(double seconds);
    void drawMinutesHand(double minutes);
    void drawHoursHand(double hours);
    void eraseHands();
};
