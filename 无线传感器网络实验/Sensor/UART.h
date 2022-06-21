#ifndef __UART_H__
#define __UART_H__


#include "Basic.h"
#include <string.h>

// CC2530 UART 波特率可选值
typedef enum
{
  BAUD_2400,      //U0GCR |= 6;     U0BAUD |= 59;
  BAUD_4800,      //U0GCR |= 7;     U0BAUD |= 59;
  BAUD_9600,      //U0GCR |= 8;     U0BAUD |= 59;
  BAUD_14400,     //U0GCR |= 8;     U0BAUD |= 216;
  BAUD_19200,     //U0GCR |= 9;     U0BAUD |= 59;
  BAUD_28800,     //U0GCR |= 9;     U0BAUD |= 216;
  BAUD_38400,     //U0GCR |= 10;    U0BAUD |= 59;
  BAUD_57600,     //U0GCR |= 10;    U0BAUD |= 216;
  BAUD_76800,     //U0GCR |= 11;    U0BAUD |= 59;
  BAUD_115200,    //U0GCR |= 11;    U0BAUD |= 216;
  BAUD_230400,    //U0GCR |= 12;    U0BAUD |= 216;
}BaudSel;

//UART0 初始化设置
void UART0_Init(BaudSel baud);
//UART0 发送数据
void UART0_Send(char *Data,int len);
//UART0 以十进制方式显示无符号数
void UART0_Dis_uNum(uint16 uValue );
//UART0 以十进制方式显示浮点型数
void UART0_Dis_fNum(float fValue );

#endif//__UART_H__
