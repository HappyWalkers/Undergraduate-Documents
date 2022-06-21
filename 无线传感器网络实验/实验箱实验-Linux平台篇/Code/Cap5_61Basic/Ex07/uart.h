//======================================================
// 文件名称:	uart.h
// 功能描述：   SPCE061A串口驱动头文件
// 维护记录：  	
//				
//======================================================
#ifndef _UART_H_
#define _UART_H_

#define 	C_UARTBaudRate_9600_H     0x05
#define 	C_UARTBaudRate_9600_L     0x00

void	SP_UARTInitial(void);
void	Uart_Send_ASC(unsigned char ch);
void 	Uart_Send_Multi_ASC(unsigned char *ptr,unsigned char cnt);

void	Uart_Send_String(unsigned char *ptr);





#endif
