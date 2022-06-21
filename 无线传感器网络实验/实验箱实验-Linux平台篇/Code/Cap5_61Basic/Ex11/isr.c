//======================================================
// �ļ�����:	isr.c
// ����������   �忴�Ź�������UART���� 
// ά����¼��  	
//				
//======================================================

#include "wifi/wifi.h"
#include "wifi/SystemTime.h"
#include <stdio.h>
#include "Shake/Shake.h"

unsigned char valueString[20];
unsigned char ShakeSensorFlag = NORMAL;
	
void IRQ4(void) __attribute__((ISR));
void IRQ4(void)
{
	if(*P_INT_Ctrl & C_IRQ4_1KHz)
	{
		SystemTickISR();
		*P_INT_Clear = C_IRQ4_1KHz;
	}
	if(*P_INT_Ctrl & C_IRQ4_4KHz)
	{
		if(ShakeRefresh() == WARNING )
		{
			ShakeSensorFlag = WARNING;
			sprintf(valueString,"Shake:%02d\n",ShakeSensorFlag);	//���𶯴��������ݱ���ַ���	
			UART_Send(valueString, sizeof(valueString));			//ͨ�����ڷ�������,��͸��ģʽ�����ݿɱ�TCP���������յ�
		}					
		*P_INT_Clear = C_IRQ4_4KHz;
	}
}
//============================================================= 
// �﷨��ʽ:    void IRQ5(void);
// ʵ�ֹ���:	�忴�Ź�
// ����:    ��
// ����ֵ:    ��
//=============================================================
void IRQ5(void) __attribute__ ((ISR));
void IRQ5(void)
{
	*P_Watchdog_Clear = 0x0001;
	*P_INT_Clear = C_IRQ5_2Hz;                                  //���жϱ�־
}
