//======================================================
// 文件名称:	isr.c
// 功能描述：   清看门狗、接收UART数据 
// 维护记录：  	
//				
//======================================================
#define EXTERN  extern 
#include "SPCE061A.h"
#include "SystemTime.h"

extern unsigned char ugetSensorDataFlag;
void IRQ0()__attribute__((ISR));
void IRQ0()
{
	if(*P_INT_Ctrl & C_IRQ0_PWM)
	{
		ugetSensorDataFlag = 1;
		*P_INT_Clear = C_IRQ0_PWM;
	}
}

void IRQ4()__attribute__((ISR));
void IRQ4()
{
	if(*P_INT_Ctrl & C_IRQ4_1KHz)
	{
		SystemTickISR();
		*P_INT_Clear = C_IRQ4_1KHz;
	}
}

void IRQ5()__attribute__((ISR));
void IRQ5()
{
	if(*P_INT_Ctrl & C_IRQ5_2Hz)
	{
		*P_Watchdog_Clear = 0x0001;
		*P_INT_Clear = C_IRQ5_2Hz;
	}
}
