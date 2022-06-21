#include<stdio.h>
#include<libwificomm.h>

// 当有新节点上线时该函数自动执行
void onNewNode(void *arg, const char *nodeIP, int funcNum, WIFI_NODE_FUNC *funcList)
{
	int i;
	printf("A New node coming, address is %s\n", nodeIP);
	printf("This node %has %d functions:\n", funcNum);
	for(i = 0; i < funcNum; i++)
	{
		printf("Function %d: funcCode - %02X, funcID - %02X, refresh cycle - %d\n",
				i, funcList[i].funcCode, funcList[i].funcID, funcList[i].rCycle);
	}
}

// 当节点有新数据时该函数自动执行
void onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len)
{
	int i;
	printf("The node %s[%d] emit a new data:", nodeIP, endPoint);
	for(i = 0; i < len; i++)
		printf("%02X ", data[i] & 0xFF);
	printf("\n");
}

// 当节点掉线时该函数自动执行
void onNodeGone(void *arg, const char *nodeIP)
{
	printf("The node %s gone!\n", nodeIP);
}

// 当服务器宕机时该函数自动执行
void onServerGone(void *arg)
{
	printf("The server has gone!\n");
}

int main()
{
	void *wifiCommUser;		// 用来保存向wifi服务器注册后得到的句柄
	wifiCommUser = wificomm_register("127.0.0.1",		// 设置wifi服务器的地址
									onNewNode,			// 设置有新节点上线时的回调函数
									onNewData,			// 设置节点有新数据时的回调函数
									onNodeGone,			// 设置节点掉线时的回调函数
									onServerGone,		// 设置wifi服务器宕机时的回调函数
									NULL);
	// 判断注册是否成功
	if(wifiCommUser == NULL)
	{
		printf("Register failed!\n");
		return 1;
	}
	// 主循环不需要做任何事情,睡眠等待wifi服务器调用回调函数
	while(1)
	{
		sleep(1);
	}
	return 0;	
}
