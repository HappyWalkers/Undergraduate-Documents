#include <ioCC2530.h>

void main(void)
{
  P1SEL &= ~0X02;   //ͨ��IO�ڹ���
  P1DIR |= 0X02;    //���
  while(1)
  {
    P1_1 = 0;       //����͵�ƽ��
  }
}