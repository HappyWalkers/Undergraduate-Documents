#include <stdio.h>
#include <libwsncomm.h>			// �������libwsncomm.hͷ�ļ�

void onNewNode(void *arg, unsigned short nwkAddr, unsigned short parAddr, unsigned char macAddr[8])
{
	// ���½ڵ��������,������ڵ�Ķ̵�ַ������ն�
	printf("A New node coming, address is %04X\n", nwkAddr);
}
void onNewFunc (void *arg, unsigned short nwkAddr, int funcNum, WSNCOMM_NODE_FUNC *funcList)
{
	// �ڵ�Ĺ��ܱ�����,����Щ�ڵ�Ĺ���������ն�
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
	// �ڵ���������,������������ն�
	int i;
	printf("The node %04X emit a new data:", nwkAddr);
	for(i = 0; i < len; i++)
		printf("%02X ", data[i] & 0xFF);
	printf("\n");
}
void onNodeGone(void *arg, unsigned short nwkAddr)
{
	// �ڵ����,�����ʾ��Ϣ���ն�
	printf("The node %04X gone!\n", nwkAddr);
}
void onServerGone(void *arg)
{
	// ����������,�����ʾ��Ϣ���ն�
	printf("The server has gone!\n");
}

int main(int argc, char *argv[])
{
	void *user = wsncomm_register("127.0.0.1",		// ���ӵ������ķ������
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
		// ��ѭ��,�������κ�����������,Zigbee���緢���仯ʱ������Ӧ�Ļص�������ִ��
		sleep(1);
	}
	return 0;
}
