
# include <ioCC2530.h>

#define uint unsigned int

#define LED_D9  P1_1
//清除 WDT 的方法是，先向 WDCTL 的高4位写 5，再写A.
#define CLR_WDT_TIMER { WDCTL = 0X58; WDCTL = 0XA8; }

void Init_IO(void)
{
  P1DIR = 0x02;
  LED_D9 = 1;
}

void Init_Watchdog(void)
{
  WDCTL = 0x00;
  //时间间隔一秒，看门狗模式
  WDCTL |= 0x08;
  //启动看门狗
}

void Init_Clock(void)
{
  CLKCONCMD = 0X00;
}

void Delay(void)
{
  uint n;
  for(n=50000;n>0;n--);
  for(n=50000;n>0;n--);
  for(n=50000;n>0;n--);
  for(n=50000;n>0;n--);
  for(n=50000;n>0;n--);
  for(n=50000;n>0;n--);
  for(n=50000;n>0;n--);
}

void main(void)
{
  //初始化系统时钟。
  Init_Clock();
  //初始化 LED_D9端口。
  Init_IO();
  //初始化看门狗定时器。
  Init_Watchdog();

  Delay();
  LED_D9 = 0;
  while(1)
  {
    //喂狗指令（加入后系统不复位，LED灯 D9 不闪烁）
    //CLR_WDT_TIMER;
  }	
}
