#include <QCoreApplication>
#include <stdio.h>
#include <string.h>
#include "libwificomm.h"
#include "libsmscb.h"
#include "node_config.h"
#include <stdlib.h>


void callback(const char *phone, const char *date_time, const char *smsContent, void *arg)
{
	const char *p=NULL;

	char sendMessage[100]="";
	char *data = NULL;
	printf("====test content:%s\n", smsContent);  //test content:control 1:1:1:1
	if(!strncasecmp(smsContent, "wifi temp", 9))
	{

		float value = 0.0;
		char *data = NULL;
		wificomm_getNodeData_byType("127.0.0.1", DevTemp, 0xFF, &data);
		if(data != NULL)
		{
			unsigned short sd = 0;
			memcpy(&sd, data, 2);
			value = ((float)sd) / 100;
			free(data);
		}
		sprintf(sendMessage, "温度：%.2f", value);
	}
	else if(!strncasecmp(smsContent, "wifi humi", 9))
	{

		float value = 0.0;
		char *data = NULL;
		wificomm_getNodeData_byType("127.0.0.1", DevHumm, 0xFF, &data);
		if(data != NULL)
		{
			unsigned short sd = 0;
			memcpy(&sd, data, 2);
			value = ((float)sd) / 100;
			free(data);
		}
		sprintf(sendMessage, "湿度：%.2f", value);
	}
	else if(!strncasecmp(smsContent, "wifi shake", 10))
	{

		char *data = NULL;
		wificomm_getNodeData_byType("127.0.0.1", DevShake, 0xFF, &data);
		if( data != NULL){
			printf("====test shake data:%d\n", *((unsigned short *)data));

			sprintf(sendMessage, "振动：%d", *data );
		}
		else
			sprintf(sendMessage, "振动：" );
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
