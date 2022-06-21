

#include "SPCE061A.h"
#define C_UARTBaudRate_9600_H  0x05
#define C_UARTBaudRate_9600_L  0x00
void Uart_Init();


int main()
{
	__asm("IRQ OFF");
	Uart_Init();					   				// UART初始化
	while(1)
	{
		*P_Watchdog_Clear = 0x0001;					// 清看门狗
	
		if((*P_UART_Command2&0x80) != 0 ) 			// 接收到数据  P_UART_Command2 bit7 ==1
		{
			while (!((*P_UART_Command2) & C_UART_Tx_RDY));
			*P_UART_Data = *P_UART_Data;
		}
	}
	return 0;
}

/*****************************************************************
【API 格式】：void Uart_Init(void)
【功能说明】：Uart初始化；
【参	数】：无；
【返 回 值】：无；
【使用举例】：Uart_Init();
【备    注】: 
*****************************************************************/
void Uart_Init()
{
	*P_IOB_Attrib = 0x0480;	
	*P_IOB_Dir = 0x0400;				 					
	*P_IOB_Data = 0x0400;
							
	*P_UART_BaudScalarHigh = C_UARTBaudRate_9600_H;		//波特率设为9600
	*P_UART_BaudScalarLow = C_UARTBaudRate_9600_L;


	*P_UART_Command1 = 0x00;				
	*P_UART_Command2 = 0x00c0;	
		
}
