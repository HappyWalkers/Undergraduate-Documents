#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libbt4comm.h>
#define MAIN_NODE_CONFIG
#include <node_config.h>

// input:	[get]
//			type=%d&id=%d&data=%s
// output: 	json data or jsonp proc
static int _str2bin(void *outBuf, const char *inBuf)
{
    int len = 0;
    unsigned char *o = (unsigned char *)outBuf;
    while(*inBuf)
    {
        char t[3] = "";
        memcpy(t, inBuf, 2);
        if(t[1] == 0)
        {
            inBuf += 1;
            char *stopAt = NULL;
            unsigned char c = strtoul(t, &stopAt, 16);
            if(stopAt != &t[1])
                break;
            *o++ = c;
            len++;
            break;
        }
        inBuf += 2;
        char *stopAt = NULL;
        unsigned char c = strtoul(t, &stopAt, 16);
        if(stopAt != &t[2])
            break;
        *o++ = c;
        len++;
    }
    return len;
}
int main(int argc, char *argv[])
{
	const char *query_string = getenv("QUERY_STRING");
	char *callback = NULL;
	unsigned char type = 0xFF;
	unsigned char id = 0xFF;
	char *data = NULL;
	int dataLen = 0;
	if((query_string != NULL) && (strlen(query_string) > 0))
	{
	    char *bk = strdup(query_string);
	    char *cb = strstr(bk, "callback=");
	    char *tp = strstr(bk, "type=");
	    char *d = strstr(bk, "id=");
	    char *dt = strstr(bk, "data=");
	    if(cb != NULL)
	    {
	        char *value = strchr(cb, '=');
	        if(value != NULL)
	        {
	            value++;
	            char *stop = strchr(value, '&');
	            if(stop != NULL)
	                *stop = 0;
	            if(strlen(value) > 0)
    	            callback = strdup(value);
	        }
	    }
	    if(tp != NULL)
        {
            char *value = strchr(tp, '=');
            if(value != NULL)
            {
                value++;
                char *stop = strchr(value, '&');
                if(stop != NULL)
                    *stop = 0;
                type = strtoul(value, &stop, 10);
                if(stop == value)
                    type = 0xFF;
            }
        }
        if(d != NULL)
        {
            char *value = strchr(d, '=');
            if(value != NULL)
            {
                value++;
                char *stop = strchr(value, '&');
                if(stop != NULL)
                    *stop = 0;
                id = strtoul(value, &stop, 10);
                if(stop == value)
                    id = 0xFF;
            }
        }
        if(dt != NULL)
        {
            char *value = strchr(dt, '=');
            if(value != NULL)
            {
                value++;
                char *stop = strchr(value, '&');
                if(stop != NULL)
                    *stop = 0;
                data = (char *)malloc((strlen(value) + 1) >> 1);
                dataLen = _str2bin(data, value);
                if(dataLen <= 0)
                {
                    free(data);
                    data = NULL;
                }
            }
        }
	    free(bk);
	}

	printf("%s\r\n\r\n", "Content-type: application/json");

	if(callback != NULL)
	    printf("%s(", callback);
	int result = 1;
	char *errString = "";
	if(type == 0xFF)
	{
	    result = 0;
	    errString = "无效的节点地址";
	}
	else if((dataLen <= 0) || (data == NULL))
	{
	    result = 0;
	    errString = "无效的数据";
	}
	else
	{
        bt4comm_sendNode_byType("127.0.0.1", type, id, data, dataLen);
        result = 1;
        errString = "完成";
	}

    printf("{\"result\":%s,\"errString\":\"%s\"}", result ? "true": "false", errString);
    if(callback != NULL)
        printf(")");
    printf("\n");
	printf("\n");

	if(callback != NULL)
	    free(callback);
	if(data != NULL)
	    free(data);
	return 0;
}
