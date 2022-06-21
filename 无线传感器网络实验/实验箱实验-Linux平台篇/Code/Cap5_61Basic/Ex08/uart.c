//======================================================
// �ļ�����:	uart.c
// ����������   SPCE061A������������ 
// ά����¼��  	
//				
//======================================================
#include    "SPCE061A.h"
#include    "uart.h"
//============================================================= 
// �﷨��ʽ:    void SP_UARTInitial(void);
// ʵ�ֹ���:	UART��ʼ��
// ����:    	��
// ����ֵ:    	��
//=============================================================
void SP_UARTInitial(void)
{
	*P_IOB_Dir |= 0x0400;	//bit10��Ϊ����ڣ�Tx��,bit7��Ϊ����ڣ�Rx��   0100 0000 0000  IOB10 =1				
	*P_IOB_Dir &= 0xff7f;	// 1111 1111 0111 1111  IOB8 = 0				 		
	*P_IOB_Attrib |= 0x0480;					
	*P_IOB_Buffer &= 0xfb7f;
						
	*P_UART_Command1 = C_UART_Reset;					//UART��λ
	
	*P_UART_BaudScalarHigh = C_UARTBaudRate_9600_H;		//��������Ϊ9600
	*P_UART_BaudScalarLow = C_UARTBaudRate_9600_L;

	*P_UART_Command1 = C_UART_Rx_IRQ_ENB;				//UART�����ж�ʹ��
	*P_UART_Command2 = C_UART_Rx_Pin_ENB|C_UART_Tx_Pin_ENB;				//UART���չܽ�ʹ�� ,���͹ܽ�ʹ��
}

void Uart_Send_ASC(unsigned char ch)
{
	*P_UART_Data = ch;
	while (!((*P_UART_Command2) & C_UART_Tx_RDY));
}
//�����ַ���
void Uart_Send_String(unsigned char *ptr)
{
	while (*ptr != '\0')
	{
		Uart_Send_ASC(*ptr);
		ptr++;
	}
}
// 
//============================================================= 
// �﷨��ʽ:    
//	void Uart_Send_Multi_ASC(unsigned char *ptr,unsigned char cnt)
// ʵ�ֹ���:	���Ͷ��ASC
// ����:    	*ptr ����ָ��
//	           cnt ��������
// ����ֵ:    	��
//=============================================================

void Uart_Send_Multi_ASC(unsigned char *ptr,unsigned char cnt)
{
	unsigned char i;

	for(i=0;i<cnt;i++)  
	{
		Uart_Send_ASC(*ptr);
		ptr++;
	}
}
