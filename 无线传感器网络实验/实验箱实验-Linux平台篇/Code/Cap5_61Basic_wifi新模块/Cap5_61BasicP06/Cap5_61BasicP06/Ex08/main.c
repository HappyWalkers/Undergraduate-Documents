//======================================================
//  The information contained herein is the exclusive property of
//  SUNPLUSAPP Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNPLUSAPP TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  �������ƣ�	Ex_?
//  ����������	�����ݴ���ʵ��


//  �漰�Ŀ⣺	CMacro1016.lib       	
//  ����ļ���	main.c��
//		
//				uart.c�ļ�, uart.hͷ�ļ���
//				isr.c
//	Ӳ�����ӣ�
//	ά����¼��	2011-12-14 v1.0
//===============================================
#include	"uart.h"
#include 	"Shake.h"


void ShakeInit(void);
unsigned char ShakeRefresh(void);


unsigned char work;
unsigned char valueString[20];
unsigned char ShakeSensorFlag = NORMAL;


int main()
{
	//add your code here
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	ShakeInit();
	SP_UARTInitial();						//UART��ʼ��	
	*P_INT_Ctrl = C_IRQ5_2Hz|C_IRQ4_4KHz;	//��2Hz�жϣ�������ʱ�忴�Ź�����ʱ
	__asm("IRQ ON");
	while(1)
	{
		;
	}
	return 0;
}

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

//============================================================= 
// �﷨��ʽ:    void IRQ4(void);
// ʵ�ֹ���:	�忴�Ź�
// ����:    	��
// ����ֵ:    	��
//=============================================================	
void IRQ4(void) __attribute__((ISR));
void IRQ4(void)
{
	if(*P_INT_Ctrl & C_IRQ4_4KHz)
	{
		if(ShakeRefresh()== WARNING)
		{
			ShakeSensorFlag = WARNING;
			sprintf(valueString,"Current Shake:%02d\n",ShakeSensorFlag);		//���𶯴��������ݱ���ַ���	
			Uart_Send_String(valueString);			//ͨ�����ڷ�������,
		}					
		*P_INT_Clear = C_IRQ4_4KHz;
	}
	
}
//============================================================= 
// �﷨��ʽ:    void IRQ5(void);
// ʵ�ֹ���:	�忴�Ź�
// ����:    	��
// ����ֵ:    	��
//=============================================================
void IRQ5(void) __attribute__ ((ISR));
void IRQ5(void)
{
	*P_Watchdog_Clear = 0x0001;
	//���ڷ��͵�ǰ�¶�ֵ
	ShakeSensorFlag = ShakeRefresh();
	sprintf(valueString,"Current Shake:%02d\n",ShakeSensorFlag);		//���𶯴��������ݱ���ַ���	
	Uart_Send_String(valueString);			//ͨ�����ڷ�������,
	*P_INT_Clear = C_IRQ5_2Hz;  //���жϱ�־
}