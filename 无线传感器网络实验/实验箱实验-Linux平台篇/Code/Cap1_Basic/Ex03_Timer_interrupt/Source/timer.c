#include "timer.h"
static unsigned int timer = 0;
void init_timer_1(void)
{
    INIT_LED();
    T1CTL = 0x0e;           // f = 32MHz / 128 = 250 000Hz, T = 4us;ģģʽ,��0~T1CC0����������
    T1CCTL0 = 0x44;         // Timer1ͨ��0�ж�����,�Ƚ�ƥ��ģʽ,�Ƚϱ���ʱ�����λ��
    T1CC0L = 0xc4 ;    // ��дT1CC0L,��дT1CC0H,T1CNT=0ʱ���¡�
    T1CC0H = 0x09 ;    // 2500 * 4us = 10 000us = 10ms;
    TIMIF |= 0x40;      // TIMIF.T1OVFIM Timer1����ж�����
    IEN1 |= 0x02;       // IEN1.T1IE Timer1���ж�����
    EA = 1;                 // ��ȫ�����ж�
}

/***********************************************************
**  ��������: T1_Handle
**  ʵ�ֹ���: Timer1 �жϴ�����
**  ��ڲ���: None
**  ���ؽ��: None
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
    T1STAT &= ~0x20;     // T1STAT.OVFIF ���Timer1����жϱ�־
    T1STAT &= ~0x02;     // T1STAT.CH0IF ���Timer1ͨ��0�жϱ�־
    IRCON &= ~0x02;      // IRCON.T1IF   ���Timer1���жϱ�־
}



