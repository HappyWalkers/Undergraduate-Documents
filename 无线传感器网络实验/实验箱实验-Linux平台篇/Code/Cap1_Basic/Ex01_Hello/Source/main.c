#include <ioCC2530.h>

void main(void)
{
  P1SEL &= ~0X02;   //通用IO口功能
  P1DIR |= 0X02;    //输出
  while(1)
  {
    P1_1 = 0;       //输出低电平。
  }
}