#ifndef _MAIN_H_
#define _MAIN_H_

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

typedef unsigned char u8;
sbit LED_startup = P2^3;
sbit LED_startup2 = P2^2;

sbit LED1_R = P0^6;
sbit LED1_Y = P0^5;
sbit LED1_G = P0^4;

sbit LED2_R = P0^7;
sbit LED2_Y = P1^6;
sbit LED2_G = P1^7;

sbit button1 = P3^2;
sbit button2 = P3^3;

sbit Display0 = P0^0;
sbit Display1 = P0^1;
sbit Display2 = P0^2;
sbit Display3 = P0^3;
sbit DCLK = P3^7;

sbit LED20 = P2^0;

void Delay1ms(int t);

#endif