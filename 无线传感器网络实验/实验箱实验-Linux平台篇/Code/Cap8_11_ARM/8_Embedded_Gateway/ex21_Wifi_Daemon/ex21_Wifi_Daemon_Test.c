#include<stdio.h>
#include<libwificomm.h>

// �����½ڵ�����ʱ�ú����Զ�ִ��
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

// ���ڵ���������ʱ�ú����Զ�ִ��
void onNewData(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len)
{
	int i;
	printf("The node %s[%d] emit a new data:", nodeIP, endPoint);
	for(i = 0; i < len; i++)
		printf("%02X ", data[i] & 0xFF);
	printf("\n");
}

// ���ڵ����ʱ�ú����Զ�ִ��
void onNodeGone(void *arg, const char *nodeIP)
{
	printf("The node %s gone!\n", nodeIP);
}

// ��������崻�ʱ�ú����Զ�ִ��
void onServerGone(void *arg)
{
	printf("The server has gone!\n");
}

int main()
{
	void *wifiCommUser;		// ����������wifi������ע���õ��ľ��
	wifiCommUser = wificomm_register("127.0.0.1",		// ����wifi�������ĵ�ַ
									onNewNode,			// �������½ڵ�����ʱ�Ļص�����
									onNewData,			// ���ýڵ���������ʱ�Ļص�����
									onNodeGone,			// ���ýڵ����ʱ�Ļص�����
									onServerGone,		// ����wifi������崻�ʱ�Ļص�����
									NULL);
	// �ж�ע���Ƿ�ɹ�
	if(wifiCommUser == NULL)
	{
		printf("Register failed!\n");
		return 1;
	}
	// ��ѭ������Ҫ���κ�����,˯�ߵȴ�wifi���������ûص�����
	while(1)
	{
		sleep(1);
	}
	return 0;	
}
