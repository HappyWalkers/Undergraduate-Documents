//======================================================
// 文件名称:	wifi.c
// 功能描述：   WIFI模块 GS1011MxP-EVB_rev1.2 驱动程序 
// 维护记录：  	
//				
//======================================================
#include "wifi.h"
#include "SystemTime.h"
#include <stdio.h>
#include <string.h>
#define WIFI_RECV_QUEUE_COUNT	4
#define WIFI_RECV_LINE_LENGTH	200

static int isRawMode = 1;
static struct {
	union {
		unsigned char payload[WIFI_RECV_QUEUE_COUNT][WIFI_RECV_LINE_LENGTH];
		unsigned char raw[1];
	};
	union {
		struct {
			int rdIdx, wrIdx;
			int wrPnter;
		} atOp;
		struct {
			int rawRdIdx, rawWrIdx;
		} rawOp;
	};
} wifiAtRecvQueue;
#define wifiRcvPayload				wifiAtRecvQueue.payload
#define wifiRcvRdIdx				wifiAtRecvQueue.atOp.rdIdx
#define wifiRcvWrIdx				wifiAtRecvQueue.atOp.wrIdx
#define wifiRcvWrPnter				wifiAtRecvQueue.atOp.wrPnter
#define wifiRcvRawData				wifiAtRecvQueue.raw
#define wifiRcvRawRdIdx				wifiAtRecvQueue.rawOp.rawRdIdx
#define wifiRcvRawWrIdx				wifiAtRecvQueue.rawOp.rawWrIdx
#define wifiRcvRawHasPendingData()	(wifiAtRecvQueue.rawOp.rawRdIdx != wifiAtRecvQueue.rawOp.rawWrIdx)
#define wifiClearRcvQueue()			do {memset(&wifiAtRecvQueue, 0, sizeof(wifiAtRecvQueue)); } while(0)
#define wifiSwitchBuffer(m)			do {isRawMode=m;wifiClearRcvQueue();}while(0)
#define wifiSwitchAtBuffer()		wifiSwitchBuffer(0)
#define wifiSwitchRawBuffer()		wifiSwitchBuffer(1)

static void Wifi_ProcessRxByte(unsigned char ch)
{
	if(isRawMode != 0)
	{
		wifiRcvRawData[wifiRcvRawWrIdx++] = ch;
		if(wifiRcvRawWrIdx >= sizeof(wifiRcvPayload))
			wifiRcvRawWrIdx = 0;
	}
	else
	{
		int done = 0;
		if(ch == '\n')
		{
			//if(wifiRcvWrPnter != 0)
			{
				wifiRcvPayload[wifiRcvWrIdx][wifiRcvWrPnter] = '\0';
				if((wifiRcvWrPnter - 1 >= 0)
					&& (wifiRcvPayload[wifiRcvWrIdx][wifiRcvWrPnter - 1] == '\r'))
					wifiRcvPayload[wifiRcvWrIdx][wifiRcvWrPnter - 1] = '\0';
				done = 1;
			}
		}
		else if(wifiRcvWrPnter < (WIFI_RECV_LINE_LENGTH - 1))
			wifiRcvPayload[wifiRcvWrIdx][wifiRcvWrPnter++] = ch;
		if(done)
		{
			wifiRcvWrPnter = 0;
			wifiRcvWrIdx++;
			if(wifiRcvWrIdx >= WIFI_RECV_QUEUE_COUNT)
				wifiRcvWrIdx = 0;
			if(wifiRcvRdIdx == wifiRcvWrIdx)
			{
				wifiRcvRdIdx++;
				if(wifiRcvRdIdx >= WIFI_RECV_QUEUE_COUNT)
					wifiRcvRdIdx = 0;
			}
		}
	}
}
static unsigned char *Wifi_GetRecvBuffer(void)
{
	unsigned char *ret = NULL;
	if(isRawMode != 0)
		return NULL;
	if(wifiRcvWrIdx != wifiRcvRdIdx)
	{
		ret = wifiRcvPayload[wifiRcvRdIdx++];
		if(wifiRcvRdIdx >= WIFI_RECV_QUEUE_COUNT)
			wifiRcvRdIdx = 0;
	}
	return ret;
}
unsigned int Wifi_GetRecvRawByte(void)
{
	unsigned int ret = 0xFFFF;
	if((isRawMode != 0) && wifiRcvRawHasPendingData())
	{
		ret = wifiRcvRawData[wifiRcvRawRdIdx++];
	}
	return ret;
}

static int Wifi_SendCommandEx(const char *cmd, unsigned int timeout, int (*line_processer)(unsigned char *, void *arg), void *arg)
{
	int ret = 0;
	WaitInfo info;
    UART_Send_String(cmd);
    SystemTickWaitAsync(&info, timeout);				//等待接受数据完成
    while(SystemTickWaitFinished(&info) != 1)
    {
    	unsigned char *resp = Wifi_GetRecvBuffer();
    	if(resp != NULL)
    	{
    		if(*resp == '\0') break;
    		if(line_processer != NULL)
    			ret = (*line_processer)(resp, arg);
    		if(ret == 1)
    			break;
    	}
    }
    SystemTickClearWait(&info);
    return ret;
}

