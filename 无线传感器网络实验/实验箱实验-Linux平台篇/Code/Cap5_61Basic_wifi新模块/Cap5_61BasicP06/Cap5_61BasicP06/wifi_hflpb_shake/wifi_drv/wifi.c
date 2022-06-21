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

static int isRawMode = 0;
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
				if((wifiRcvWrPnter - 1 > 0)
					&& (wifiRcvPayload[wifiRcvWrIdx][wifiRcvWrPnter - 1] == '\r'))
					{
						wifiRcvPayload[wifiRcvWrIdx][wifiRcvWrPnter - 1] = '\0';
						done = 1;
					}
					else wifiRcvWrPnter=0;
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

unsigned char Wifi_RecvFlag(unsigned char cmd)
{
	static int i;
//	SystemTickWait(200);
	switch(cmd)
	{
		case CWJAP:
				for(i=0;i<WIFI_RECV_QUEUE_COUNT;i++)
				{
					if(strncasecmp(wifiRcvPayload[i], "WIFI GOT IP", 11) == 0)
						return 0;
					else if(strncasecmp(wifiRcvPayload[i], "FAIL", 4) == 0)
					{
						wifiRcvPayload[i][0]='A';
						return 2;
					}
				}
			break;
			
		case CIPSTART:
				for(i=0;i<WIFI_RECV_QUEUE_COUNT;i++)
				{
					if(strncasecmp(wifiRcvPayload[i], "1,CONNECT", 9) == 0)
						return 0;
				}
			break;
		case DISCONNECT:
				for(i=0;i<WIFI_RECV_QUEUE_COUNT;i++)
				{
					if(strncasecmp(wifiRcvPayload[i], "WIFI DISCONNECT", 15) == 0)
						return 0;
				}
			break;
			

	default :  break;
	
	}
	return 1;
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


static int Wifi_SendCommandEx(const char *cmd, unsigned int timeout, int (*line_processer)(unsigned char *, void *arg), void *arg)
{
	int ret = 0;
	WaitInfo info;
	if(wifiRcvRdIdx != wifiRcvWrIdx)
	wifiRcvRdIdx = wifiRcvWrIdx;
    UART_Send_String(cmd);
    SystemTickWait(500);
    SystemTickWaitAsync(&info, timeout);				//等待接受数据完成
    while(SystemTickWaitFinished(&info) != 1)
    {
    	unsigned char *resp = Wifi_GetRecvBuffer();//wifiRcvPayload[i];
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
	if(strncasecmp(line, "OK", 2) == 0)
		*res = 1;
	return 0;
}
static int Wifi_SendCommand(const char *cmd, unsigned int timeout)
{
	int res = 0;
	Wifi_SendCommandEx(cmd, timeout, Wifi_SendCommandCB, &res);
	return res;
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
//	int ret = 0;
	Wifi_BasicInit();
	SystemTickWait(500);
	UART_Send("ATE0\r\n",6);
	SystemTickWait(200);
	do {
	//	ret = Wifi_Check();
	//SystemTickWait(3000);

	} while(0);
	__asm("nop");
	__asm("nop");
	return 1;
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
	while(i-- && ((ret = Wifi_SendCommand("AT\r\n", 500)) != 1));
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
	while(i-- && ((ret = Wifi_SendCommand("AT+RST\r\n", 500)) != 1));
	return ret;
}

int Wifi_SetWorkMode(unsigned int mode)
{
	static const char *modes[] = { "1", "2", "3" };
	char cmd[20];
	if(mode >= sizeof(modes) / sizeof(modes[0])) mode = STAMODE;
	sprintf(cmd, "AT+CWMODE=%s\r\n", modes[mode]);
	return Wifi_SendCommand(cmd, 300);
}

int Wifi_SetMux(unsigned int mode)
{
	static const char *modes[] = { "0", "1"};
	char cmd[20],len;
	if(mode >= sizeof(modes) / sizeof(modes[0])) mode = STAMODE;
	len=sprintf(cmd, "AT+CIPMUX=%s\r\n", modes[mode]);
	return Wifi_SendCommand(cmd, 300);
}
static int Wifi_GetCurrentSSIDCB(unsigned char *line, void *arg)
{
	char *out = (char *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(strncasecmp(line, "+CWJAP:", 7) == 0)
	{
		memcpy(out,line+8,11);
//		strcpy(out, line + 8);
	}
	return 0;
}

int Wifi_GetSSID(char *out)
{
	*out = '\0';
	Wifi_SendCommandEx("AT+CWJAP?\r\n", 1000, Wifi_GetCurrentSSIDCB, out);
	return (out[0] != '\0');
}

//int Wifi_SetSSID(const char *ssid)
//{
//	char cmd[12+50];
//	sprintf(cmd, "AT+WSSSID=%s\r", ssid);
//	return Wifi_SendCommand(cmd, 300);
//}
int Wifi_SetSSID(const char *ssid,const char *key)
{
	char cmd[12+50],len;
	len=sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid,key);
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
		sprintf(cmd, "AT+CIPSTA=dhcp\r");
	else
		sprintf(cmd, "AT+CIPSTA=\"%s\"\r\n", ip);
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
	if(strncasecmp(line, "+CIFSR", 6) == 0)
	{
		char *p;
		if(strncmp(line + 4, "DHCP", 4) == 0)
			*(info->dhcp) = 1;
		else
			*(info->dhcp) = 0;
		p = strchr(line + 4, '\"');
		if(p != NULL)
		{
			int status = 0;
			p++;
			while((p != NULL) && (*p != '\0') && (status < 3))
			{
				char *str = p;
				p = strchr(str, '\"');
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
	return Wifi_SendCommandEx("AT+CIFSR\r\n", 300, Wifi_GetIPCB, (void *)&info);
}

int Wifi_ConfigureSocket(int protocol, int cs, unsigned short port, const char *ip)
{
	char cmd[100],len;
	len=sprintf(cmd, "AT+CIPSTART=%s,\"%s\",\"%s\",%d\r\n"
	    	, cs ? "1" : "0"
			, protocol ? "UDP" : "TCP"	
			, ip,port );
	return Wifi_SendCommand(cmd, 1000);
}


static int Wifi_CheckLinkCB(unsigned char *line, void *arg)
{
	int *isLink = (int *)arg;
	while((*line <= ' ') && (*line != '\0')) line++;
	if(strncasecmp(line, "+CWJAP:", 7) == 0)
	{
		if(line[10] == 'n')
			*isLink = 1;
		else
			*isLink = 0;
	}
	return 0;
}

int Wifi_CheckLink()
{
	int isLink = -1;
	Wifi_SendCommandEx("AT+CWJAP?\r\n", 3000, Wifi_CheckLinkCB, (void *)&isLink);
	return isLink;
}
