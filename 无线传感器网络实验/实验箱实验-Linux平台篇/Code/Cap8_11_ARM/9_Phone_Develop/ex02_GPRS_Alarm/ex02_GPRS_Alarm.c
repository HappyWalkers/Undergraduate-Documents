#include <stdio.h>
#include <string.h>
#include "libwsncomm.h"
#include "libsmscb.h"
#include "node_config.h"

#define PHONENUMBER "18611575352"       // Modify this number!!!
#define WARNING_MSG_GAS "Gas Warning!!!"
#define WARNING_MSG_RAIN "Raining Warning!!!"

void onNewData(void *arg, unsigned short nwkAddr, int endPoint, int funcCode, int funcID, char *data, int len)
{
	// ���յ���˹������������,�ж��Ƿ���Ҫ���ͱ�������
	printf("onNewData ===== data:%x; funcCode=%x\n", data[0], funcCode);

	if(funcCode == DevGas)
    {
        if(data[0] != 0){
            SMSCB_SendSMS("127.0.0.1", PHONENUMBER, WARNING_MSG_GAS);
		}
    }
	else if(funcCode == DevRain)
    {
        if(data[0] != 0){
            SMSCB_SendSMS("127.0.0.1", PHONENUMBER, WARNING_MSG_RAIN);
		}
	}
}

int main()
{
	//SMSCB_SendSMS("127.0.0.1", PHONENUMBER, WARNING_MSG_GAS);
	printf("sended a message!\n");
	void *user = wsncomm_register("127.0.0.1",	// ���ӵ������ķ������
							NULL,   			// ע�ᷢ���½ڵ�Ļص�����
							NULL,   			// ע�ᷢ���¹��ܵĻص�����
							onNewData,			// ע�������ݵĻص�����
							NULL,   			// ע��ڵ���ߵĻص�����
							NULL,       		// ע����������ߵĻص�����
							NULL);				// �ص���������
	if(user == NULL)
	{
		printf("Register failed!\n");
		return 1;
	}
	// ��ѭ������Ҫ���κ�����
	while(1)
	{
	    sleep(1);
	}
	return 0;
}
