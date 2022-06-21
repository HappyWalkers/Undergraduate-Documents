#include "UART.h"
#include "Basic.h"
void LEDPortInit(void)
{
  P1SEL &= ~0X02;
  P2SEL &= ~0X01;

  P1DIR |= 0X02;
  P2DIR |= 0X01;

  CLR_LED_D8;
  CLR_LED_D9;
}
void UART0_Init(BaudSel baud)
{
  CLKCONCMD &= ~0X40;             //晶振
  while(!(SLEEPSTA & 0X40))
    ;                             //等待晶振稳定
  CLKCONCMD &= ~0X47;             //TICHSPD128分频，CLKSPD不分频
  SLEEPCMD |= 0X04; 		  //关闭不用的RC振荡器

  PERCFG = 0X00;		  //位置1 P0口
  P0SEL |= 0X0C;		  //P0用作串口

  U0CSR |= 0X80;		  //UART方式
  switch(baud)
  {
    case BAUD_2400:      U0GCR |= 6;     U0BAUD |= 59;    break;
    case BAUD_4800:      U0GCR |= 7;     U0BAUD |= 59;    break;
    case BAUD_9600:      U0GCR |= 8;     U0BAUD |= 59;    break;
    case BAUD_14400:     U0GCR |= 8;     U0BAUD |= 216;   break;
    case BAUD_19200:     U0GCR |= 9;     U0BAUD |= 59;    break;
    case BAUD_28800:     U0GCR |= 9;     U0BAUD |= 216;   break;
    case BAUD_38400:     U0GCR |= 10;    U0BAUD |= 59;    break;
    case BAUD_57600:     U0GCR |= 10;    U0BAUD |= 216;   break;
    case BAUD_76800:     U0GCR |= 11;    U0BAUD |= 59;    break;
    case BAUD_115200:    U0GCR |= 11;    U0BAUD |= 216;   break;
    case BAUD_230400:    U0GCR |= 12;    U0BAUD |= 216;   break;
    default         :    U0GCR |= 11;    U0BAUD |= 216;   break; //BAUD_115200;
  }

  UTX0IF = 0;
  U0CSR |= 0X40;		  //允许接收
  IEN0 |= 0X84;			  //开总中断，接收中断

}
void SetIOInput(uint8 group, uint8 bit)
{
   switch(group)
   {
   case 0: P0DIR &= ~(1 << bit); P0SEL &= ~(1 << bit); P0INP |=(1 << bit); break;
   case 1: P1DIR &= ~(1 << bit); P1SEL &= ~(1 << bit); P1INP |=(1 << bit); break;
   case 2: P2DIR &= ~(1 << bit); P2SEL &= ~(1 << bit); P2INP |=(1 << bit); break;
   }
}
void Delay(uint n)
{
  uint i,j,k;
  for(i=0;i<n;i++)
    for(j=0;j<100;j++)
      for(k=0;k<100;k++)
        ;
}
void UART0_Dis_uNum(uint16 uValue )
{
  uint8 i;
  char cData[5] = {'0','0','0','0','0'};

  cData[0] = uValue % 100000 / 10000 + '0';
  cData[1] = uValue % 10000 / 1000 + '0';
  cData[2] = uValue % 1000 / 100 + '0';
  cData[3] = uValue % 100 / 10 + '0';
  cData[4] = uValue % 10 / 1 + '0';
  if(0 != uValue )
  {
    for( i=0; i<5; i++)
    {
      if('0' != cData[i] )
        break;
      if('0' == cData[i] )
        cData[i] = ' ';
    }
  }
  else if(0 == uValue )
  {
    for( i=0; i<4; i++)
    {
        cData[i] = ' ';
    }
  }
  //数字和其他输出内容前后都有一个空格间距
  UART0_Send(" ", 1);
  UART0_Send(cData, 5);
  UART0_Send(" ", 1);
}
void delay(uint n)
{
  uint i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}
void UART0_Send(char *Data,int len)
{
  int i;
  for(i=0;i<len;i++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0)
      ;
    UTX0IF = 0;
  }
}
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
void main(){
    uint8 SensorVel;
    LEDPortInit();
    UART0_Init(BAUD_115200);
    SetIOInput(0,0);
    while(1){
      SensorVel=GetIOLevel(0,0);
      UART0_Send( "Rain Sensor:", sizeof("Rain Sensor:")-1 );
      UART0_Dis_uNum(SensorVel);
      if(0 == SensorVel)
        UART0_Send( "Sunny", sizeof("Sunny")-1 );
      else if(1 == SensorVel)
        UART0_Send( "Raining!", sizeof("Raining!")-1 );
      UART0_Send( "\r\n", sizeof("\r\n")-1 );

    //运行时LED 指示灯闪烁
      SET_LED_D8;
      Delay(5);
      CLR_LED_D8;
      Delay(120);
    }
}