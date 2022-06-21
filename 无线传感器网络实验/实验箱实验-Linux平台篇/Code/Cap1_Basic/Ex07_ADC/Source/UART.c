#include "UART.h"

/***********************************************************
**  函数名称: UART0_Init
**  实现功能: 初始化 UART0
**  入口参数: baud:波特率设置;
**  返回结果: None
***********************************************************/
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

/***********************************************************
**  函数名称: UART0_Send
**  实现功能: UART0 发送数据
**  入口参数: Data:待发送数据区首地址
**            len:待发送数据的字节数
**  返回结果: None
***********************************************************/
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
/***********************************************************
**  函数名称: UART0_Dis_uNum
**  实现功能: UART0 以十进制方式显示 uint16 型数据
**  入口参数: uValue:需要显示的无符号型数据
**  返回结果: None
***********************************************************/
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

/***********************************************************
**  函数名称: UART0_Dis_fNum
**  实现功能: UART0 以十进制方式显示 float 型数据
**  入口参数: fValue:需要显示的浮点型数据
**  返回结果: None
***********************************************************/
void UART0_Dis_fNum(float fValue )
{
  uint16 uValue = (uint16)( 100 * fValue );
  char cData[5] = {'0','0','.','0','0'};

  cData[0] = uValue % 10000 / 1000 + '0';
  cData[1] = uValue % 1000 / 100 + '0';
  cData[2] = '.';
  cData[3] = uValue % 100 / 10 + '0';
  cData[4] = uValue % 10 / 1 + '0';

  //数字和其他输出内容前后都有一个空格间距
  UART0_Send(" ", 1);
  UART0_Send(cData, 5);
  UART0_Send(" ", 1);
}

/***********************************************************
**  函数名称: UART0_ISR
**  实现功能: UART0 接收中断处理函数
**  入口参数: None
**  返回结果: None
***********************************************************/
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
//    static char temp[1];
//    temp[0] = U0DBUF;
//    UART0_Send(temp, 1);
    URX0IF = 0;				//清中断标志
 }
