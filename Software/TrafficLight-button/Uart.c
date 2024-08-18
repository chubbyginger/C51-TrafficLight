#include <reg52.h>
#include "main.h"
#include "Uart.h"
typedef unsigned char u8;
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xE0;			//���ö�ʱ��ʼֵ
	TH1 = 0xFE;			//���ö�ʱ��ʼֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
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
