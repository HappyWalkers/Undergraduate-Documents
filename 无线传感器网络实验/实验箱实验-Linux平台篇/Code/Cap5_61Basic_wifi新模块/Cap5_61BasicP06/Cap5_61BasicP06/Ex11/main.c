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
//			wifi.c文件, wifi.h头文件、
//			uart.c文件, uart.h头文件、
//			isr.c
//	硬件连接：
//	维护记录：	2011-12-14 v1.0
//===============================================
#include "wifi/wifi.h"
#include "wifi/SystemTime.h"
#include <stdio.h>
#include <stdlib.h>
#include "Shake\Shake.h"	//  震动传感器

#define SET_LED1    UART_Send("AT+CIOWRITE=4,0\r\n",17)
#define SET_LED2    UART_Send("AT+CIOWRITE=5,0\r\n",17)
#define RESET_LED1    UART_Send("AT+CIOWRITE=4,1\r\n",17)
#define RESET_LED2    UART_Send("AT+CIOWRITE=5,1\r\n",17)
												
unsigned char Get_Shake(void);

const char *ssid = "sunplus_001";							// 热点名
const char *key = "12345678";								// 密钥
const char *ip = "192.168.0.3";	//"192.168.0.2";			// 模块的IP地址
const char *serverIP = "192.168.123.1";						// PC机的IP地址
unsigned short port = 8080;									// PC机上创建的TCP服务器的端口

extern unsigned char ShakeSensorFlag;
int main()
{ 
	int ret;	
	unsigned char valueString[20],SendCmd[20];	
	
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	ShakeInit();
	*P_INT_Ctrl = C_IRQ5_2Hz | C_IRQ4_1KHz | C_IRQ4_4KHz;	//开2Hz中断，用来定时清看门狗和延时,1KHz终端,用于计时
	__asm("IRQ ON");
	// 初始化串口Wifi模块
	while(Wifi_Init() != 1)
		*P_Watchdog_Clear = 0x0001;
	SET_LED1;
	SystemTickWait(500);
	SET_LED2;
	SystemTickWait(500);
	// Wifi_Init之后模块处于AT指令模式,可以直接发送指令
	ret = Wifi_Reset();										//复位WiFi节点模块
	SystemTickWait(200);	
	UART_Send("ATE0\r\n",6);
	SystemTickWait(200);
	ret = Wifi_SetWorkMode(STAMODE);						// 设置串口Wifi模块工作在STA模式
	SystemTickWait(100);
	ret = Wifi_SetMux(1);									// 设置串口Wifi模为多链接模式
	SystemTickWait(100);
	ret = Wifi_SetSSID(ssid,key);								// 设置串口Wifi模块连接的热点的名字和密码
	SystemTickWait(5000);
	while(Wifi_RecvFlag(CWJAP));
	SystemTickWait(3000);	
	ret = Wifi_ConfigureSocket(1, 1, port, serverIP);		// 设置串口Wifi模块连接的TCP服务器地址
	while(Wifi_RecvFlag(CIPSTART));
	//SystemTickWait(3000);
	
	RESET_LED1;
	SystemTickWait(500);		
	RESET_LED2;
	SystemTickWait(500);
	while(1)
	{
		if(Wifi_RecvFlag(DISCONNECT)==0)
		{
			SET_LED2;
			SystemTickWait(500);
		}
//		else if(Wifi_RecvFlag(CWJAP)==0)
//		{			
//			Wifi_ConfigureSocket(0, 1, 5357, "192.168.0.1");
//			SystemTickWait(500);
//			while(Wifi_RecvFlag(CIPSTART));
//			RESET_LED2;
//			SystemTickWait(500);
//		}		
		sprintf(valueString,"Shake:%02d\n",ShakeSensorFlag);	//将震动传感器数据变成字符串
		
		sprintf(SendCmd,"AT+CIPSEND=1,9\r\n");
		UART_Send(SendCmd, 16);
		SystemTickWait(200);	
		UART_Send(valueString, sizeof(valueString));		//通过串口发送数据,在透传模式下数据可被TCP服务器接收到		
		SystemTickWait(2000);
		*P_Watchdog_Clear = 0x0001;							//等待大约2秒钟
	}
}

/*****************************************************************
【API 格式】：void Get_Shake(void)
【功能说明】：获取震动传感器数据
【参    数】：
【返 回 值】：shake_value 传感器数据
【使用举例】：Get_Shake();
【备    注】: 
*****************************************************************/
unsigned char Get_Shake(void)
{
	unsigned char shake_value;
	shake_value = ShakeRefresh();
	return shake_value;
}

