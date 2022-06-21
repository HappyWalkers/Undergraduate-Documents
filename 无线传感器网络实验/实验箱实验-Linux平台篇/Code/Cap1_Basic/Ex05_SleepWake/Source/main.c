#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char
#define DELAY 10000

//小灯控端口定义
#define RLED P2_0
#define YLED P1_1

void Delay(void);
void Init_IO_AND_LED(void);
void PowerMode(uchar sel);

/****************************************************************
*函数功能：延时						
*入口参数：无							
*返回值  ：无							
*说  明	：可在宏定义中改变延时长度			
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
*函数功能：初始化电源					
*入口参数：para1,para2,para3,para4			
*返回值	：无						
*说  明	：para1,模式选择						
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
		PCON = 0x01;//睡眠
	}
	else
	{
	    PCON = 0x00;//唤醒
	}
}

/****************************************************************
*	函数功能：初始化I/O,控制LED							
*	入口参数：无						
*	返回值	：无						
*	说  明	：初始化完成后关灯				
****************************************************************/
void Init_IO_AND_LED(void)
{
    P2DIR |= 0x01;
    P1DIR = 0X03;
    RLED = 1;
    YLED = 1;

    P0SEL &= ~0X30;
    P0DIR &= ~0X30;
    P0INP  &= ~0X30;//有上拉、下拉
    P2INP &= ~0X40; //选择上拉

    P0IEN |= 0X30;   //P12 P13
    PICTL |= 0X02;   //下降沿

    EA = 1;
    IEN1 |= 0X20;  //P1IE = 1;

    P0IFG |= 0x00;   //P12 P13
};
/****************************************************************
*	函数功能：主函数					
*	入口参数：					
*	返回值	：无						
*	说  明	：10次绿色LED闪烁后进入睡眠状态			
****************************************************************/
void main()
{
  uchar count = 0;
  Init_IO_AND_LED();

  RLED = 0 ;       //开红色LED，系统工作指示
  Delay();        //延时
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
      //10次闪烁后进入睡眠状态
    }

    //Delay();
    Delay();
    //延时函数无形参，只能通过改变系统时钟频率
    //来改变小灯的闪烁频率
  };
}

/*****************************************
//唤醒系统
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
