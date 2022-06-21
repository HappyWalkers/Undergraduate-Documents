
#include "Basic.h"

/***********************************************************
**  函数名称: delay
**  实现功能: 微秒级短暂延时函数
**  入口参数: n:延时值;
**  返回结果: None
***********************************************************/
void delay(uint n)
{
  uint i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}

/***********************************************************
**  函数名称: Delay
**  实现功能: 约 10_ms 延时函数
**  入口参数: n:需要延时的 10ms 数;
**  返回结果: None
***********************************************************/
void Delay(uint n)
{
  uint i,j,k;
  for(i=0;i<n;i++)
    for(j=0;j<100;j++)
      for(k=0;k<100;k++)
        ;
}

/***********************************************************
**  函数名称: LEDPortInit
**  实现功能: 初始化 LED_D8_D9(P2_0.P1_1)
**  入口参数: None
**  返回结果: None
***********************************************************/
void LEDPortInit(void)
{
  P1SEL &= ~0X02;
  P2SEL &= ~0X01;

  P1DIR |= 0X02;
  P2DIR |= 0X01;

  CLR_LED_D8;
  CLR_LED_D9;
}

/***********************************************************
**  函数名称: GetCh08bitADC
**  实现功能: 获取 ADC 通道0 的8位 ADC 输入值
**  入口参数: None
**  返回结果: 1 Byte ADC值
***********************************************************/
uint8 GetCh08bitADC(void)
{
    uint8 v = 0;
    ADCCFG = 0x01;
    ADCCON1 = 0x33;
    ADCCON2 = 0xB0;
    ADCCON1 |= 0x40;
    while(!(ADCCON1 & 0x80));
    v = ADCL;
    v = ADCH;
    return(v);
}

/***********************************************************
**  函数名称: SetIOInput
**  实现功能: 设置端口为三态输入(不启用内部上下拉电阻)
**  入口参数: group:Port
**            bit:Bit in Port
**  返回结果: None
***********************************************************/
// pull: 0 - disable, 1 - pulldown, 2 - pullup
void SetIOInput(uint8 group, uint8 bit)
{
   switch(group)
   {
   case 0: P0DIR &= ~(1 << bit); P0SEL &= ~(1 << bit); P0INP |=(1 << bit); break;
   case 1: P1DIR &= ~(1 << bit); P1SEL &= ~(1 << bit); P1INP |=(1 << bit); break;
   case 2: P2DIR &= ~(1 << bit); P2SEL &= ~(1 << bit); P2INP |=(1 << bit); break;
   }
}

/***********************************************************
**  函数名称: SetIOOutput
**  实现功能: 设置端口为通用输出IO口
**  入口参数: group:Port
**            bit:Bit in Port
**  返回结果: None
***********************************************************/
void SetIOOutput(uint8 group, uint8 bit)
{
   switch(group)
   {
   case 0: P0DIR |= (1 << bit); P0SEL &= ~(1 << bit); break;
   case 1: P1DIR |= (1 << bit); P1SEL &= ~(1 << bit); break;
   case 2: P2DIR |= (1 << bit); P2SEL &= ~(1 << bit); break;
   }
}

/***********************************************************
**  函数名称: GetIOLevel
**  实现功能: 获取对应端口上的输入电平
**  入口参数: group:Port
**            bit:Bit in Port
**  返回结果:  1 Byte(1 :输入为高电平; 0 :输入为低电平;)
***********************************************************/
uint8 GetIOLevel(uint8 group, uint8 bit)
{
    switch(group)
    {
    case 0: return !!(P0 & (1 << bit));
    case 1: return !!(P1 & (1 << bit));
    case 2: return !!(P2 & (1 << bit));
    }
    return 0;
}

/***********************************************************
**  函数名称: SetIOLevel
**  实现功能: 设置IO口输出电平
**  入口参数: group:Port
**            bit:Bit in Port
**            value:(1 :输出高电平; 0 :输出低电平;)
**  返回结果: None
***********************************************************/
void SetIOLevel(uint8 group, uint8 bit, uint8 value)
{
    switch(group)
    {
    case 0:
        if(value)
          P0 |= (1 << bit);
        else
          P0 &=~(1 << bit);
        break;
    case 1:
        if(value)
          P1 |= (1 << bit);
        else
          P1 &=~(1 << bit);
        break;
    case 2:
        if(value)
          P2 |= (1 << bit);
        else
          P2 &=~(1 << bit);
        break;
    }
}