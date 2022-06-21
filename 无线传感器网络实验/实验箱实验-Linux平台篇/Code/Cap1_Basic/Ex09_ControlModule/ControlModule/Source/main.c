
#include "Basic.h"
#include "UART.h"
#include "Control.h"

extern uint8 ControlState;

void main(void)
{
  //LED �ƣ�D8 D9���˿ڳ�ʼ��
  LEDPortInit();

  //UART0 ��ʼ��
  UART0_Init( BAUD_115200 );

  //��������ִ�������˿�(P1.7~P1.4)��ʼ��
  SetIOOutput(1,4);
  SetIOOutput(1,5);
  SetIOOutput(1,6);
  SetIOOutput(1,7);

  //��ʼ���̵���״̬
  ControlState = ControlSet(0X00);

  for( ; ; )
  {
    /*
    ͨ�����ڵ������ַ���1Byte,��Byte�ĵ�4λ�����������һ��״̬
    ��Ӧλ��1���̵������ϣ���ӦLED������
    ��Ӧλ��0���̵����Ͽ�����ӦLEDϨ��
    | P1.4 | P1.3 | P1.2 | P1.1 |
    |  BD  |  BU  |  AD  |  AU  |
    ͨ��UART0�жϴ������ı����״̬��
    */
    //��ʾ��ǰ״̬
    Dis_ConState( ControlState );

    //����ʱLED ָʾ����˸
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
