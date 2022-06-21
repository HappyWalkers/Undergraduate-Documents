#include "timer.h"
static unsigned int timer = 0;
void init_timer_1(void)
{
   T1CTL = 0x0d;
   INIT_LED();
}

void glint_led(unsigned char led)
{
  unsigned char glint = 0;

   if((T1STAT & 0x20) > 0)
   {
      T1STAT &= ~0x20;                //清溢出标志
      timer ++;
   }

   if(timer < GLINT_TIME)
   {
     glint |= led;
     LEDprintf(glint,BYTE_5);
   }
   else
   {
     if(timer > 2*GLINT_TIME)
     timer = 0;
     glint &= ~led;
     LEDprintf(glint,BYTE_5);
   }
}



