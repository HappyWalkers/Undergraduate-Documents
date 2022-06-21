//======================================================
// �ļ�����:	wifi.h
// ����������   WIFIģ�� GS1011MxP-EVB_rev1.2 ����ͷ�ļ�
// ά����¼��  	
//				
//======================================================
#ifndef _WIFI_H_
#define _WIFI_H_

#include	"UART.h"
//#include	"../sound/Sound.h"

#define  AT_RETRY  1     		// ����ATָ��ĳ��Դ���
#define  NULL    0

#define UART_BUFFER_CNT 200
#define CWJAP  0
#define CIPSTART 1
#define DISCONNECT 2

int Wifi_BasicInit(void);
int Wifi_Init(void);
int Wifi_Check(void);
int Wifi_Reset(void);
enum { STAMODE = 0, APMODE, APSTAMODE };
int Wifi_SetWorkMode(unsigned int mode);
int Wifi_SetMux(unsigned int mode);
int Wifi_GetSSID(char *out);
//int Wifi_SetSSID(const char *ssid);
int Wifi_SetSSID(const char *ssid,const char *key);
enum { NONKEY, WEPKEY, WPAKEY, WPA2KEY };
int Wifi_SetIP(int dhcp, const char *ip, const char *mask, const char *gateway);
int Wifi_GetIP(int *dhcp, char *ip, char *mask, char *gateway);
// protocol - 0 for TCP and 1 for UDP
// cs - 0 for SERVER and 1 for CLIENT
int Wifi_ConfigureSocket(int protocol, int cs, unsigned short port, const char *ip);
int Wifi_CheckLink();
unsigned char Wifi_RecvFlag(unsigned char cmd);

#endif /* _WIFI_H_ */
