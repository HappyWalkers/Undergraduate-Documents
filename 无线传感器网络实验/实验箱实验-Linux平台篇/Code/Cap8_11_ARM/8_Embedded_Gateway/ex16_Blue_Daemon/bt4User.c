#include <stdio.h>
#include <libbt4comm.h>			// �������libbt4comm.hͷ�ļ�

void onNewNode(void *arg, unsigned char *nwkAddr)
{
	int j;

	// ���½ڵ��������,������ڵ�Ķ̵�ַ������ն�
	printf("A New node coming, address is:");
	for(j = 0; j<BT_ADDR_LEN; j++)
		printf("%x", nwkAddr[j]);
}

void onNewFunc (void *arg, unsigned char *nwkAddr, int funcNum, BT4COMM_NODE_FUNC *funcList)
{
	// �ڵ�Ĺ��ܱ�����,����Щ�ڵ�Ĺ���������ն�
	int i, j;

	printf("The node:");
	for(j = 0; j<BT_ADDR_LEN; j++)
		printf("%x", nwkAddr[j]);
	printf(" has %d functions:\n", funcNum);
	for(i = 0; i < funcNum; i++)
	{
		printf("Function %d: funcCode - %02X, funcID - %02X, refresh cycle - %d\n",
				i, funcList[i].funcCode, funcList[i].funcID, funcList[i].rCycle);
	}
}

void onNewData(void *arg, unsigned char *nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
	// �ڵ���������,������������ն�
	int i, j;
	printf("The node:");
	for(j = 0; j<BT_ADDR_LEN; j++)
		printf("%x", nwkAddr[j]);
	printf(" emit a new data:");
	for(i = 0; i < len; i++)
		printf("%02X ", data[i] & 0xFF);
	printf("\n");
}

void onNodeGone(void *arg, unsigned char *nwkAddr)
{
	int j;
	// �ڵ����,�����ʾ��Ϣ���ն�
	printf("The node:");
	for(j = 0; j<BT_ADDR_LEN; j++)
		printf("%x", nwkAddr[j]);
	printf(" gone!\n");
}

void onServerGone(void *arg)
{
	// ����������,�����ʾ��Ϣ���ն�
	printf("The server has gone!\n");
}

int main(int argc, char *argv[])
{
	void *user = bt4comm_register("127.0.0.1",		// ���ӵ������ķ������
							onNewNode,			// ע�ᷢ���½ڵ�Ļص�����
							onNewFunc,			// ע�ᷢ���¹��ܵĻص�����
							onNewData,			// ע�������ݵĻص�����
							onNodeGone,			// ע��ڵ���ߵĻص�����
							onServerGone,		// ע����������ߵĻص�����
							NULL);				// �ص���������
	// �ж�ע���Ƿ�ɹ�
	if(user == NULL)
	{
		printf("Register failed!\n");
		return 1;
	}
	while(1)
	{
		// ��ѭ��,�������κ�����������,�������緢���仯ʱ������Ӧ�Ļص�������ִ��
		sleep(1);
	}
	return 0;
}
