/****************************************************************/
/* FileName: wifi_pkgman.c                                           */
/* Desc:     This is a common module that would be used by      */
/*           any other modules.                                 */
/* Author:   Lijian<lijian@sunplusapp.com>                      */
/* History:                                                     */
/*           2012-04-24 0.2     Fix some bug                    */
/*           2012-04-09 0.1     First Version                   */
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wifi_pkgman.h"
#include <errno.h>
#include "wifi_drv/wifi.h"

static uint8 calcMemoryFcs(uint8 lastResult, const void *buf, uint8 len)
{
    uint8 x;
    uint8 xorResult = lastResult;
    const uint8 *msg_ptr = (const uint8 *)buf;

    for ( x = 0; x < len; x++, msg_ptr++ )
        xorResult = xorResult ^ *msg_ptr;

    return xorResult;
}

static uint8 calcPackageFcs(WIFICOMMPKG *pkg)
{
    return calcMemoryFcs(0, &pkg->len, pkg->len + sizeof(pkg->len));
}

WIFICOMMPKG *pkgman_create_package(uint8 nodeEP, const void *data, uint8 len)
{
	static unsigned char buf[100];
	WIFICOMMPKG *pkg = NULL;
    if((data == NULL) || (len <= 0))
        return NULL;

    //pkg = (WIFICOMMPKG *)malloc(sizeof(WIFICOMMPKG) + len);
    pkg = (WIFICOMMPKG*)buf;
    pkg->sop = WIFICOMM_SOP;
    pkg->len = sizeof(WIFICOMMPKG_DATA) + len;
    pkg->dataField.endPoint = nodeEP;
    memcpy(pkg->dataField.data, data, len);
    pkg->fcs = calcPackageFcs(pkg);
    return pkg;
}

void pkgman_delete_package(WIFICOMMPKG *pkg)
{
    //free(pkg);
}

int pkgman_send_package(int cid, const WIFICOMMPKG *pkg)
{
	unsigned char cmd[20],len;
	
    if(pkg == NULL)	return 0;
    len = sprintf(cmd,"AT+CIPSEND=1,%d\r\n",WIFICOMMPKG_LEN(pkg)+3);
    UART_Send(&cmd, len); 
    SystemTickWait(300);   
    UART_Send((unsigned char *)&(pkg->sop), WIFICOMMPKG_LEN(pkg));
    UART_Send((unsigned char *)&(pkg->fcs), sizeof(pkg->fcs));
    UART_Send("\r\n", 2);
    return WIFICOMMPKG_LEN(pkg) + sizeof(pkg->fcs);
}

int pkgman_send_packageEx(int fd, unsigned char nodeEP, const void *data, int len)
{
    WIFICOMMPKG *pkg = pkgman_create_package(nodeEP, data, len);
    int ret = 0;
    if(pkg == NULL)
        return 0;
    ret = pkgman_send_package(fd, pkg);
    pkgman_delete_package(pkg);
    return ret;
}

PM_RECVINFO *pkgman_init_recv_info(PM_RECVINFO *info)
{
    if(info == NULL)
        return NULL;
    info->status = STAT_SOP;
    info->dataIdx = 0;
    info->dataPnter = NULL;
    info->pkg = NULL;
    return info;
}
int pkgman_recv_packageCb(PM_RECVINFO *info, const unsigned char *data, int len, WIFICOMMPKG **pkg, const unsigned char **restData, int *restLen)
{
	static unsigned char buf[100];
    int ret = 0;
    *restData = NULL;
    *restLen = 0;
    while((len > 0) && (info->status != STAT_DONE))
    {
        uint8 ch = *data++;
        len--;
        switch(info->status)
        {
        case STAT_SOP:
            if(ch == WIFICOMM_SOP)
                info->status = STAT_LEN;
            break;
        case STAT_LEN:
            if(ch <= sizeof(WIFICOMMPKG_DATA))
                info->status = STAT_SOP;
            else
            {
                //info->pkg = (WIFICOMMPKG *)malloc(sizeof(WIFICOMMPKG) + ch - sizeof(WIFICOMMPKG_DATA));
                info->pkg = (WIFICOMMPKG*)buf;
                info->dataIdx = 0;
                info->pkg->sop = WIFICOMM_SOP;
                info->pkg->len = ch;
                info->dataPnter = info->pkg->dataBody;
                info->status = STAT_DATA;
            }
            break;
        case STAT_DATA:
            *(info->dataPnter) = ch;
            info->dataPnter++;
            if(++(info->dataIdx) >= info->pkg->len)
                info->status = STAT_FCS;
            break;
        case STAT_FCS:
            info->pkg->fcs = ch;
            info->status = STAT_DONE;
            break;
        default:
            break;
        }
    }
    if(info->status == STAT_DONE)
    {
        if(info->pkg->fcs != calcPackageFcs(info->pkg))
        {
            free(info->pkg);
            info->pkg = NULL;
        }
        else
            ret = 1;
        *pkg = info->pkg;
        info->status = STAT_SOP;
        info->dataIdx = 0;
        info->dataPnter = NULL;
        info->pkg = NULL;
    }
    if(len <= 0)
    {
        *restData = NULL;
        *restLen = 0;
    }
    else
    {
        *restData = data;
        *restLen = len;
    }
    return ret;
}
