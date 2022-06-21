#ifndef __UART_H__
#define __UART_H__

#include "iocc2541.h"
#include "ioCC2541_bitdef.h"
//����ģʽ����
//����������
//����0��ʼ��(�����ʡ�ӳ��˿�)
//����1��ʼ��(�����ʡ�ӳ��˿�)
//�����ж�����
//��ͨ���ͺ���
//�жϷ��ͺ���

//U0CSR��U0UCR��U0GCR��U0DBUF��U0BAUD
//U0CSR UART0 Control and Status Register
//U0UCR 

// CC2541 UART �����ʿ�ѡֵ
typedef enum
{
  BAUD_2400,      //UxGCR |= 6;     UxBAUD |= 59;
  BAUD_4800,      //UxGCR |= 7;     UxBAUD |= 59;
  BAUD_9600,      //UxGCR |= 8;     UxBAUD |= 59;
  BAUD_14400,     //UxGCR |= 8;     UxBAUD |= 216;
  BAUD_19200,     //UxGCR |= 9;     UxBAUD |= 59;
  BAUD_28800,     //UxGCR |= 9;     UxBAUD |= 216;
  BAUD_38400,     //UxGCR |= 10;    UxBAUD |= 59;
  BAUD_57600,     //UxGCR |= 10;    UxBAUD |= 216;
  BAUD_76800,     //UxGCR |= 11;    UxBAUD |= 59;
  BAUD_115200,    //UxGCR |= 11;    UxBAUD |= 216;
  BAUD_230400,    //UxGCR |= 12;    UxBAUD |= 216;
}BaudSel_t;

void Init_UART0(BaudSel_t baud,uint8 alt);
void UART0_Send( char* pData,int len );


#endif//__UART_H__