
#include "Basic.h"
#include "UART.h"

void main(void)
{	
  uint8 ADC_Value;
  //LED �ƣ�D8 D9���˿ڳ�ʼ��
  LEDPortInit();

  //UART0 ��ʼ��
  UART0_Init( BAUD_115200 );

  //ADC ͨ��0��ʼ��
  P0SEL |= 0X01;

  while(1)
  {
    //��ȡ������ֵ
    ADC_Value = 127 - GetCh08bitADC();
    //��ʾ���

    UART0_Dis_uNum( ADC_Value );
    UART0_Send("\r\n", sizeof("\r\n")-1);

    //����ʱLED ָʾ����˸
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
