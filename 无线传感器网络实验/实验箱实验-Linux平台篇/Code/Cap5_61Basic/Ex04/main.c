//1.	通编程要求：编写一个C语言程序，实现Timer A定时器的中断功能。
//2.	实现功能： 打开并设置TimerA定时器，并且开TimerA的IRQ1中断，当有TimerA的IRQ1中断请求时，响应相应的中断服务程序，在中断服务中翻转I/O端口输出电平，以控制接在I/O端口的发光二极管（LED）的亮灭。
//3.	实验现象：TimerA定时长度为2s，在8个LED的负极设置为低电平的前提下，当进入TimerA的IRQ1中断后，翻转8路发光二极管的显示。 
//

#include "SPCE061A.h"
#include "led.h"

unsigned char g_ucLed_Data;	 
void TimerA_Init();


int main()
{
	__asm("IRQ OFF");
	INIT_LED();								// led端口初始化
	TimerA_Init();					   		// TimerA初始化
	__asm("IRQ ON");
	g_ucLed_Data = 0;
	while(1)
	{
		LED_Printf(g_ucLed_Data,BYTE_5);    //刷新LED显示
		*P_Watchdog_Clear = 0x0001;			// 清看门狗

	}
	return 0;
}

/*****************************************************************
【API 格式】：void TimerA_Init(void)
【功能说明】：TimerA初始化；
【参	数】：无；
【返 回 值】：无；
【使用举例】：TimerA_Init();
【备    注】: 
*****************************************************************/
void TimerA_Init()
{
	*P_TimerA_Ctrl = (1<<3)|(5);		//选择低频2Hz clOckA 1,clockB 1024HZ
	*P_TimerA_Data = 0xF7FF;			//设置计数初值 （10000H-F7FFH）*1/1024=2s。 0xF800
	*P_INT_Ctrl |= (1<<12);    			// enable IRQ1_TMA
}
