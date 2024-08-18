/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC89-90xx Series MCU UART (8-bit/9-bit)Demo ----------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

#include "reg51.h"
#include "intrins.h"
#include "STCUART.h"
#include "main.h"

bit busy;

void UartInit()
{
    SCON = 0x50;            //8-bit variable UART
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
    TH1 = -(FOSC/12/32/BAUD); //Set auto-reload vaule
		TL1 = -(FOSC/12/32/BAUD);
		ET1 = 0;
    TR1 = 1;                //Timer1 start run
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(BYTE dat)
{
    SBUF = dat;             //Send data to UART buffer
		while (!TI);
		TI = 0;
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(char *s)
{
    while (*s != '\0')              //Check the end of the string
    {
        SendData(*s);     //Send current char
			  s++;
    }
}

