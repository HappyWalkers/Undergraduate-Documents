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
 ALIENTEK 阿波罗STM32F429开发板实验42
 汉字显示实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com  
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
    
int main(void)
{	
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];                    //gbk码
	u8 key,t;
	u8 curtainFlag;
	
	HAL_Init();                     //初始化HAL库   
	Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
	delay_init(180);                //初始化延时函数
	uart_init(115200);              //初始化USART
	LED_Init();                     //初始化LED 
	KEY_Init();                     //初始化按键
	SDRAM_Init();                   //SDRAM初始化
	LCD_Init();                     //LCD初始化
	W25QXX_Init();				    //初始化W25Q256
	my_mem_init(SRAMIN);            //初始化内部内存池
	my_mem_init(SRAMEX);            //初始化外部SDRAM内存池
	my_mem_init(SRAMCCM);           //初始化内部CCM内存池
	exfuns_init();		            //为fatfs相关变量申请内存  
	f_mount(fs[0],"0:",1);          //挂载SD卡 
	f_mount(fs[1],"1:",1);          //挂载SPI FLASH. 
	font_init();
	//0为关闭窗帘，1反之
	curtainFlag=0;
	POINT_COLOR=RED; 
	while(1)
	{
		t=200;
		while(t--)//延时,同时扫描按键
		{
			delay_ms(1);
			key=KEY_Scan(0);
			if(key==KEY0_PRES){}
			if(key==KEY1_PRES){
				if(curtainFlag==0){
					LED0=!LED0;
					curtainFlag=1;
					Show_Str(30,284,200,24,"窗帘已打开！",24,0);
				}else{
					LED0=!LED0;
					curtainFlag=0;
					Show_Str(30,284,200,24,"窗帘已关闭！",24,0);
				}
			} 
		}		
	} 
}
