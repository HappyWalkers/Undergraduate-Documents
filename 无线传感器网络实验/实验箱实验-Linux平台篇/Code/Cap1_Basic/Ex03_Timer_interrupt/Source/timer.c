#include "timer.h"
static unsigned int timer = 0;
void init_timer_1(void)
{
    INIT_LED();
    T1CTL = 0x0e;           // f = 32MHz / 128 = 250 000Hz, T = 4us;模模式,从0~T1CC0反复计数。
    T1CCTL0 = 0x44;         // Timer1通道0中断允许,比较匹配模式,比较比配时输出置位。
    T1CC0L = 0xc4 ;    // 先写T1CC0L,再写T1CC0H,T1CNT=0时更新。
    T1CC0H = 0x09 ;    // 2500 * 4us = 10 000us = 10ms;
    TIMIF |= 0x40;      // TIMIF.T1OVFIM Timer1溢出中断允许
    IEN1 |= 0x02;       // IEN1.T1IE Timer1总中断允许
    EA = 1;                 // 打开全局总中断
}

/***********************************************************
**  函数名称: T1_Handle
**  实现功能: Timer1 中断处理函数
**  入口参数: None
**  返回结果: None
***********************************************************/
#pragma vector = T1_VECTOR
    __interrupt void T1_Handle(void)
{
 static unsigned char glint = 0;
    timer ++;
       if(timer < GLINT_TIME)
   {
     glint |= 0x01;
     LEDprintf(glint,BYTE_5);
   }
   else
   {
     if(timer > 2*GLINT_TIME)
     timer = 0;
     glint &= ~0x01;
     LEDprintf(glint,BYTE_5);
   }
    T1STAT &= ~0x20;     // T1STAT.OVFIF 清除Timer1溢出中断标志
    T1STAT &= ~0x02;     // T1STAT.CH0IF 清除Timer1通道0中断标志
    IRCON &= ~0x02;      // IRCON.T1IF   清除Timer1总中断标志
}



