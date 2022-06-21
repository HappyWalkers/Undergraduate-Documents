
# include <ioCC2530.h>

#define uint unsigned int

#define LED_D9  P1_1
//��� WDT �ķ����ǣ����� WDCTL �ĸ�4λд 5����дA.
#define CLR_WDT_TIMER { WDCTL = 0X58; WDCTL = 0XA8; }

void Init_IO(void)
{
  P1DIR = 0x02;
  LED_D9 = 1;
}

void Init_Watchdog(void)
{
  WDCTL = 0x00;
  //ʱ����һ�룬���Ź�ģʽ
  WDCTL |= 0x08;
  //�������Ź�
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
  //��ʼ��ϵͳʱ�ӡ�
  Init_Clock();
  //��ʼ�� LED_D9�˿ڡ�
  Init_IO();
  //��ʼ�����Ź���ʱ����
  Init_Watchdog();

  Delay();
  LED_D9 = 0;
  while(1)
  {
    //ι��ָ������ϵͳ����λ��LED�� D9 ����˸��
    //CLR_WDT_TIMER;
  }	
}
