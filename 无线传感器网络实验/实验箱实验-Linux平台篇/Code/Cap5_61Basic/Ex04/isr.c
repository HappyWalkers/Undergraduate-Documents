//isr.c
#include "SPCE061A.h"

extern unsigned char g_ucLed_Data;	 

void BREAK(void) __attribute__ ((ISR));

void FIQ(void) __attribute__ ((ISR));

void IRQ0(void) __attribute__ ((ISR));

void IRQ1(void) __attribute__ ((ISR));

void IRQ2(void) __attribute__ ((ISR));

void IRQ3(void) __attribute__ ((ISR));

void IRQ4(void) __attribute__ ((ISR));

void IRQ5(void) __attribute__ ((ISR));

void IRQ6(void) __attribute__ ((ISR));

void IRQ7(void) __attribute__ ((ISR));




void BREAK(void)
{
	//add your code here

}

void FIQ(void)
{
	//add your code here

}

void IRQ0(void)
{
	//add your code here

}

void IRQ1(void)
{
	//add your code here
	*P_INT_Clear = 0x1000;    			// clear IRQ1_TMA
	g_ucLed_Data = ~g_ucLed_Data;
}

void IRQ2(void)
{
	//add your code here

}

void IRQ3(void)
{
	//add your code here

}

void IRQ4(void)
{
	//add your code here

}

void IRQ5(void)
{
	//add your code here

}

void IRQ6(void)
{
	//add your code here

}

void IRQ7(void)
{
	//add your code here

}