static int Wifi_SendCommandCB(unsigned char *line, void *arg)
{
	int *res = (int *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(*line == '\0')	return 1;
	if(strncasecmp(line, "+ok", 3) == 0)
		*res = 1;
	return 0;
}
static int Wifi_SendCommand(const char *cmd, unsigned int timeout)
{
	int res = 0;
	Wifi_SendCommandEx(cmd, timeout, Wifi_SendCommandCB, &res);
	return res;
}

static int Wifi_CheckRawMode(void)
{
	int ret = 0;
	WaitInfo info;
	wifiSwitchRawBuffer();
	UART_Send_String("+++");
    SystemTickWaitAsync(&info, 400);				//等待接受数据完成
    while(SystemTickWaitFinished(&info) != 1)
    {
    	unsigned int ch = Wifi_GetRecvRawByte();
    	if(ch == 'a')
    	{
    		ret = 1;
    		break;
    	}
    }
    SystemTickClearWait(&info);
    wifiSwitchBuffer(ret);
    return ret;
}

int Wifi_GotoAtMode(void)
{
	int ret = 0;
	if(Wifi_CheckRawMode() == 1)
	{
		wifiSwitchAtBuffer();
		ret = Wifi_SendCommand("a", 400);
		ret = Wifi_SendCommand("AT+\r", 400);
	}
	else
	{
		ret = Wifi_SendCommand("\r", 400);
		ret = 1;
	}
    return ret;
}

int Wifi_GotoRawMode(void)
{
	int ret = 0;
	if(Wifi_CheckRawMode() == 1)
	{
		ret = 1;
		UART_Send_String("+");
	}
	else
	{
		Wifi_SendCommand("\r", 500);
		ret = Wifi_SendCommand("AT+ENTM\r", 500);
	}
	return ret;
}

/*****************************************************************
//【API 格式】：void Wifi_BasicInit(void)
//【功能说明】：初始化必要的资源
//【参    数】：无
//【返 回 值】：无
*****************************************************************/
int Wifi_BasicInit(void)
{
	memset(&wifiAtRecvQueue, 0, sizeof(wifiAtRecvQueue));
	UART_Init(Wifi_ProcessRxByte);
	UART_BaudSet(BaudRate115200);
	return 0;
}

/*****************************************************************
//【API 格式】：void Wifi_Init(void)
//【功能说明】：初始化
//【参    数】：无
//【返 回 值】：无
*****************************************************************/
int Wifi_Init(void)
{
	int ret = 0;
	Wifi_BasicInit();
	SystemTickWait(2000);
	do {
		ret = Wifi_GotoAtMode();
		ret = Wifi_Check();
		//Wifi_Reset();
		//SystemTickWait(3000);
		//ret = Wifi_GotoAtMode();
	} while(0);
	__asm("nop");
	__asm("nop");
	return ret;
}

int Wifi_EnterAtMode(void)
{
	return Wifi_GotoAtMode();
}

int Wifi_EnterRawMode(void)
{
	return Wifi_GotoRawMode();
}

/*****************************************************************
//【API 格式】：int Wifi_Check(void)
//【功能说明】：联机指令，检查WIFI模块是否连接正常
//【参    数】：无
//【返 回 值】：成功返回1，失败返回0
*****************************************************************/
int Wifi_Check(void)
{
	int i = AT_RETRY;
	int ret = 0;
 	//测试10次，在某一次成功就退出
	while(i-- && ((ret = Wifi_SendCommand("AT+\r", 500)) != 1));
	return ret;
}
/*****************************************************************
//【API 格式】：int Wifi_Reset(void)
//【功能说明】：恢复出厂设置
//【参    数】：无
//【返 回 值】：成功返回1，失败返回0
*****************************************************************/
int Wifi_Reset(void)
{
	int i = AT_RETRY;
	int ret = 0;
	while(i-- && ((ret = Wifi_SendCommand("AT+Z\r", 500)) != 1));
	return ret;
}

int Wifi_SetWorkMode(unsigned int mode)
{
	static const char *modes[] = { "AP", "STA", "APSTA" };
	char cmd[20];
	if(mode >= sizeof(modes) / sizeof(modes[0])) mode = STAMODE;
	sprintf(cmd, "AT+WMODE=%s\r", modes[mode]);
	return Wifi_SendCommand(cmd, 300);
}

static int Wifi_GetCurrentSSIDCB(unsigned char *line, void *arg)
{
	char *out = (char *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(strncasecmp(line, "+ok=", 4) == 0)
		strcpy(out, line + 4);
	return 0;
}

int Wifi_GetSSID(char *out)
{
	*out = '\0';
	Wifi_SendCommandEx("AT+WSSSID\r", 200, Wifi_GetCurrentSSIDCB, out);
	return (out[0] != '\0');
}

int Wifi_SetSSID(const char *ssid)
{
	char cmd[12+50];
	sprintf(cmd, "AT+WSSSID=%s\r", ssid);
	return Wifi_SendCommand(cmd, 300);
}

int Wifi_SetKey(unsigned int type, const char *key)
{
	const char *auth = "OPEN";
	const char *encry = "NONE";
	char cmd[13 + 100];
	int keylen = (key == NULL) ? 0 : strlen(key);
	if((type != NONKEY) && (key != NULL))
	{
		switch(type)
		{
		case WEPKEY:
			auth = "SHARED";
			if((keylen == 5) || (keylen == 13))
				encry = "WEP-A";
			else if((keylen == 10) || (keylen == 26))
				encry = "WEP-H";
			else return -1;
			break;
		case WPAKEY:
			auth = "WPAPSK";
			encry = "AES";
			break;
		case WPA2KEY:
			auth = "WPA2PSK";
			encry = "AES";
			break;
		}
	}
	else
		key = "";
	sprintf(cmd, "AT+WSKEY=%s,%s,%s\r", auth, encry, key);
	return Wifi_SendCommand(cmd, 300);
}

int Wifi_SetIP(int dhcp, const char *ip, const char *mask, const char *gateway)
{
	char cmd[100];
	if(ip == NULL)
		ip = "0.0.0.0";
	if(mask == NULL)
		mask = "255.255.255.0";
	if(gateway == NULL)
		gateway = "0.0.0.0";
	if(dhcp != 0)
		sprintf(cmd, "AT+WANN=dhcp\r");
	else
		sprintf(cmd, "AT+WANN=static,%s,%s,%s\r", ip, mask, gateway);
	return Wifi_SendCommand(cmd, 300);
}

struct getip_info_t {
	int *dhcp;
	char *addr[3];
};
static int Wifi_GetIPCB(unsigned char *line, void *arg)
{
	struct getip_info_t *info = (struct getip_info_t *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(strncasecmp(line, "+ok=", 4) == 0)
	{
		char *p;
		if(strncmp(line + 4, "DHCP", 4) == 0)
			*(info->dhcp) = 1;
		else
			*(info->dhcp) = 0;
		p = strchr(line + 4, ',');
		if(p != NULL)
		{
			int status = 0;
			p++;
			while((p != NULL) && (*p != '\0') && (status < 3))
			{
				char *str = p;
				p = strchr(str, ',');
				if(p == NULL)
					strcpy(info->addr[status], str);
				else
				{
					strncpy(info->addr[status], str, p - str);
					p++;
				}
				status++;
			}
		}
	}
	return 0;
}

int Wifi_GetIP(int *dhcp, char *ip, char *mask, char *gateway)
{
	struct getip_info_t info = { dhcp, { ip, mask, gateway } };
	return Wifi_SendCommandEx("AT+WANN\r", 300, Wifi_GetIPCB, (void *)&info);
}

int Wifi_ConfigureSocket(int protocol, int cs, unsigned short port, const char *ip)
{
	char cmd[100];
	sprintf(cmd, "AT+NETP=%s,%s,%d,%s\r"
			, protocol ? "UDP" : "TCP"
			, cs ? "CLIENT" : "SERVER"
			, port, ip);
	return Wifi_SendCommand(cmd, 1000);
}

int Wifi_ConfigureSocketB(int protocol, int cs, unsigned short port, const char *ip)
{
	char cmd[100];
	sprintf(cmd, "AT+SOCKB=%s,%s,%d,%s\r"
			, protocol ? "UDP" : "TCP"
			, cs ? "CLIENT" : "SERVER"
			, port, ip);
	return Wifi_SendCommand(cmd, 300);
}

int Wifi_EnableSocket(int on)
{
	if(on)
		return Wifi_SendCommand("AT+TCPDIS=on\r", 300);
	else
		return Wifi_SendCommand("AT+TCPDIS=off\r", 300);
}

int Wifi_EnableSocketB(int on)
{
	if(on)
		return Wifi_SendCommand("AT+TCPDISB=on\r", 300);
	else
		return Wifi_SendCommand("AT+TCPDISB=off\r", 300);
}

static int Wifi_CheckWLinkCB(unsigned char *line, void *arg)
{
	char *essid = (char *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(strncasecmp(line, "+ok=", 4) == 0)
	{
		if(strncasecmp(&line[4], "Disconnected", 12) != 0)
		{
			if(essid != NULL)
				strcpy(essid, &line[4]);
		}
	}
	return 0;
}

int Wifi_CheckWLink(char *essid)
{
	if(essid != NULL)	essid[0] = '\0';
	return Wifi_SendCommandEx("AT+WSLK\r", 5000, Wifi_CheckWLinkCB, (void *)essid);
}

static int Wifi_CheckLinkCB(unsigned char *line, void *arg)
{
	int *isLink = (int *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(strncasecmp(line, "+ok=", 4) == 0)
	{
		if(line[5] == 'n')
			*isLink = 1;
		else
			*isLink = 0;
	}
	return 0;
}

int Wifi_CheckLink()
{
	int isLink = -1;
	Wifi_SendCommandEx("AT+TCPLK\r", 5000, Wifi_CheckLinkCB, (void *)&isLink);
	return isLink;
}
