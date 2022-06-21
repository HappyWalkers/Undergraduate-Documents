#include <stdio.h>
#include <string.h>
#include "libipv6comm.h"
#include "libsmscb.h"
#include "node_config.h"

#define PHONENUMBER "18611575352"       // Modify this number!!!
#define WARNING_MSG "Gas Warning!!!"

void onNewData(void *arg, unsigned short nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
	// 接收到瓦斯传感器的数据,判断是否需要发送报警短信

	printf("get new data, funcCode:%x, data:%x\n", funcCode, data[0]);
	if(funcCode == DevGas)
    {
        if(data[0] != 0){
            SMSCB_SendSMS("127.0.0.1", PHONENUMBER, WARNING_MSG);
		}
    }
}

int main()
{
	SMSCB_SendSMS("127.0.0.1", PHONENUMBER, WARNING_MSG);
	printf("sended a message!\n");
	void *user = ipv6comm_register("127.0.0.1",	// 连接到本机的服务程序
							NULL,   			// 注册发现新节点的回调函数
							NULL,   			// 注册发现新功能的回调函数
							onNewData,			// 注册新数据的回调函数
							NULL,   			// 注册节点掉线的回调函数
							NULL,       		// 注册服务程序断线的回调函数
							NULL);				// 回调函数参数
	if(user == NULL)
	{
		printf("Register failed!\n");
		return 1;
	}
	// 主循环不需要做任何事情
	while(1)
	{
	    sleep(1);
	}
	return 0;
}
