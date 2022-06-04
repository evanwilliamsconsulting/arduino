// DO NOT ADD YOUR OWN FONTS TO THIS FILE
// If you want to use your own fonts you should just drop the font .c file into your sketch folder.
// ------------------------------------------------------------------------------------------------

#if defined(__AVR__)
	#include <avr/pgmspace.h>
#elif defined(__PIC32MX__)
	#define PROGMEM
#elif defined(__arm__)
	#define PROGMEM
#endif

// SmallFont.c 
// Font Size	: 8x10
// Memory usage	: 1144 bytes
// # characters	: 95
