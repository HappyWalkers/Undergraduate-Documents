/***************************************************************
学习unSP IDE集成开发环境，学习该环境下C语言程序的编写。
实现功能：从1到100进行累加，并把计算结果保存在变量Sum中。
实验现象：打开变量观察窗口观察变量Sum的变化，累加结束时变量Sum为5050（16进制表示为0x13BA）。
***************************************************************/
#include "SPCE061A.h"

int main()
{
	int Sum=0;
	unsigned char i;

	for(i=0;i<=100;i++)
		Sum += i;
	while(1)
	{
		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared
	}
}
