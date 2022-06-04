#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-04-09 02:13:11

#include "Arduino.h"
#include "Arduino.h"
#include "Fonts.h"
#include "Calculator.h"
#include "Clock.h"
#include "SevenSegment.h"
#include "Keys.h"
#include "Terminal.h"
#include <avr/pgmspace.h>

void setup() ;
void loop() ;
void setup() ;
void printHex(unsigned int x,char &c1,char &c2,char &c3,char &c4) ;
void printDec(unsigned int x,int r,int c) ;
void getLargeChar(char currentKey,uint16_t theChar) ;
void looptest() ;
void loop() ;
void putKey(char keycode)   ;
char lookupChar(int x,int y) ;
void paintCalculator() ;

#include "Keyboard_4.ino"

#include "UTFT_Keyboard4.ino"

#endif
