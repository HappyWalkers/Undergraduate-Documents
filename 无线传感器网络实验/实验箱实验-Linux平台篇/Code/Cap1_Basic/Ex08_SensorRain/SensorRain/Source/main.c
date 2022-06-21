
#include "Basic.h"
#include "UART.h"


void main(void)
{
  uint8 SensorValue;
  //LED 灯（D8 D9）端口初始化
  LEDPortInit();

  //UART0 初始化
  UART0_Init( BAUD_115200 );

  //传感器端口(P0_0)初始化
  SetIOInput(0,0);

  for( ; ; )
  {
    //读取传感器值
    SensorValue = GetIOLevel( 0, 0 );
    //显示结果
    UART0_Send( "Rain Sensor:", sizeof("Rain Sensor:")-1 );
    UART0_Dis_uNum(SensorValue);
    if(0 == SensorValue)
      UART0_Send( "Sunny", sizeof("Sunny")-1 );
    else if(1 == SensorValue)
      UART0_Send( "Raining!", sizeof("Raining!")-1 );
    UART0_Send( "\r\n", sizeof("\r\n")-1 );

    //运行时LED 指示灯闪烁
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
