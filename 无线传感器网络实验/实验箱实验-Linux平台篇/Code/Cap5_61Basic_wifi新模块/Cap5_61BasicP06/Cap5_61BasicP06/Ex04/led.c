#include "led.h"

/*****************************************************************
��API ��ʽ����void INIT_LED(void)
������˵������led�˿ڳ�ʼ����
����	�������ޣ�
���� �� ֵ�����ޣ�
��ʹ�þ�������INIT_LED();
����    ע��: 
*****************************************************************/
void INIT_LED(void)
{
	*P_IOA_Dir = 0x8700;  //*P_IOB_Data = 0x00;
	*P_IOA_Attrib = 0x8700;  //*P_IOB_Dir = 0x87;
	*P_IOA_Data = 0x00;  //*P_IOB_Attrib = 0x87;	
//  P1SEL &= ~0xFF;
//  P1DIR |= 0xFF;
//  P1 = 0;
}
/*****************************************************************
��API ��ʽ����void LED_Printf(unsigned char data,unsigned char byte)
������˵����������8·LED��ͨ��74HC595����
����    ������unsigned char data,led��ʾ����ֵ��
			  unsigned char byte ��ѡ���˴�����ΪBYTE_5
���� �� ֵ�����ޣ�
��ʹ�þ�������LED_Printf(1,BYTE_5);
����    ע��: 
*****************************************************************/
void LED_Printf(unsigned char data,unsigned char byte)
{
  unsigned char bits = 0;
  unsigned char get_bit = 0x80;
  *P_IOA_Data |= byte;  //*P_IOB_Data |= byte;
  RCK = LOW;
  SRCK = LOW;
  for(bits = 8;bits > 0;bits --)
  {
    if(data & get_bit)
      SER = 1;
    else
      SER = 0;
    SRCK = HIGH;
    get_bit >>= 1;
    SRCK = LOW;
  }
  RCK = HIGH;
}






