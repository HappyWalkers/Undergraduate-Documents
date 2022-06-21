//1.	ͨ���Ҫ�󣺱�дһ��C���Գ���ʵ��Timer A��ʱ�����жϹ��ܡ�
//2.	ʵ�ֹ��ܣ� �򿪲�����TimerA��ʱ�������ҿ�TimerA��IRQ1�жϣ�����TimerA��IRQ1�ж�����ʱ����Ӧ��Ӧ���жϷ���������жϷ����з�תI/O�˿������ƽ���Կ��ƽ���I/O�˿ڵķ�������ܣ�LED��������
//3.	ʵ������TimerA��ʱ����Ϊ2s����8��LED�ĸ�������Ϊ�͵�ƽ��ǰ���£�������TimerA��IRQ1�жϺ󣬷�ת8·��������ܵ���ʾ�� 
//

#include "SPCE061A.h"
#include "led.h"

unsigned char g_ucLed_Data;	 
void TimerA_Init();


int main()
{
	__asm("IRQ OFF");
	INIT_LED();								// led�˿ڳ�ʼ��
	TimerA_Init();					   		// TimerA��ʼ��
	__asm("IRQ ON");
	g_ucLed_Data = 0;
	while(1)
	{
		LED_Printf(g_ucLed_Data,BYTE_5);    //ˢ��LED��ʾ
		*P_Watchdog_Clear = 0x0001;			// �忴�Ź�

	}
	return 0;
}

/*****************************************************************
��API ��ʽ����void TimerA_Init(void)
������˵������TimerA��ʼ����
����	�������ޣ�
���� �� ֵ�����ޣ�
��ʹ�þ�������TimerA_Init();
����    ע��: 
*****************************************************************/
void TimerA_Init()
{
	*P_TimerA_Ctrl = (1<<3)|(5);		//ѡ���Ƶ2Hz clOckA 1,clockB 1024HZ
	*P_TimerA_Data = 0xF7FF;			//���ü�����ֵ ��10000H-F7FFH��*1/1024=2s�� 0xF800
	*P_INT_Ctrl |= (1<<12);    			// enable IRQ1_TMA
}
