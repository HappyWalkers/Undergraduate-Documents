/***********************************************************
**  FileName:         Basic.c
**  Introductions:    Sunplusapp CC2530 ZigBee Node Basic Functions & Options
**  Last Modify time: 2012.05.28
**  Modify:           传感器实验仪中LED标号更改
**  Author:           GuoZhenjiang	<zhenjiang.guo@sunplusapp.com>
***********************************************************/

#include "Basic.h"

/***********************************************************
**  函数名称: SystemClockSet
**  实现功能: 系统时钟设置
**  入口参数: RTC_Clk:  RTC时钟源选择( CPU_32kHz_RC 或 CPU_32kHz_XOC)
**            CPU_Clk:  CPU时钟源选择( CPU_16MHz_RC 或 CPU_32MHz_XOC)
**            T_Spd:    定时器时钟源预分频设置，TSPD_x，表示取CPU时钟源的1/x。
**            CPU_Spd:  CPU时钟源预分频设置， CLKSPD_x，表示取CPU时钟源的1/x。
**  返回结果: None
***********************************************************/
void SystemClockSet( ClkSet_t RTC_Clk, ClkSet_t CPU_Clk, ClkSet_t T_Spd, ClkSet_t CPU_Spd )
{
  uint8 SysClockSet;
  SysClockSet = RTC_Clk | CPU_Clk | T_Spd | CPU_Spd;
  //设置系统各项时钟参数
  CLKCONCMD = SysClockSet;

  //等待时钟稳定
  while( CLKCONSTA != SysClockSet)
      ;
}

/***********************************************************
**  函数名称: delay_us
**  实现功能: 微秒级短暂延时
**  入口参数: [t]:CPU 减一延时次数;
**  返回结果: None
***********************************************************/
void delay_us(uint16 t)
{
  uint16 i;
  for(i=0; i<t; i++)
    ;
}

/***********************************************************
**  函数名称: delay_10ms
**  实现功能: 延时函数
**  入口参数: num_10ms:要延时值的 10ms 个数;
**  返回结果: None
***********************************************************/
void delay_10ms(uint16 num_10ms)
{
  uint16 i, j, k;
  for(i=0; i<num_10ms; i++)
    for(j=0; j<100; j++)
      for(k=0; k<100; k++)
        ;
}

/***********************************************************
**  函数名称: LED_4_5_PortInit
**  实现功能: 扩展板上的 LED_D4_D5 端口初始化
**  入口参数: None
**  返回结果: None
***********************************************************/
void LED_4_5_PortInit(void)
{
  P1SEL &= ~0X02;
  P2SEL &= ~0X01;

  P1DIR |= 0X02;
  P2DIR |= 0X01;

  LED_4_OFF;
  LED_5_OFF;
}

/***********************************************************
**  函数名称: SetIOInput
**  实现功能: 设置端口为普通输入IO
**  入口参数: group:Port;
**            bit:Bit;
**            pull:(Pull_None:无上下拉; Pull_Up:上拉; Pull_Down:下拉;);
**  返回结果: None
***********************************************************/
void SetIOInput(uint8 group, uint8 bit, PullSet_t pull)
{
   switch(group)
   {
     case 0:
       //设置为通用输入IO
       P0DIR &= BIT_0(bit); P0SEL &= BIT_0(bit);
       //设置内部上下拉电阻状态
       if(Pull_None == pull)
         P0INP |= BIT_1(bit);     //P0INP[7-0]:(0:上下拉有效; 1:无效;)
       else if(Pull_Up == pull)
       {
         P0INP &= BIT_0(bit);     //P0INP[7-0]:(0:上下拉有效; 1:无效;)
         P2INP &= BIT_0(5);       //P2INP[5  ]:(0:Port0 上拉; 1:Port0 下拉;)
       }
       else if(Pull_Down == pull)
       {
         P0INP &= BIT_0(bit);     //P0INP[7-0]:(0:上下拉有效; 1:无效;)
         P2INP |= BIT_1(5);       //P2INP[5  ]:(0:Port0 上拉; 1:Port0 下拉;)
       }
       break;
     case 1:
       //设置为通用输入IO
       P1DIR &= BIT_0(bit); P1SEL &= BIT_0(bit);
       //设置内部上下拉电阻状态
       if(Pull_None == pull)
         P1INP |= BIT_1(bit);     //P1INP[7-2]:(0:上下拉有效; 1:无效;) P[1-0] 写无效，读为0.
       else if(Pull_Up == pull)
       {
         P1INP &= BIT_0(bit);     //P1INP[7-2]:(0:上下拉有效; 1:无效;) P[1-0] 写无效，读为0.
         P2INP &= BIT_0(6);       //P2INP[6  ]:(0:Port1 上拉; 1:Port1 下拉;)
       }
       else if(Pull_Down == pull)
       {
         P0INP &= BIT_0(bit);     //P1INP[7-2]:(0:上下拉有效; 1:无效;) P[1-0] 写无效，读为0.
         P2INP |= BIT_1(6);       //P2INP[6  ]:(0:Port1 上拉; 1:Port1 下拉;)
       }
       break;
     case 2:
       //设置为通用输入IO
       P2DIR &= BIT_0(bit); P2SEL &= BIT_0(bit);
       //设置内部上下拉电阻状态
       if(Pull_None == pull)
         P2INP |= BIT_1(bit);     //P2INP[4-0]:(0:上下拉有效; 1:无效;)
       else if(Pull_Up == pull)
       {
         P2INP &= BIT_0(bit);     //P2INP[4-0]:(0:上下拉有效; 1:无效;)
         P2INP &= BIT_0(7);       //P2INP[7  ]:(0:Port2 上拉; 1:Port2 下拉;)
       }
       else if(Pull_Down == pull)
       {
         P2INP &= BIT_0(bit);     //P2INP[4-0]:(0:上下拉有效; 1:无效;)
         P2INP |= BIT_1(7);       //P2INP[7  ]:(0:Port2 上拉; 1:Port2 下拉;)
       }
       break;
     default:
       break;
   }
}

