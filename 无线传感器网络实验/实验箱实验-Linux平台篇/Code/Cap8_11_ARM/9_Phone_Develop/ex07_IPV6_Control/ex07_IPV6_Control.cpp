#include <QCoreApplication>
#include <stdio.h>
#include <string.h>
#include "libipv6comm.h"
#include "libsmscb.h"
#include "node_config.h"
#include "QDebug"
void callback(const char *phone, const char *date_time, const char *smsContent, void *arg)
{
	const char *p = NULL;
	char sendMessageBuf[100]="";
	char state = 0;
	printf("test content:%s\n", smsContent);
	strcpy(sendMessageBuf, smsContent);
	QString messageContent = QString(sendMessageBuf);

	qDebug()<<"==message:"<<messageContent;
	memset(sendMessageBuf,0,sizeof(sendMessageBuf));
	if(!strncmp(smsContent, "control", 7))
	{
		p = strchr(smsContent + 7, ' ');
		printf("==test content:%s\n", p);

		p = strchr(smsContent, ' ');
		//p = strtok(NULL, " ");
		if(p != NULL){
			printf("test1 p:%s\n", p);
			p++;
		}
		else
			p = smsContent+7;
		printf("test2 p:%s\n", p);
		if(*p == '1')
			state|=0x08;
		if(*(p+2) == '1')
			state|=0x04;
		if(*(p+4) == '1')
			state|=0x02;
		if(*(p+6) == '1')
			state|=0x01;
		printf("test state:%x\n",state);
		//ipv6comm_sendNode_byType("127.0.0.1", DevExecuteB, 3, &state, 1);
		ipv6comm_sendNode_byType("127.0.0.1", DevExecuteB, 0xFF, &state, 1);
		strcpy(sendMessageBuf, "Set Controler OK!");
	}
	else
	{
		strcpy(sendMessageBuf, "Message Error!");
	}
	printf("test receive number:%s\n", phone);
	SMSCB_SendSMS("127.0.0.1", phone, sendMessageBuf);
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	printf("starting...\n");
	void *usr = SMSCB_RegisterSMSReceiver("127.0.0.1", callback, NULL);
	printf("started %p!\n", usr);
	
	return app.exec();
}
