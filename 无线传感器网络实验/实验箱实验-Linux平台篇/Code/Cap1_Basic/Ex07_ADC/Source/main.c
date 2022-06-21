
#include "Basic.h"
#include "UART.h"

void main(void)
{	
  uint8 ADC_Value;
  //LED 灯（D8 D9）端口初始化
  LEDPortInit();

  //UART0 初始化
  UART0_Init( BAUD_115200 );

  //ADC 通道0初始化
  P0SEL |= 0X01;

  while(1)
  {
    //读取传感器值
    ADC_Value = 127 - GetCh08bitADC();
    //显示结果

    UART0_Dis_uNum( ADC_Value );
    UART0_Send("\r\n", sizeof("\r\n")-1);

    //运行时LED 指示灯闪烁
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
