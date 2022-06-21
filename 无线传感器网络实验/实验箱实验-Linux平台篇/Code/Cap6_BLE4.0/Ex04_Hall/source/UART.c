#include "UART.h"
/***************************************************************************
    * Configure UART
    *
    */

void Init_UART0(BaudSel_t baud,uint8 PERCFG_U0CFG_ALT)
{
    // Initialise UART protocol (start/stop bit, data bits, parity, etc.):
    // 1bit start/stop 8bit data no parity no flow
    // USART mode = UART (U0CSR.MODE = 1).

    //PERCF_U0CFG  select the UART 0 Alternative Location
    PERCFG = (PERCFG & ~PERCFG_U0CFG) | PERCFG_U0CFG_ALT;
    if(PERCFG_U0CFG_ALT == PERCFG_U0CFG_ALT1)
      P0SEL |= BIT5 | BIT4 | BIT3 | BIT2;
    else if(PERCFG_U0CFG_ALT == PERCFG_U0CFG_ALT2)
      P1SEL |= BIT5 | BIT4 | BIT3 | BIT2;

    U0CSR |= U0CSR_MODE;
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
}

/***********************************************************
**  函数名称: UART0_Send
**  实现功能: UART0 发送数据
**  入口参数: pData:待发送数据区首地址
**            len:待发送数据的字节数
**  返回结果: None
***********************************************************/
void UART0_Send( char* pData,int len )
{
  int i;
  for(i=0;i<len;i++)
  {
    //填写发送内容
    U0DBUF = *pData++;
    //等待当前字节发送结束
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
  UART0_Send(cData, 5);
  //UART0_Send("\n", sizeof("\n"));
  //return cData;
}
