
#include "Basic.h"
#include "UART.h"


void main(void)
{
  uint8 SensorValue;
  //LED �ƣ�D8 D9���˿ڳ�ʼ��
  LEDPortInit();

  //UART0 ��ʼ��
  UART0_Init( BAUD_115200 );

  //�������˿�(P0_0)��ʼ��
  SetIOInput(0,0);

  for( ; ; )
  {
    //��ȡ������ֵ
    SensorValue = GetIOLevel( 0, 0 );
    //��ʾ���
    UART0_Send( "Rain Sensor:", sizeof("Rain Sensor:")-1 );
    UART0_Dis_uNum(SensorValue);
    if(0 == SensorValue)
      UART0_Send( "Sunny", sizeof("Sunny")-1 );
    else if(1 == SensorValue)
      UART0_Send( "Raining!", sizeof("Raining!")-1 );
    UART0_Send( "\r\n", sizeof("\r\n")-1 );

    //����ʱLED ָʾ����˸
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
