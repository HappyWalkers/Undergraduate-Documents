#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "string.h"
#include "sdram.h"
#include "malloc.h"
#include "w25qxx.h"
#include "ff.h"
#include "exfuns.h"
#include "string.h"
#include "sdio_sdcard.h"
#include "fontupd.h"
#include "text.h"
/************************************************
 ALIENTEK ������STM32F429������ʵ��42
 ������ʾʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
    
int main(void)
{	
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];                    //gbk��
	u8 key,t;
	u8 curtainFlag;
	
	HAL_Init();                     //��ʼ��HAL��   
	Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
	delay_init(180);                //��ʼ����ʱ����
	uart_init(115200);              //��ʼ��USART
	LED_Init();                     //��ʼ��LED 
	KEY_Init();                     //��ʼ������
	SDRAM_Init();                   //SDRAM��ʼ��
	LCD_Init();                     //LCD��ʼ��
	W25QXX_Init();				    //��ʼ��W25Q256
	my_mem_init(SRAMIN);            //��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);            //��ʼ���ⲿSDRAM�ڴ��
	my_mem_init(SRAMCCM);           //��ʼ���ڲ�CCM�ڴ��
	exfuns_init();		            //Ϊfatfs��ر��������ڴ�  
	f_mount(fs[0],"0:",1);          //����SD�� 
	f_mount(fs[1],"1:",1);          //����SPI FLASH. 
	font_init();
	//0Ϊ�رմ�����1��֮
	curtainFlag=0;
	POINT_COLOR=RED; 
	while(1)
	{
		t=200;
		while(t--)//��ʱ,ͬʱɨ�谴��
		{
			delay_ms(1);
			key=KEY_Scan(0);
			if(key==KEY0_PRES){}
			if(key==KEY1_PRES){
				if(curtainFlag==0){
					LED0=!LED0;
					curtainFlag=1;
					Show_Str(30,284,200,24,"�����Ѵ򿪣�",24,0);
				}else{
					LED0=!LED0;
					curtainFlag=0;
					Show_Str(30,284,200,24,"�����ѹرգ�",24,0);
				}
			} 
		}		
	} 
}
