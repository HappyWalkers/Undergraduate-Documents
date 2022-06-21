#include <stdio.h>
#include <libwsncomm.h>			// 必须包含libwsncomm.h头文件

void onNewNode(void *arg, unsigned short nwkAddr, unsigned short parAddr, unsigned char macAddr[8])
{
	// 有新节点加入网络,将这个节点的短地址输出到终端
	printf("A New node coming, address is %04X\n", nwkAddr);
}
void onNewFunc (void *arg, unsigned short nwkAddr, int funcNum, WSNCOMM_NODE_FUNC *funcList)
{
	// 节点的功能被发现,将这些节点的功能输出到终端
	int i;
	printf("The node %04X has %d functions:\n", nwkAddr, funcNum);
	for(i = 0; i < funcNum; i++)
	{
		printf("Function %d: funcCode - %02X, funcID - %02X, refresh cycle - %d\n",
				i, funcList[i].funcCode, funcList[i].funcID, funcList[i].rCycle);
	}
}
void onNewData(void *arg, unsigned short nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
	// 节点有新数据,将数据输出到终端
	int i;
	printf("The node %04X emit a new data:", nwkAddr);
	for(i = 0; i < len; i++)
		printf("%02X ", data[i] & 0xFF);
	printf("\n");
}
void onNodeGone(void *arg, unsigned short nwkAddr)
{
	// 节点掉线,输出提示信息到终端
	printf("The node %04X gone!\n", nwkAddr);
}
void onServerGone(void *arg)
{
	// 服务程序断线,输出提示信息到终端
	printf("The server has gone!\n");
}

int main(int argc, char *argv[])
{
	void *user = wsncomm_register("127.0.0.1",		// 连接到本机的服务程序
							onNewNode,			// 注册发现新节点的回调函数
							onNewFunc,			// 注册发现新功能的回调函数
							onNewData,			// 注册新数据的回调函数
							onNodeGone,			// 注册节点掉线的回调函数
							onServerGone,		// 注册服务程序断线的回调函数
							NULL);				// 回调函数参数
	// 判断注册是否成功
	if(user == NULL)
	{
		printf("Register failed!\n");
		return 1;
	}
	while(1)
	{
		// 主循环,可以做任何其他的事情,Zigbee网络发生变化时会在相应的回调函数中执行
		sleep(1);
	}
	return 0;
}
