//main.c
/*****************************************************************************
���Ҫ�󣺱�дһ��C ���Գ���ʵ�ֶ˿�IOA�����������
2��ʵ�ֹ��ܣ�ͨ��IOA����������ݿ��� 8 ����������ܵ�����
3��ʵ������8����������ܶ�̬������Ϩ�𣬲���ѭ����ʾ��
*****************************************************************************/
#include "SPCE061A.h"
#include "led.h"

void delay();
int main()
{
	unsigned char data=0;	 
	//add your code here
	INIT_LED();
	while(1)
	{
		data++;
		LED_Printf(data,BYTE_5);        // 74HC595����
		
		delay();
		*P_Watchdog_Clear = 0x0001;	    // �忴�Ź�

	}
	return 0;
}

void delay()
{
	unsigned int j;
		for(j=0;j<10000;j++);
		
}
