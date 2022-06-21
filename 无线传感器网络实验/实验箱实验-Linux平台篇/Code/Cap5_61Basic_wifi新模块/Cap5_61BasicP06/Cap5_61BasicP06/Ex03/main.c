//main.c

#include "SPCE061A.h"
#include "led.h"
#include "adc.h"
void delay();
int main()
{
	unsigned char data;	 
	unsigned int Result;	 
	INIT_LED();						// led端口初始化
	ADC_Init();						// ADC初始化
	while(1)
	{
		Result = Get_ADC_Data();
		data = (Result>>2)&0xFF;			// 10位ADC结果 转成8位
		LED_Printf(data,BYTE_5);
		//delay();
	}
	return 0;
}

void delay()
{
	unsigned int j;
	
	for(j=0;j<1000;j++);
		
}
