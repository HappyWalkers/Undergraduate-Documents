#include <QCoreApplication>
#include <stdio.h>
#include <string.h>
#include "libbt4comm.h"
#include "libsmscb.h"
#include "node_config.h"
#include <stdlib.h>


void callback(const char *phone, const char *date_time, const char *smsContent, void *arg)
{
	const char *p=NULL;

	char sendMessage[100]="";
	char *data = NULL;
	printf("====test content:%s\n", smsContent);  //test content:control 1:1:1:1
	if(!strncasecmp(smsContent, "ble illum", 9))
	{
		bt4comm_getNodeData_byType("127.0.0.1", DevILLum, 0xFF, &data);
		if( data != NULL){
			printf("====test illum data:%d\n", *((unsigned short *)data));
			unsigned short temp = *((unsigned short *)data);
			float v = float(temp) / 100;

			//QString dataStr = QString::number(v);

			sprintf(sendMessage, "光照:%.02f", v );
		}
		else
			sprintf(sendMessage, "光照:" );
		if(data != NULL)
		{
			free(data);
		}
	}
	else if(!strncasecmp(smsContent, "ble hall", 8))
	{


		bt4comm_getNodeData_byType("127.0.0.1", DevHall, 0xFF, &data);
		if( data != NULL){
			printf("====test hall data:%d\n", *((unsigned short *)data));

			sprintf(sendMessage, "霍尔:%d", *data );
		}
		else
			sprintf(sendMessage, "霍尔:" );
		if(data != NULL)
		{
			free(data);
		}
	}
	else
	{
		strcpy(sendMessage, "短信无效!");
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
