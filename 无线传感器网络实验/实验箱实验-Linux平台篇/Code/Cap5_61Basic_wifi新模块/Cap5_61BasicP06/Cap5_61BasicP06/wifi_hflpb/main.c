//======================================================
//  The information contained herein is the exclusive property of
//  Sunnnorth Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNNORTH TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  �������ƣ�	new_wifi
//  ����������	WiFiģ�����ݴ���ʵ��,
//				WiFiģ����TCP�ͻ��ˣ�����Զ��TCP�����������ӳɹ��󣬷��ʹ��������ݵ�TCP������
//  �漰�Ŀ⣺	CMacro1016.lib
//  ����ļ���	main.c��
//			wifi.c�ļ�, wifi.hͷ�ļ���
//			uart.c�ļ�, uart.hͷ�ļ���
//			SHT10.c�ļ�,  SHT10.hͷ�ļ���
//			isr.c
//	Ӳ�����ӣ� SHT10  DATA��IOA7��CLK��IOA8
//			   SPCE061A���ڽ�WiFiģ��
//	ά����¼��	2011-12-16 v1.0
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

int tempre;													//  �¶�ʵ��ֵ��100��
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
	*P_INT_Mask |= (C_IRQ4_1KHz | C_IRQ5_2Hz);				//��2Hz�жϣ�������ʱ�忴�Ź�����ʱ,1KHz������ʱ
	__asm("IRQ ON");
	// ��ʼ��Wifi
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
			ret = Wifi_SetMux(1);									// ���ô���WifiģΪ������ģʽ
			SystemTickWait(100);
			RECONNECT:if(strncasecmp(essid, "sunplus", 7) == 0)
			ret = Wifi_SetSSID(essid,"12345678");								// ���ô���Wifiģ�����ӵ��ȵ�����ֺ�����
			else Wifi_SetSSID(&DEFAULT_ESSID,"12345678");
        	SystemTickWait(1000);
        	while(ret=Wifi_RecvFlag(CWJAP))
        		if(ret==2)goto RECONNECT;
        	SystemTickWait(3000);
			ret = Wifi_ConfigureSocket(0, 1, 5357, "192.168.0.1");		// ���ô���Wifiģ�����ӵ�TCP��������ַ
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
��API ��ʽ����void Temp_Humi_Collect(void)
������˵��������ȡ��ʪ�ȴ�����SHT10����
����    ������
���� �� ֵ����
��ʹ�þ�������Temp_Humi_Collect();
����    ע��:
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