/***********************************************************
**  函数名称: SetIOOutput
**  实现功能: 设置端口为普通输出IO
**  入口参数: group:Port;
**            bit:Bit;
**  返回结果: None
***********************************************************/
void SetIOOutput(uint8 group, uint8 bit)
{
   switch(group)
   {
     case 0: P0DIR |= BIT_1(bit); P0SEL &= BIT_0(bit); break;
     case 1: P1DIR |= BIT_1(bit); P1SEL &= BIT_0(bit); break;
     case 2: P2DIR |= BIT_1(bit); P2SEL &= BIT_0(bit); break;
     default: break;
   }
}

/***********************************************************
**  函数名称: GetIOLevel
**  实现功能: 获取端口的输入状态
**  入口参数: group:Port;
**            bit:Bit;
**  返回结果: (0:Low; 1:High;)
***********************************************************/
uint8 GetIOLevel(uint8 group, uint8 bit)
{
    switch(group)
    {
      case 0: return !!(P0 & (BIT_1(bit)));
      case 1: return !!(P1 & (BIT_1(bit)));
      case 2: return !!(P2 & (BIT_1(bit)));
      default: break;
    }
    return 0;
}

/***********************************************************
**  函数名称: SetIOLevel
**  实现功能: 设置端口的输出电平
**  入口参数: group:Port;
**            bit:Bit;
**            value:(0:Low; 1:High);
**  返回结果: None
***********************************************************/
void SetIOLevel(uint8 group, uint8 bit, uint8 value)
{
    switch(group)
    {
      case 0:
          if(value)
            P0 |= BIT_1(bit);
          else
            P0 &= BIT_0(bit);
          break;
      case 1:
          if(value)
            P1 |= BIT_1(bit);
          else
            P1 &= BIT_0(bit);
          break;
      case 2:
          if(value)
            P2 |= BIT_1(bit);
          else
            P2 &= BIT_0(bit);
          break;
      default:
          break;
    }
}

/***********************************************************
**  函数名称: IOIntteruptSet
**  实现功能: 设置端口中断触发方式
**  入口参数: group:Port;
**            bit:Bit;
**            trigger:(Rising:上升沿触发; Falling:下降沿触发;)
**  返回结果: None
***********************************************************/
void IOIntteruptSet(uint8 group, uint8 bit, IntSel_t trigger)
{
  switch(group)
  {
    case 0:
        IEN1 |= BIT_1(5); //P0总中断允许
        switch(trigger)
        {
          case None:    P0IEN &= BIT_0( bit ); break;   //单独位中断屏蔽
          case Rising:  P0IEN |= BIT_1( bit );  PICTL &= BIT_0(0); break;
          case Falling: P0IEN |= BIT_1( bit );  PICTL |= BIT_1(0); break;
          default : break;
        }
      break;
    case 1:
        IEN2 |= BIT_1(4); //P1总中断允许
        switch(trigger)
        {
          case None:    P1IEN &= BIT_0( bit ); break;   //单独位中断屏蔽
          case Rising:
            {
              if( bit <= 3 )
              {
                P1IEN |= BIT_1( bit );  PICTL &= BIT_0(1); break;
              }
              else if( bit >= 4 )
              {
                P1IEN |= BIT_1( bit );  PICTL &= BIT_0(2); break;
              }
            }
          case Falling:
            {
              if( bit <= 3 )
              {
                P1IEN |= BIT_1( bit );  PICTL |= BIT_1(1); break;
              }
              else if( bit >= 4 )
              {
                P1IEN |= BIT_1( bit );  PICTL |= BIT_1(2); break;
              }
            }
          default : break;
        }
      break;
    case 2:
        IEN2 |= BIT_1(1); //P2总中断允许
        switch(trigger)
        {
          case None:    P2IEN &= BIT_0( bit ); break;   //单独位中断屏蔽
          case Rising:  P2IEN |= BIT_1( bit );  PICTL &= BIT_0(3); break;
          case Falling: P2IEN |= BIT_1( bit );  PICTL |= BIT_1(3); break;
          default : break;
        }
      break;
  }
}