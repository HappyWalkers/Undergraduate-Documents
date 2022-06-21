//======================================================
//  The information contained herein is the exclusive property of
//  SUNPLUSAPP Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNPLUSAPP TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  工程名称：	Ex_?
//  功能描述：	震动数据传输实验


//  涉及的库：	CMacro1016.lib       	
//  组成文件：	main.c、
//		
//				uart.c文件, uart.h头文件、
//				isr.c
//	硬件连接：
//	维护记录：	2011-12-14 v1.0
//===============================================
#include	"uart.h"
#include 	"Shake.h"


void ShakeInit(void);
unsigned char ShakeRefresh(void);


unsigned char work;
unsigned char valueString[20];
unsigned char ShakeSensorFlag = NORMAL;


int main()
{
	//add your code here
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	ShakeInit();
	SP_UARTInitial();						//UART初始化	
	*P_INT_Ctrl = C_IRQ5_2Hz|C_IRQ4_4KHz;	//开2Hz中断，用来定时清看门狗和延时
	__asm("IRQ ON");
	while(1)
	{
		;
	}
	return 0;
}

void ShakeInit(void)
{
    *P_IOA_Dir &= ~SHAKE_IN;         //IOA0作为震动传感器的输入端 设置为带上拉电阻的输入端口
	*P_IOA_Attrib &= ~SHAKE_IN;
	*P_IOA_Data |= SHAKE_IN;
}
unsigned char ShakeRefresh(void)
{
    // 第3行显示检测到的状态
   unsigned char SensorFlag = 0;
   SensorFlag = READ_IOA_BIT(SHAKE_IN);
   return SensorFlag;
}

//============================================================= 
// 语法格式:    void IRQ4(void);
// 实现功能:	清看门狗
// 参数:    	无
// 返回值:    	无
//=============================================================	
void IRQ4(void) __attribute__((ISR));
void IRQ4(void)
{
	if(*P_INT_Ctrl & C_IRQ4_4KHz)
	{
		if(ShakeRefresh()== WARNING)
		{
			ShakeSensorFlag = WARNING;
			sprintf(valueString,"Current Shake:%02d\n",ShakeSensorFlag);		//将震动传感器数据变成字符串	
			Uart_Send_String(valueString);			//通过串口发送数据,
		}					
		*P_INT_Clear = C_IRQ4_4KHz;
	}
	
}
//============================================================= 
// 语法格式:    void IRQ5(void);
// 实现功能:	清看门狗
// 参数:    	无
// 返回值:    	无
//=============================================================
void IRQ5(void) __attribute__ ((ISR));
void IRQ5(void)
{
	*P_Watchdog_Clear = 0x0001;
	//串口发送当前温度值
	ShakeSensorFlag = ShakeRefresh();
	sprintf(valueString,"Current Shake:%02d\n",ShakeSensorFlag);		//将震动传感器数据变成字符串	
	Uart_Send_String(valueString);			//通过串口发送数据,
	*P_INT_Clear = C_IRQ5_2Hz;  //清中断标志
}