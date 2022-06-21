
#include "Basic.h"
#include "UART.h"
#include "Control.h"

extern uint8 ControlState;

void main(void)
{
  //LED 灯（D8 D9）端口初始化
  LEDPortInit();

  //UART0 初始化
  UART0_Init( BAUD_115200 );

  //控制器（执行器）端口(P1.7~P1.4)初始化
  SetIOOutput(1,4);
  SetIOOutput(1,5);
  SetIOOutput(1,6);
  SetIOOutput(1,7);

  //初始化继电器状态
  ControlState = ControlSet(0X00);

  for( ; ; )
  {
    /*
    通过串口调试助手发送1Byte,该Byte的低4位代表控制器下一个状态
    对应位是1：继电器吸合，对应LED点亮；
    对应位是0：继电器断开，对应LED熄灭；
    | P1.4 | P1.3 | P1.2 | P1.1 |
    |  BD  |  BU  |  AD  |  AU  |
    通过UART0中断处理函数改变控制状态。
    */
    //显示当前状态
    Dis_ConState( ControlState );

    //运行时LED 指示灯闪烁
    SET_LED_D8;
    Delay(5);
    CLR_LED_D8;
    Delay(120);
  }
}
