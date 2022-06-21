//======================================================
// 文件名称:	isr.c
// 功能描述：   清看门狗、接收UART数据 
// 维护记录：  	
//				
//======================================================

#include "wifi/wifi.h"
#include "wifi/SystemTime.h"

void IRQ4(void) __attribute__((ISR));
void IRQ4(void)
{
	if(*P_INT_Ctrl & C_IRQ4_1KHz)
	{
		SystemTickISR();
		*P_INT_Clear = C_IRQ4_1KHz;
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
