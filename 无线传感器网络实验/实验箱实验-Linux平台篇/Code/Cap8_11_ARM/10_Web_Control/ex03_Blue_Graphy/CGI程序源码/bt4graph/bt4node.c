#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libbt4comm.h>
#define MAIN_NODE_CONFIG
#include <node_config.h>

char *utils_bt4addr2str(char *outStr, const unsigned char curAddr[BT_ADDR_LEN])
{
    sprintf(outStr, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
            curAddr[0], curAddr[1], curAddr[2], curAddr[3],curAddr[4], curAddr[5], curAddr[6], curAddr[7],
            curAddr[8], curAddr[9], curAddr[10], curAddr[11], curAddr[12], curAddr[13], curAddr[14], curAddr[15]);


	//printf("==utils_bt4addr2str== outStr: %s\n", outStr);	
    return outStr;
}

int utils_bt4str2nwkAddr(unsigned char nwkAddr[BT_ADDR_LEN], const char *strAddr)
{

	int i;
	for(i = 0; i < BT_ADDR_LEN/*sizeof(nwkAddr)*/; i++)
	{
		char byte[3];
		byte[0] = *strAddr++;
		byte[1] = *strAddr++;
		byte[2] = 0;
		nwkAddr[i] = strtoul(byte, NULL, 16);
		//printf("utils_bt4str2nwkAddr[%d]==: %02x\n", i, nwkAddr[i]);	
		
	}
	return (i == BT_ADDR_LEN) ? 0 : -1;

}
// input:	[get]
//			addr=%s
// output: 	json data or jsonp proc

int main(int argc, char *argv[])
{
	const char *query_string = getenv("QUERY_STRING");
	char *callback = NULL;
	//unsigned short nwkAddr = 0xFFFF;
	char *nwkAddr = NULL;
	unsigned char curnwkAddr[BT_ADDR_LEN];
	if((query_string != NULL) && (strlen(query_string) > 0))
	{
	    char *bk = strdup(query_string);
	    char *cb = strstr(bk, "callback");
	    char *ad = strstr(bk, "addr");
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
	    if(ad != NULL)
        {
            char *value = strchr(ad, '=');
            if(value != NULL)
            {
                value++;
                char *stop = strchr(value, '&');
                if(stop != NULL)
                    *stop = 0;
                //nwkAddr = strtoul(value, &stop, 16);
				nwkAddr = strdup(value);
                //if(nwkAddr == NULL)
                    //nwkAddr = 0xFFFF;
            }
        }
	    free(bk);
	}

	printf("%s\r\n\r\n", "Content-type: application/json");
	int count = 0;
	BT4COMM_NODE *saveBuf = NULL;
	if(nwkAddr == NULL)	//nwkAddr == 0xFFFF)
	{
	    count = bt4comm_getAllNode("127.0.0.1", &saveBuf);
	}
	else
	{
		memset(curnwkAddr, 0, BT_ADDR_LEN);
		utils_bt4str2nwkAddr(curnwkAddr, nwkAddr);
	    saveBuf = bt4comm_getNode_byAddr("127.0.0.1", curnwkAddr);
	    if(saveBuf != NULL)
	        count = 1;
	}

	if(callback != NULL)
	    printf("%s(", callback);
	printf("[");
	if((count > 0) && (saveBuf != NULL))
	{
		int i;
		for(i = 0; i < count; i++)
		{
			char nwkString[2*BT_ADDR_LEN+1];
		    printf("{");
		    //printf("\"nwkAddr\":\"%04X\",", saveBuf[i].nwkAddr);
			memset(nwkString, 0, sizeof(nwkString));
			utils_bt4addr2str(nwkString, saveBuf[i].nwkAddr);	
			printf("\"nwkAddr\":\"%s\",", nwkString);
			
		    //printf("\"parAddr\":\"%04X\",", saveBuf[i].parAddr);
		    //printf("\"macAddr\":\"%02X%02X%02X%02X%02X%02X%02X%02X\","
			//    , saveBuf[i].hwAddr[0], saveBuf[i].hwAddr[1], saveBuf[i].hwAddr[2], saveBuf[i].hwAddr[3]
			//    , saveBuf[i].hwAddr[4], saveBuf[i].hwAddr[5], saveBuf[i].hwAddr[6], saveBuf[i].hwAddr[7]);
			printf("\"funcList\":[");
			int j;
			for(j = 0; j < saveBuf[i].funcNum; j++)
			{
			    printf("{");
			    printf("\"typeCode\":%d,", saveBuf[i].funcInfo[j].funcCode);
			    const char *type = bt4comm_find_nodeTypeString(saveBuf[i].funcInfo[j].funcCode);
			    if(type == NULL)
			        type = "?N?";
			    printf("\"type\":\"%s\",", type);
			    printf("\"id\":%d,", saveBuf[i].funcInfo[j].funcID);
			    printf("\"cycle\":%d,", saveBuf[i].funcInfo[j].rCycle);
			    char *data = NULL;
			    {
			        char *d = NULL;
			        int len = bt4comm_getNodeData_byPoint("127.0.0.1", saveBuf[i].nwkAddr, j + 1, &d);
				//printf("get data:%x\n", d);
			        if(d != NULL)
			        {
			            switch(saveBuf[i].funcInfo[j].funcCode)
			            {
                        case DevTemp:
                        case DevHumm:
                        case DevILLum:
                        case DevIRDist:
                            {
                                unsigned short w = 0;
                                memcpy(&w, d, 2);
                                data = (char *)malloc(100);
                                sprintf(data, "%f", ((float)w) / 100);
                            }
                            break;
                        case DevGas:
                        case DevSmoke:
                        case DevFire:
                        case DevRain:
                        case DevIRPers:
                        case DevVoice:
                //            qDebug()<<"data = "<<v[0].byteData[0];
                            data = (char *)malloc(2);
                            data[0] = (!!d[0]) ? '1' : '0';
                            data[1] = 0;
                            break;
                        case DevExecuteB:
                        case DevExecuteA:
                        case DevRemoter:
                        case Dev125kReader:
                        default:
                            data = (char *)malloc((len << 1) + 4);
                            {
                                int idx;
                                char *o = data;
                                *o++ = '\"';
                                for(idx = 0; idx < len; idx++)
                                {
                                    o += sprintf(o, "%02X", d[idx] & 0xFF);
                                }
                                *o++ = '\"';
                                *o = 0;
                            }
                            break;
			            }
			            free(d);
			        }
			        else
			            data = strdup("null");
			    }
			    printf("\"data\":%s", data);
			    free(data);
			    printf("}");
			    if(j < saveBuf[i].funcNum - 1)
			        printf(",");
			}
			printf("]");
			printf("}");
			if(i < count - 1)
			    printf(",");
		}
        if(saveBuf != NULL)
        	bt4comm_delete_node_list(saveBuf, count);
	}
	printf("]");
    if(callback != NULL)
        printf(")");
	if(callback != NULL)
	    free(callback);
	if(nwkAddr != NULL)
	    free(nwkAddr);
	return 0;
}
