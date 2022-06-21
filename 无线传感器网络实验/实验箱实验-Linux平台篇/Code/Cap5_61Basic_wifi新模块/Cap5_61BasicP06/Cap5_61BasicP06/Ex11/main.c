//======================================================
//  The information contained herein is the exclusive property of
//  SUNPLUSAPP Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNPLUSAPP TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  �������ƣ�	Ex_?
//  ����������	WiFiģ�����ݴ���ʵ��


//  �漰�Ŀ⣺	CMacro1016.lib       	
//  ����ļ���	main.c��
//			wifi.c�ļ�, wifi.hͷ�ļ���
//			uart.c�ļ�, uart.hͷ�ļ���
//			isr.c
//	Ӳ�����ӣ�
//	ά����¼��	2011-12-14 v1.0
//===============================================
#include "wifi/wifi.h"
#include "wifi/SystemTime.h"
#include <stdio.h>
#include <stdlib.h>
#include "Shake\Shake.h"	//  �𶯴�����

#define SET_LED1    UART_Send("AT+CIOWRITE=4,0\r\n",17)
#define SET_LED2    UART_Send("AT+CIOWRITE=5,0\r\n",17)
#define RESET_LED1    UART_Send("AT+CIOWRITE=4,1\r\n",17)
#define RESET_LED2    UART_Send("AT+CIOWRITE=5,1\r\n",17)
												
unsigned char Get_Shake(void);

const char *ssid = "sunplus_001";							// �ȵ���
const char *key = "12345678";								// ��Կ
const char *ip = "192.168.0.3";	//"192.168.0.2";			// ģ���IP��ַ
const char *serverIP = "192.168.123.1";						// PC����IP��ַ
unsigned short port = 8080;									// PC���ϴ�����TCP�������Ķ˿�

extern unsigned char ShakeSensorFlag;
int main()
{ 
	int ret;	
	unsigned char valueString[20],SendCmd[20];	
	
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	ShakeInit();
	*P_INT_Ctrl = C_IRQ5_2Hz | C_IRQ4_1KHz | C_IRQ4_4KHz;	//��2Hz�жϣ�������ʱ�忴�Ź�����ʱ,1KHz�ն�,���ڼ�ʱ
	__asm("IRQ ON");
	// ��ʼ������Wifiģ��
	while(Wifi_Init() != 1)
		*P_Watchdog_Clear = 0x0001;
	SET_LED1;
	SystemTickWait(500);
	SET_LED2;
	SystemTickWait(500);
	// Wifi_Init֮��ģ�鴦��ATָ��ģʽ,����ֱ�ӷ���ָ��
	ret = Wifi_Reset();										//��λWiFi�ڵ�ģ��
	SystemTickWait(200);	
	UART_Send("ATE0\r\n",6);
	SystemTickWait(200);
	ret = Wifi_SetWorkMode(STAMODE);						// ���ô���Wifiģ�鹤����STAģʽ
	SystemTickWait(100);
	ret = Wifi_SetMux(1);									// ���ô���WifiģΪ������ģʽ
	SystemTickWait(100);
	ret = Wifi_SetSSID(ssid,key);								// ���ô���Wifiģ�����ӵ��ȵ�����ֺ�����
	SystemTickWait(5000);
	while(Wifi_RecvFlag(CWJAP));
	SystemTickWait(3000);	
	ret = Wifi_ConfigureSocket(1, 1, port, serverIP);		// ���ô���Wifiģ�����ӵ�TCP��������ַ
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
		sprintf(valueString,"Shake:%02d\n",ShakeSensorFlag);	//���𶯴��������ݱ���ַ���
		
		sprintf(SendCmd,"AT+CIPSEND=1,9\r\n");
		UART_Send(SendCmd, 16);
		SystemTickWait(200);	
		UART_Send(valueString, sizeof(valueString));		//ͨ�����ڷ�������,��͸��ģʽ�����ݿɱ�TCP���������յ�		
		SystemTickWait(2000);
		*P_Watchdog_Clear = 0x0001;							//�ȴ���Լ2����
	}
}

/*****************************************************************
��API ��ʽ����void Get_Shake(void)
������˵��������ȡ�𶯴���������
����    ������
���� �� ֵ����shake_value ����������
��ʹ�þ�������Get_Shake();
����    ע��: 
*****************************************************************/
unsigned char Get_Shake(void)
{
	unsigned char shake_value;
	shake_value = ShakeRefresh();
	return shake_value;
}

