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
												
unsigned char Get_Shake(void);

const char *ssid = "sunplus001";							// �ȵ���
const char *key = "12345678";								// ��Կ
const char *ip = "192.168.0.3";	//"192.168.0.2";			// ģ���IP��ַ
const char *serverIP = "192.168.0.1";						// PC����IP��ַ
unsigned short port = 8080;									// PC���ϴ�����TCP�������Ķ˿�

extern unsigned char ShakeSensorFlag;
int main()
{ 
	int ret;	
	unsigned char valueString[20];	
	
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	ShakeInit();
	*P_INT_Ctrl = C_IRQ5_2Hz | C_IRQ4_1KHz | C_IRQ4_4KHz;	//��2Hz�жϣ�������ʱ�忴�Ź�����ʱ,1KHz�ն�,���ڼ�ʱ
	__asm("IRQ ON");
	// ��ʼ������Wifiģ��
	while(Wifi_Init() != 1)
		*P_Watchdog_Clear = 0x0001;

	// Wifi_Init֮��ģ�鴦��ATָ��ģʽ,����ֱ�ӷ���ָ��
	ret = Wifi_SetWorkMode(STAMODE);						// ���ô���Wifiģ�鹤����STAģʽ
	ret = Wifi_SetSSID(ssid);								// ���ô���Wifiģ�����ӵ��ȵ������
	ret = Wifi_SetKey(WPA2KEY, key);						// ���ô���Wifiģ�������ȵ�ʱʹ�õ���Կ
	ret = Wifi_SetIP(0, ip, "255.255.255.0", serverIP);
															// ���ô���Wifiģ���IP��ַ
	ret = Wifi_ConfigureSocket(0, 1, port, serverIP);		// ���ô���Wifiģ�����ӵ�TCP��������ַ
	ret = Wifi_EnableSocket(1);								// ʹ��TCP����
	ret = Wifi_Reset();										// ����ģ��,ʹ����������Ч
	SystemTickWait(3000);									// �ȴ�ģ���������,��Լ3����

	while(1)
	{		
		sprintf(valueString,"Shake:%02d\n",ShakeSensorFlag);	//���𶯴��������ݱ���ַ���	
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

