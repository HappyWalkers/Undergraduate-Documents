
#include "Basic.h"

extern char TxBuf[30];

void delay(uint n)
{
  uint i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}

extern char TxBuf[30];

void Delay(uint n)
{
  uint i,j,k;
  for(i=0;i<n;i++)
    for(j=0;j<100;j++)
      for(k=0;k<100;k++)
        ;
}

void PortInit(void)
{
  P0SEL = 0X00;
  P0DIR = 0XFF;

  P1SEL = 0X00;
  P1DIR = 0XFF;

  P2SEL &= ~0X01;
  P2DIR |= 0X01;


  P0 = 0XFF;
  P1 = 0XFF;
  P2 &= ~0X01;
}

void PortTest_FlashAll(uint8 num)
{
  uint8 Num, i;
  Num = 2 * num;
  for(i=0; i<Num; i++)
  {
    P0 ^= 0XFF;
    P1 ^= 0XFF;

    delay(50000);
    delay(50000);
    delay(50000);
    delay(50000);
  }
}

void PortTest_FlowLED(uint8 num)
{
  uint8 i, j;
  for(i=0; i<num; i++)
  {
    for(j=0; j<8; j++)
    {
      if((2 == j) || (3 == j))
        continue;
      P0 ^= (0X01<<j);
      delay(50000);

      P0 ^= (0X01<<j);
      delay(50000);
    }
    for(j=0; j<8; j++)
    {
      P1 ^= (0X80>>j);
      delay(50000);

      P1 ^= (0X80>>j);
      delay(50000);
    }
  }
}