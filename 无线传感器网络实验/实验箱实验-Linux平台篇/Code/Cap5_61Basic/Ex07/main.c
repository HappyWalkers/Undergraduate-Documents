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
//  功能描述：	WiFi模块数据传输实验


//  涉及的库：	CMacro1016.lib       	
//  组成文件：	main.c、
//		
//			uart.c文件, uart.h头文件、
//			SHT10.c文件,  SHT10.h头文件、
//			isr.c
//	硬件连接：
//	维护记录：	2011-12-14 v1.0
//===============================================
#include    "SPCE061A.h"
#include	"SHT10.h"
#include	"uart.h"
int tempre;													//  温度实际值的100倍
int humit; 													//  湿度实际值的100倍，humidity [hju:'mid?ti]	 湿度；湿气

void Temp_Humi_Collect(void);
int main()
{ 
	unsigned char work;
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	SHT10_init(0x01);
	SP_UARTInitial();											//UART初始化
	*P_INT_Ctrl = C_IRQ5_2Hz;									//开2Hz中断，用来定时清看门狗和延时
	__asm("IRQ ON");
	
	
	
	while(1)
	{
		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared

		Temp_Humi_Collect();									//采集数据

	
			
		//串口发送当前温度值
		Uart_Send_String("Current Temp:");
			
		work = (unsigned char)(tempre/1000) + '0';					// 千位
		Uart_Send_ASC(work);								//串口发送温度整数
		work = (unsigned char)(tempre%1000/100) + '0';				// 百位
		Uart_Send_ASC(work);				
		work = '.';
		Uart_Send_ASC(work);
		work = (unsigned char)(tempre%100/10) + '0';				// 十位
		Uart_Send_ASC(work);								//串口发送温度小数
		work = (unsigned char)(tempre%10) + '0';					// 个位
		Uart_Send_ASC(work);
		
		//串口发送当前湿度值
		Uart_Send_String(";Current Humidity:");
		work = (unsigned char)(humit/1000) + '0';					// 千位
		Uart_Send_ASC(work);							//串口发送湿度整数
		work = (unsigned char)(humit%1000/100) + '0';				// 百位
		Uart_Send_ASC(work);			
		work = '.';
		Uart_Send_ASC(work);
		work = (unsigned char)(humit%100/10) + '0';					// 十位
		Uart_Send_ASC(work);								//串口发送湿度小数
		work = (unsigned char)(humit%10) + '0';						// 个位
		Uart_Send_ASC(work);
		Uart_Send_String("\r\n");
		
	}
}

/*****************************************************************
【API 格式】：void Temp_Humi_Collect(void)
【功能说明】：获取温湿度传感器SHT10数据
【参    数】：
【返 回 值】：
【使用举例】：Temp_Humi_Collect();
【备    注】: 
*****************************************************************/
void Temp_Humi_Collect(void)
{
	unsigned int error,temp_value,humi_value;
	unsigned char checksum;
	error = 0;
	
	error+=SHT10_Measure((unsigned int*) &temp_value,&checksum,TEMPERATURE);//measure temperature
	tempre = CalcT(temp_value); //2167;  	
	if(error!=0) 	   	
		SHT10_Connectionreset();   //in case of an error: connection reset

	error+=SHT10_Measure((unsigned int*) &humi_value,&checksum,HUMIDITY);//measure temperature
	humit  = CalcRH(humi_value);//3498; 		  
	if(error!=0) 	   	
	SHT10_Connectionreset();   //in case of an error: connection reset
}

