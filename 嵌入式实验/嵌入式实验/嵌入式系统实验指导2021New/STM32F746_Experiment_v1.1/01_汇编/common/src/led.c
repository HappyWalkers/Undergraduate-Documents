#include "def.h"
#include "option.h"
#include "2440addr.h"
/****************************************************
LED TEST
****************************************************/
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"  


Led_test(void)
{
	U8 i=0;
	unsigned int ledtab[5]={0x7de,0x79e,0x69e,0x29e,0xffe};
	Uart_Printf("\nLED Test, press ESC key to exit !\n");	

	rGPBCON &=~((3<<10)|(3<<12)|(3<<16)|(3<<20)) ; //GPB5,6,8,10 set OutPut
	rGPBCON |=(1<<10)|(1<<12)|(1<<16)|(1<<20);
	rGPBUP &=(0<5)|(0<6)|(0<8)|(0<10);
	

	while(1)
	{
		rGPBDAT=ledtab[i++];
	    Delay(400);
	    if(i==5)
	 	i=0;
		if ( Uart_GetKey() == ESC_KEY ) break;
		
	}
}