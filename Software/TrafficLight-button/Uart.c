#include <reg52.h>
#include "main.h"
#include "Uart.h"
typedef unsigned char u8;
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE0;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}

void uart_send_byte(u8 byte_data)
{
 	SBUF = byte_data;
	while(!TI);
	TI=0;
}

void uart_send_string(u8 *str)
{
 	while(*str)
	{
	 	uart_send_byte(*str++);	
		Delay1ms(10);
	}
}

char putchar(char c){
	uart_send_byte(c);
	return c;
}
