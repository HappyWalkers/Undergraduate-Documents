//main.c
/*****************************************************************************
编程要求：编写一段C 语言程序，实现端口IOA的输出操作。
2、实现功能：通过IOA口输出的数据控制 8 个发光二极管的亮灭。
3、实验现象8个发光二极管动态点亮和熄灭，并且循环显示，
*****************************************************************************/
#include "SPCE061A.h"
#include "led.h"

void delay();
int main()
{
	unsigned char data=0;	 
	//add your code here
	INIT_LED();
	while(1)
	{
		data++;
		LED_Printf(data,BYTE_5);        // 74HC595驱动
		
		delay();
		*P_Watchdog_Clear = 0x0001;	    // 清看门狗

	}
	return 0;
}

void delay()
{
	unsigned int j;
		for(j=0;j<10000;j++);
		
}
