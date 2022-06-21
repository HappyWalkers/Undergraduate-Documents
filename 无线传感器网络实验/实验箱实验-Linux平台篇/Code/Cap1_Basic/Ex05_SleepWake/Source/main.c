#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char
#define DELAY 10000

//С�ƿض˿ڶ���
#define RLED P2_0
#define YLED P1_1

void Delay(void);
void Init_IO_AND_LED(void);
void PowerMode(uchar sel);

/****************************************************************
*�������ܣ���ʱ						
*��ڲ�������							
*����ֵ  ����							
*˵  ��	�����ں궨���иı���ʱ����			
****************************************************************/
void Delay(void)
{
	uint tt;
	for(tt = 0;tt<DELAY;tt++);
	for(tt = 0;tt<DELAY;tt++);
	for(tt = 0;tt<DELAY;tt++);
	for(tt = 0;tt<DELAY;tt++);
	for(tt = 0;tt<DELAY;tt++);
}

/****************************************************************
*�������ܣ���ʼ����Դ					
*��ڲ�����para1,para2,para3,para4			
*����ֵ	����						
*˵  ��	��para1,ģʽѡ��						
*																*
* para1  0 	1	2	3											*
* mode 	PM0	PM1	PM2	PM3											*
*																*
****************************************************************/
void PowerMode(uchar sel)
{
	uchar i,j;
	i = sel;
	if(sel<4)
	{
		SLEEPCMD &= 0xfc;
		SLEEPCMD |= i;
		for(j=0;j<4;j++);
		PCON = 0x01;//˯��
	}
	else
	{
	    PCON = 0x00;//����
	}
}

/****************************************************************
*	�������ܣ���ʼ��I/O,����LED							
*	��ڲ�������						
*	����ֵ	����						
*	˵  ��	����ʼ����ɺ�ص�				
****************************************************************/
void Init_IO_AND_LED(void)
{
    P2DIR |= 0x01;
    P1DIR = 0X03;
    RLED = 1;
    YLED = 1;

    P0SEL &= ~0X30;
    P0DIR &= ~0X30;
    P0INP  &= ~0X30;//������������
    P2INP &= ~0X40; //ѡ������

    P0IEN |= 0X30;   //P12 P13
    PICTL |= 0X02;   //�½���

    EA = 1;
    IEN1 |= 0X20;  //P1IE = 1;

    P0IFG |= 0x00;   //P12 P13
};
/****************************************************************
*	�������ܣ�������					
*	��ڲ�����					
*	����ֵ	����						
*	˵  ��	��10����ɫLED��˸�����˯��״̬			
****************************************************************/
void main()
{
  uchar count = 0;
  Init_IO_AND_LED();

  RLED = 0 ;       //����ɫLED��ϵͳ����ָʾ
  Delay();        //��ʱ
  Delay();
  Delay();
  Delay();

  while(1)
  {
    YLED = !YLED;
    RLED = 0;
    count++;
    if(count >= 20)
    {
      count = 0;
      RLED = 1;
      PowerMode(3);
      //10����˸�����˯��״̬
    }

    //Delay();
    Delay();
    //��ʱ�������βΣ�ֻ��ͨ���ı�ϵͳʱ��Ƶ��
    //���ı�С�Ƶ���˸Ƶ��
  };
}

/*****************************************
//����ϵͳ
*****************************************/
#pragma vector = P0INT_VECTOR
 __interrupt void P0_ISR(void)
 {
        if(P0IFG>0)
        {
          P0IFG = 0;
        }
        P0IF = 0;
        PowerMode(7);
 }
