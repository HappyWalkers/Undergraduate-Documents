#include <QCoreApplication>
#include <stdio.h>
#include <string.h>
#include "libwsncomm.h"
#include "libsmscb.h"
#include "node_config.h"


void callback(const char *phone, const char *date_time, const char *smsContent, void *arg)
{
	const char *p=NULL;

	char sendMessage[100]="";
	char state = 0;
	printf("====test content:%s\n", smsContent);  //test content:control 1:1:1:1
	if(!strncmp(smsContent, "control", 7))
	{
		p = strchr(smsContent + 7, ' ');

		if( p != NULL ){
			printf("==11==test1 p:%s\n", p);
			//p = strtok(NULL, " ");

		}

		printf("==22==test1 p:%d\n", *p);
		if(*p != '1')
			p++;

		if(*p == '1')
			state|=0x08;
		if(*(p+2) == '1')
			state|=0x04;
		if(*(p+4) == '1')
			state|=0x02;
		if(*(p+6) == '1')
			state|=0x01;
		printf("test state:%x\n",state);
		wsncomm_sendNode_byType("127.0.0.1", DevExecuteB, 3, &state, 1);
		strcpy(sendMessage, "Set Controler OK!");
	}
	else{
		strcpy(sendMessage, "Message Error!");
	}
	printf("test send phone:%s; msg:%s\n", phone, sendMessage);
	SMSCB_SendSMS("127.0.0.1", phone, sendMessage);
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	printf("starting...\n");
	void *usr = SMSCB_RegisterSMSReceiver("127.0.0.1", callback, NULL);
	printf("started %p!\n", usr);
	
	return app.exec();
}
