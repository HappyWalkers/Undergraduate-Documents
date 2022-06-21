//======================================================
// 文件名称:	isr.c
// 功能描述：   清看门狗、接收UART数据 
// 维护记录：  	
//				
//======================================================

#include "wifi/wifi.h"
#include "wifi/SystemTime.h"
#include <stdio.h>
#include "Shake/Shake.h"

unsigned char valueString[20];
unsigned char ShakeSensorFlag = NORMAL;
	
void IRQ4(void) __attribute__((ISR));
void IRQ4(void)
{
	if(*P_INT_Ctrl & C_IRQ4_1KHz)
	{
		SystemTickISR();
		*P_INT_Clear = C_IRQ4_1KHz;
	}
	if(*P_INT_Ctrl & C_IRQ4_4KHz)
	{
		if(ShakeRefresh() == WARNING )
		{
			ShakeSensorFlag = WARNING;
			sprintf(valueString,"Shake:%02d\n",ShakeSensorFlag);	//将震动传感器数据变成字符串	
			UART_Send(valueString, sizeof(valueString));			//通过串口发送数据,在透传模式下数据可被TCP服务器接收到
		}					
		*P_INT_Clear = C_IRQ4_4KHz;
	}
}
//============================================================= 
// 语法格式:    void IRQ5(void);
// 实现功能:	清看门狗
// 参数:    无
// 返回值:    无
//=============================================================
void IRQ5(void) __attribute__ ((ISR));
void IRQ5(void)
{
	*P_Watchdog_Clear = 0x0001;
	*P_INT_Clear = C_IRQ5_2Hz;                                  //清中断标志
}
