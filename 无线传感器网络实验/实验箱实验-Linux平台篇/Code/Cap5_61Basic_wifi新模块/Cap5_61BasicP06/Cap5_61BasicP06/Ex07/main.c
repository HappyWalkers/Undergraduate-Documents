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
//  ����������	WiFiģ�����ݴ���ʵ��


//  �漰�Ŀ⣺	CMacro1016.lib       	
//  ����ļ���	main.c��
//		
//			uart.c�ļ�, uart.hͷ�ļ���
//			SHT10.c�ļ�,  SHT10.hͷ�ļ���
//			isr.c
//	Ӳ�����ӣ�
//	ά����¼��	2011-12-14 v1.0
//===============================================
#include    "SPCE061A.h"
#include	"SHT10.h"
#include	"uart.h"
int tempre;													//  �¶�ʵ��ֵ��100��
int humit; 													//  ʪ��ʵ��ֵ��100����humidity [hju:'mid?ti]	 ʪ�ȣ�ʪ��

void Temp_Humi_Collect(void);
int main()
{ 
	unsigned char work;
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	SHT10_init(0x01);
	SP_UARTInitial();											//UART��ʼ��
	*P_INT_Ctrl = C_IRQ5_2Hz;									//��2Hz�жϣ�������ʱ�忴�Ź�����ʱ
	__asm("IRQ ON");
	
	
	
	while(1)
	{
		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared

		Temp_Humi_Collect();									//�ɼ�����

	
			
		//���ڷ��͵�ǰ�¶�ֵ
		Uart_Send_String("Current Temp:");
			
		work = (unsigned char)(tempre/1000) + '0';					// ǧλ
		Uart_Send_ASC(work);								//���ڷ����¶�����
		work = (unsigned char)(tempre%1000/100) + '0';				// ��λ
		Uart_Send_ASC(work);				
		work = '.';
		Uart_Send_ASC(work);
		work = (unsigned char)(tempre%100/10) + '0';				// ʮλ
		Uart_Send_ASC(work);								//���ڷ����¶�С��
		work = (unsigned char)(tempre%10) + '0';					// ��λ
		Uart_Send_ASC(work);
		
		//���ڷ��͵�ǰʪ��ֵ
		Uart_Send_String(";Current Humidity:");
		work = (unsigned char)(humit/1000) + '0';					// ǧλ
		Uart_Send_ASC(work);							//���ڷ���ʪ������
		work = (unsigned char)(humit%1000/100) + '0';				// ��λ
		Uart_Send_ASC(work);			
		work = '.';
		Uart_Send_ASC(work);
		work = (unsigned char)(humit%100/10) + '0';					// ʮλ
		Uart_Send_ASC(work);								//���ڷ���ʪ��С��
		work = (unsigned char)(humit%10) + '0';						// ��λ
		Uart_Send_ASC(work);
		Uart_Send_String("\r\n");
		
	}
}

/*****************************************************************
��API ��ʽ����void Temp_Humi_Collect(void)
������˵��������ȡ��ʪ�ȴ�����SHT10����
����    ������
���� �� ֵ����
��ʹ�þ�������Temp_Humi_Collect();
����    ע��: 
*****************************************************************/
void Temp_Humi_Collect(void)
{
	unsigned int error,temp_value,humi_value;
	unsigned char checksum;
	error = 0;
	
	error+=SHT10_Measure((unsigned int*) &temp_value,&checksum,TEMPERATURE);//measure temperature
	tempre = CalcT(temp_value); //2167;  	
	if(error!=0) 	   	
		SHT10_Connectionreset();   //in case of an error: connection reset

	error+=SHT10_Measure((unsigned int*) &humi_value,&checksum,HUMIDITY);//measure temperature
	humit  = CalcRH(humi_value);//3498; 		  
	if(error!=0) 	   	
	SHT10_Connectionreset();   //in case of an error: connection reset
}

