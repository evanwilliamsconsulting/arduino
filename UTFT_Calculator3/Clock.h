/*

Clock.h

*/
class Clock
{
   private:
    int offset_x;
	int offset_y;
	int side_len;
   public:
    Clock(UTFT myGLCD);
	paintClock();
};
