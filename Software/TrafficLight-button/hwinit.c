#include <reg51.h>
#include "main.h"

void DisplayInit() {
	DCLK = 1;
	Display0 = 1;
	Display1 = 1;
	Display2 = 1;
	Display3 = 1;
	DCLK = 0;
	LED1_R = 0;
	LED1_Y = 0;
	LED1_G = 1;
	LED2_R = 1;
	LED2_Y = 0;
	LED2_G = 0;
}

void Timer0Init() {
	TMOD |= 0x01;	  
	TH0 = (65536 - 50*1000)/256;
	TL0 = (65536 - 50*1000)%256;
	EA = 1;
	ET0 = 1;
	TR0 = 0;
}