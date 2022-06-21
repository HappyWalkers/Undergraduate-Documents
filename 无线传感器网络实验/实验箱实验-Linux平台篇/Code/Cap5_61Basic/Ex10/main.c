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
//			SHT10.c文件,  SHT10.h头文件、
//			isr.c
//	硬件连接：
//	维护记录：	2011-12-14 v1.0
//===============================================
#include "wifi/wifi.h"
#include "wifi/SystemTime.h"
#include "SHT10.h"
#include <stdio.h>
#include <stdlib.h>

int tempre;													//  温度实际值的100倍
int humit; 													//  湿度实际值的100倍，humidity [hju:'mid?ti]	 湿度；湿气
void Temp_Humi_Collect(void);

const char *ssid = "sunplus001";							// 热点名
const char *key = "12345678";								// 密钥
const char *ip = "192.168.0.2";								// 模块的IP地址
const char *serverIP = "192.168.0.1";						// PC机的IP地址
unsigned short port = 8080;									// PC机上创建的TCP服务器的端口

int main()
{ 
	int ret;
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	SHT10_init(0x01);
	*P_INT_Ctrl = C_IRQ5_2Hz | C_IRQ4_1KHz;					//开2Hz中断，用来定时清看门狗和延时,1KHz终端,用于计时
	__asm("IRQ ON");
	// 初始化串口Wifi模块
	while(Wifi_Init() != 1)
		*P_Watchdog_Clear = 0x0001;

	// Wifi_Init之后模块处于AT指令模式,可以直接发送指令
	ret = Wifi_SetWorkMode(STAMODE);						// 设置串口Wifi模块工作在STA模式
	ret = Wifi_SetSSID(ssid);								// 设置串口Wifi模块连接的热点的名字
	ret = Wifi_SetKey(WPA2KEY, key);						// 设置串口Wifi模块连接热点时使用的密钥
	ret = Wifi_SetIP(0, ip, "255.255.255.0", serverIP);
															// 设置串口Wifi模块的IP地址
	ret = Wifi_ConfigureSocket(0, 1, port, serverIP);		// 设置串口Wifi模块连接的TCP服务器地址
	ret = Wifi_EnableSocket(1);								// 使能TCP连接
	ret = Wifi_Reset();										// 重启模块,使上述设置生效
	SystemTickWait(3000);									// 等待模块启动完成,大约3秒钟

	while(1)
	{
		char valueString[50];
		int len;
		Temp_Humi_Collect();								//采集数据
		if(tempre < -100)
			tempre = 0;
		len = sprintf(valueString,							// 将温湿度变成字符串
					"Temp:%02d.%02d, Humi:%02d.%02d\r\n",
					tempre / 100, abs(tempre % 100),
					humit / 100, humit % 100);
		UART_Send(valueString, len);						//通过串口发送数据,在透传模式下数据可被TCP服务器接收到
		SystemTickWait(2000);								// 等待大约2秒钟
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

