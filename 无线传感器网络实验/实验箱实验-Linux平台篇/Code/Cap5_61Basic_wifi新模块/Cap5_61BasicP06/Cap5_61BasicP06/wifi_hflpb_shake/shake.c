/**************************************************************
*   File Name:  Shake.c
*   Introductions:
*   Last Modify Date: 2013.07.22
*   Modify:
*   Author: GuoZhenjiang < zhenjiang.guo@sunplusapp.com >
**************************************************************/
#include "Shake.h"

#define SHAKE_IN 			C_Bit0					//�𶯴���������IOA0

#define SET_IOA_BIT(b)		do { *P_IOA_Buffer |= (b); } while(0)
#define CLR_IOA_BIT(b)		do { *P_IOA_Buffer &=~(b); } while(0)
#define READ_IOA_BIT(b)		((*P_IOA_Data & (b)) ? 1 : 0)

void ShakeInit(void)
{
    *P_IOA_Dir &= ~SHAKE_IN;         //IOA0��Ϊ�𶯴������������ ����Ϊ���������������˿�
	*P_IOA_Attrib &= ~SHAKE_IN;
	*P_IOA_Data |= SHAKE_IN;
}
unsigned char ShakeRefresh(void)
{
    // ��3����ʾ��⵽��״̬
   unsigned char SensorFlag = 0;
   SensorFlag = READ_IOA_BIT(SHAKE_IN);
   return SensorFlag;
}
