//======================================================
//  The information contained herein is the exclusive property of
//  Sunnnorth Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNNORTH TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  工程名称：	new_wifi
//  功能描述：	WiFi模块数据传输实验,
//				WiFi模块做TCP客户端，连接远程TCP服务器，连接成功后，发送传感器数据到TCP服务器
//  涉及的库：	CMacro1016.lib
//  组成文件：	main.c、
//			wifi.c文件, wifi.h头文件、
//			uart.c文件, uart.h头文件、
//			SHT10.c文件,  SHT10.h头文件、
//			isr.c
//	硬件连接： SHT10  DATA接IOA7，CLK接IOA8
//			   SPCE061A串口接WiFi模块
//	维护记录：	2011-12-16 v1.0
//===============================================
#define EXTERN
#include	"wifi_drv/wifi.h"
#include "SystemTime.h"
#include	"SHT10.h"
#include "wifi_pkgman.h"
#include <string.h>

#define DEFAULT_ESSID	"sunplus_001"
#define ESSID_ADDR		0xFF00

#define SET_LED1    UART_Send("AT+CIOWRITE=4,0\r\n",17)
#define SET_LED2    UART_Send("AT+CIOWRITE=5,0\r\n",17)
#define RESET_LED1    UART_Send("AT+CIOWRITE=4,1\r\n",17)
#define RESET_LED2    UART_Send("AT+CIOWRITE=5,1\r\n",17)

int tempre;													//  温度实际值的100倍
int humit;
void Temp_Humi_Collect(void);

void ReportNodeInfo(void)
{
	unsigned char profile[] = {
		CtlQueryProfile, 
//			0,0,0,0,0,0,
		2,
		1, 0, 5,
		2, 0, 5,
	};
//		memcpy(&profile[1], mac, 6);
	pkgman_send_packageEx(0, 0, profile, sizeof(profile));
}

int main()
{
	PM_RECVINFO recvPkgInfo;
	WaitInfo tempWait, humiWait;
//	int cid = -1;
	const char *essid = DEFAULT_ESSID;

	{
		unsigned int flag = *(unsigned int *)ESSID_ADDR;
		if((flag != 0xFFFF) && (flag != 0x0000))
			essid = (const char *)ESSID_ADDR;
	}

	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	SHT10_init(0x01);
	*P_INT_Mask |= (C_IRQ4_1KHz | C_IRQ5_2Hz);				//开2Hz中断，用来定时清看门狗和延时,1KHz用来计时
	__asm("IRQ ON");
	// 初始化Wifi
	while(Wifi_Init() != 1)

		*P_Watchdog_Clear = 0x0001;
		
	SET_LED1;
	SystemTickWait(500);
	SET_LED2;
	SystemTickWait(500);
	loop:
	{
//		char oldESSID[30];
//		Wifi_GetSSID(oldESSID); 

			// rewrite settings
			int ret = Wifi_Reset();
			SystemTickWait(200);
			UART_Send("ATE0\r\n",6);
			SystemTickWait(200);			
			ret = Wifi_SetWorkMode(STAMODE);
			SystemTickWait(100);
			ret = Wifi_SetMux(1);									// 设置串口Wifi模为多链接模式
			SystemTickWait(100);
			RECONNECT:if(strncasecmp(essid, "sunplus", 7) == 0)
			ret = Wifi_SetSSID(essid,"12345678");								// 设置串口Wifi模块连接的热点的名字和密码
			else Wifi_SetSSID(&DEFAULT_ESSID,"12345678");
        	SystemTickWait(1000);
        	while(ret=Wifi_RecvFlag(CWJAP))
        		if(ret==2)goto RECONNECT;
        	SystemTickWait(3000);
			ret = Wifi_ConfigureSocket(0, 1, 5357, "192.168.0.1");		// 设置串口Wifi模块连接的TCP服务器地址
			SystemTickWait(500);
			while(Wifi_RecvFlag(CIPSTART));
			RESET_LED1;
			SystemTickWait(500);
			RESET_LED2;
			SystemTickWait(500);

	}

	SystemTickWaitAsync(&tempWait, 5000);
	SystemTickWaitAsync(&humiWait, 2500);
	pkgman_init_recv_info(&recvPkgInfo);
	ReportNodeInfo();
	while(1)
	{
	
			
		if(Wifi_RecvFlag(DISCONNECT)==0)
		{
			SET_LED2;
			SystemTickWait(500);
		}
		else if(Wifi_RecvFlag(CWJAP)==0)
		{			
			goto loop;
		}	
		

 		if(SystemTickWaitFinished(&tempWait) == 1)
		{ 
			unsigned char val[2];
			int t = 0;
		    SystemTickClearWait(&tempWait);
			Temp_Humi_Collect();
    		t = (tempre << 2) - 3960;
			val[0] = t&0xFF;
			val[1] = t>>8;
			pkgman_send_packageEx(0, 1, val, 2);
		    SystemTickWaitAsync(&tempWait, 5000);
		} 
		if(SystemTickWaitFinished(&humiWait) == 1)
		{
			unsigned char val[2];
		    SystemTickClearWait(&humiWait);
			Temp_Humi_Collect();
			humit &= 0xFF;
			humit = (65 * humit) - 400 - ((295 * (unsigned long)humit * (unsigned long)humit) >> 12);
			val[0] = humit&0xFF;
			val[1] = humit>>8;
			pkgman_send_packageEx(0, 2, val, 2);
		    SystemTickWaitAsync(&humiWait, 5000);
		}
 		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared
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
	//tempre = CalcT(temp_value); //2167;
	tempre = temp_value; //2167;
	if(error!=0)
		SHT10_Connectionreset();   //in case of an error: connection reset

	error+=SHT10_Measure((unsigned int*) &humi_value,&checksum,HUMIDITY);//measure temperature
	//humit  = CalcRH(humi_value);//3498;
	humit = humi_value;
	if(error!=0)
		SHT10_Connectionreset();   //in case of an error: connection reset
}

