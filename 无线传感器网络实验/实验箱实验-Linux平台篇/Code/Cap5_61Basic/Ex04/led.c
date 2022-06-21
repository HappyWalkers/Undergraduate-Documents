#include "led.h"

/*****************************************************************
【API 格式】：void INIT_LED(void)
【功能说明】：led端口初始化；
【参	数】：无；
【返 回 值】：无；
【使用举例】：INIT_LED();
【备    注】: 
*****************************************************************/
void INIT_LED(void)
{
	*P_IOA_Dir = 0x8700;  //*P_IOB_Data = 0x00;
	*P_IOA_Attrib = 0x8700;  //*P_IOB_Dir = 0x87;
	*P_IOA_Data = 0x00;  //*P_IOB_Attrib = 0x87;	
//  P1SEL &= ~0xFF;
//  P1DIR |= 0xFF;
//  P1 = 0;
}
/*****************************************************************
【API 格式】：void LED_Printf(unsigned char data,unsigned char byte)
【功能说明】：点亮8路LED，通过74HC595发送
【参    数】：unsigned char data,led显示的数值；
			  unsigned char byte 端选，此处设置为BYTE_5
【返 回 值】：无；
【使用举例】：LED_Printf(1,BYTE_5);
【备    注】: 
*****************************************************************/
void LED_Printf(unsigned char data,unsigned char byte)
{
  unsigned char bits = 0;
  unsigned char get_bit = 0x80;
  *P_IOA_Data |= byte;  //*P_IOB_Data |= byte;
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






