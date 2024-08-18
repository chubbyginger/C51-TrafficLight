#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include "STCUART.h"
#include "main.h"
#include "Key.h"
#include "hwinit.h"

unsigned char state = 0;
/*
	State0: 车绿灯，行人红灯
	State1: 车倒计时绿灯，行人红灯
	State2: 车黄灯，行人红灯
	State3: 车红灯，行人红灯
	State4: 车红灯，行人倒计时绿灯
	State5: 车红灯，行人红灯
	然后回到State0
*/
unsigned char Tcnt = 20;
unsigned char Icnt = 20;

void Delay1ms(int t)		//@11.0592MHz
{
	int k = 0;
	for (k = 0; k < t; k++) 
	{
		unsigned char i, j;
		_nop_();
		i = 2;
		j = 199;
		do {
			while (--j);
		}
		while (--i);
	}
}

void switchState(int buttonState) {
	if (state == 0 && buttonState == 1) {
		state = 1;
		SendString("Switching to state 1\r\n");
		TR0 = 1;
	}
}

void clearScreen() {
	DCLK = 1;
	Display0 = 1;
	Display1 = 1;
	Display2 = 1;
	Display3 = 1;
	DCLK = 0;
}

void Timer0_ISR() interrupt 1 using 1 {
	TH0 = (65536 - 50*1000)/256;
	TL0 = (65536 - 50*1000)%256;
	if (Icnt > 0) {
		Icnt--;
	} else { // Tcnt=0时切换模式
		Icnt = 20;
		if (Tcnt > 0) {
			Tcnt--;
		} else {
			TR0 = 0;
			switch (state) {
				case 1:
					SendString("Switching to state 2\r\n");
					clearScreen();
					state = 2;
					Tcnt = 3;
					TR0 = 1;
					break;
				case 2:
					SendString("Switching to state 3\r\n");
					state = 3;
					Tcnt = 3;
					TR0 = 1;
					break;
				case 3:
					SendString("Switching to state 4\r\n");
					state = 4;
					Tcnt = 20;
					TR0 = 1;
					break;
				case 4:
					SendString("Switching to state 5\r\n");
					state = 5;
					Tcnt = 3;
					TR0 = 1;
					break;
				case 5:
					SendString("Switching to state 0\r\n");
					state = 0;
					Tcnt = 20;
					break;
				default:
					SendString("FSM internal error");
					break;
			}
		}
	}
}

void main() {
	UartInit();
	SendString("UART initialization OK\r\n");
	Timer0Init();
	SendString("Timer0 initialization OK\r\n");
	DisplayInit();
	SendString("Display initialization OK\r\n");
	
	while (1)
	{
		switchState(ReadKey());
		if (state == 0)
		{
			LED1_R = 0;
			LED1_Y = 0;
			LED1_G = 1;
			LED2_R = 1;
			LED2_Y = 0;
			LED2_G = 0;
		}
		else if (state == 1)
		{
			LED1_R = 0;
			LED1_Y = 0;
			LED1_G = 1;
			LED2_R = 1;
			LED2_Y = 0;
			LED2_G = 0;
			if (Tcnt <= 9) {
				DCLK = 1;
				Display0 = Tcnt%2;	
				Display1 = (Tcnt/2)%2;
				Display2 = (Tcnt/4)%2;
				Display3 = (Tcnt/8)%2;
				DCLK = 0;
			} else {
				DCLK = 1;
				Display0 = 1;
				Display1 = 1;
				Display2 = 1;
				Display3 = 1;
				DCLK = 0;
			}
		}
		else if (state == 2)
		{
			LED1_R = 0;
			LED1_Y = 1;
			LED1_G = 0;
			LED2_R = 1;
			LED2_Y = 0;
			LED2_G = 0;
		}
		else if (state == 3)
		{
			LED1_R = 1;
			LED1_Y = 0;
			LED1_G = 0;
			LED2_R = 1;
			LED2_Y = 0;
			LED2_G = 0;
		}
		else if (state == 4)
		{
			LED1_R = 1;
			LED1_Y = 0;
			LED1_G = 0;
			LED2_R = 0;
			LED2_Y = 0;
			LED2_G = 1;
			if (Tcnt <= 9) {
				DCLK = 1;
				Display0 = Tcnt%2;	
				Display1 = (Tcnt/2)%2;
				Display2 = (Tcnt/4)%2;
				Display3 = (Tcnt/8)%2;
				DCLK = 0;
			} else {
				DCLK = 1;
				Display0 = 1;
				Display1 = 1;
				Display2 = 1;
				Display3 = 1;
				DCLK = 0;
			}
		}
		else if (state == 5)
		{
			LED1_R = 1;
			LED1_Y = 0;
			LED1_G = 0;
			LED2_R = 1;
			LED2_Y = 0;
			LED2_G = 0;
		}
		else
		{
			LED1_R = 0;
			LED1_Y = 0;
			LED1_G = 1;
			LED2_R = 1;
			LED2_Y = 0;
			LED2_G = 0;
		}
		Delay1ms(10);
	}
}