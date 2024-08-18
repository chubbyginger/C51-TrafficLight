#ifndef _STCUART_H_
#define _STCUART_H_

typedef unsigned char BYTE;
typedef unsigned int WORD;

void UartInit(void);
void SendData(BYTE dat);
void SendString(char *s);

#endif