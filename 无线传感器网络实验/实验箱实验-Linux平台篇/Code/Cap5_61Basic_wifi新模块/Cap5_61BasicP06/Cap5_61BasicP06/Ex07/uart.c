//======================================================
// 文件名称:	uart.c
// 功能描述：   SPCE061A串口驱动程序 
// 维护记录：  	
//				
//======================================================
#include    "SPCE061A.h"
#include    "uart.h"
//============================================================= 
// 语法格式:    void SP_UARTInitial(void);
// 实现功能:	UART初始化
// 参数:    	无
// 返回值:    	无
//=============================================================
void SP_UARTInitial(void)
{
	*P_IOB_Dir |= 0x0400;	//bit10设为输出口（Tx）,bit7设为输入口（Rx）   0100 0000 0000  IOB10 =1				
	*P_IOB_Dir &= 0xff7f;	// 1111 1111 0111 1111  IOB8 = 0				 		
	*P_IOB_Attrib |= 0x0480;					
	*P_IOB_Buffer &= 0xfb7f;
						
	*P_UART_Command1 = C_UART_Reset;					//UART复位
	
	*P_UART_BaudScalarHigh = C_UARTBaudRate_9600_H;		//波特率设为9600
	*P_UART_BaudScalarLow = C_UARTBaudRate_9600_L;

	*P_UART_Command1 = C_UART_Rx_IRQ_ENB;				//UART接收中断使能
	*P_UART_Command2 = C_UART_Rx_Pin_ENB|C_UART_Tx_Pin_ENB;				//UART接收管脚使能 ,发送管脚使能
}

void Uart_Send_ASC(unsigned char ch)
{
	*P_UART_Data = ch;
	while (!((*P_UART_Command2) & C_UART_Tx_RDY));
}
//发送字符串
void Uart_Send_String(unsigned char *ptr)
{
	while (*ptr != '\0')
	{
		Uart_Send_ASC(*ptr);
		ptr++;
	}
}
// 
//============================================================= 
// 语法格式:    
//	void Uart_Send_Multi_ASC(unsigned char *ptr,unsigned char cnt)
// 实现功能:	发送多个ASC
// 参数:    	*ptr 参数指针
//	           cnt 参数个数
// 返回值:    	无
//=============================================================

void Uart_Send_Multi_ASC(unsigned char *ptr,unsigned char cnt)
{
	unsigned char i;

	for(i=0;i<cnt;i++)  
	{
		Uart_Send_ASC(*ptr);
		ptr++;
	}
}
