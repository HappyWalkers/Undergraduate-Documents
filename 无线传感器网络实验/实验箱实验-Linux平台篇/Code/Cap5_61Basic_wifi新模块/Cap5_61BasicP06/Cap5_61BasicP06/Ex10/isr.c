//======================================================
// �ļ�����:	isr.c
// ����������   �忴�Ź�������UART���� 
// ά����¼��  	
//				
//======================================================

#include "wifi/wifi.h"
#include "wifi/SystemTime.h"

void IRQ4(void) __attribute__((ISR));
void IRQ4(void)
{
	if(*P_INT_Ctrl & C_IRQ4_1KHz)
	{
		SystemTickISR();
		*P_INT_Clear = C_IRQ4_1KHz;
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
