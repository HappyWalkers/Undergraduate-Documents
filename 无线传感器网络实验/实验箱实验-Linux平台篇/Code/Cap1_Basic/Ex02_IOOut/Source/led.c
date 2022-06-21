#include "led.h"

void INIT_LED(void)
{
  P1SEL &= ~0xFF;
  P1DIR |= 0xFF;
  P1 = 0;
}
void LEDprintf(unsigned char data,unsigned char byte)
{
  unsigned char bits = 0;
  unsigned char get_bit = 0x80;
  P1 |= byte;
  RCK = LOW;
  SRCK = LOW;
  for(bits = 8;bits > 0;bits --)
  {
    if(data & get_bit)
      SER = 1;
    else
      SER = 0;
    SRCK = HIGH;
    get_bit >>= 1;
    SRCK = LOW;
  }
  RCK = HIGH;
}






