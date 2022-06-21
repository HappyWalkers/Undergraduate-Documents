//======================================================
// 文件名称:	wifi.h
// 功能描述：   WIFI模块 GS1011MxP-EVB_rev1.2 驱动头文件
// 维护记录：  	
//				
//======================================================
#ifndef _WIFI_H_
#define _WIFI_H_

#include	"UART.h"
//#include	"../sound/Sound.h"

#define  AT_RETRY  5     		// 发送AT指令的尝试次数
#define  NULL    0

#define UART_BUFFER_CNT 200

int Wifi_BasicInit(void);
int Wifi_Init(void);
int Wifi_GotoAtMode(void);
int Wifi_GotoRawMode(void);
unsigned int Wifi_GetRecvRawByte(void);

int Wifi_Check(void);
int Wifi_Reset(void);
enum { APMODE = 0, STAMODE, APSTAMODE };
int Wifi_SetWorkMode(unsigned int mode);
int Wifi_GetSSID(char *out);
int Wifi_SetSSID(const char *ssid);
enum { NONKEY, WEPKEY, WPAKEY, WPA2KEY };
int Wifi_SetKey(unsigned int type, const char *key);
int Wifi_SetIP(int dhcp, const char *ip, const char *mask, const char *gateway);
int Wifi_GetIP(int *dhcp, char *ip, char *mask, char *gateway);
// protocol - 0 for TCP and 1 for UDP
// cs - 0 for SERVER and 1 for CLIENT
int Wifi_ConfigureSocket(int protocol, int cs, unsigned short port, const char *ip);
int Wifi_ConfigureSocketB(int protocol, int cs, unsigned short port, const char *ip);
int Wifi_EnableSocket(int on);
int Wifi_EnableSocketB(int on);
int Wifi_CheckLink();

#endif /* _WIFI_H_ */
