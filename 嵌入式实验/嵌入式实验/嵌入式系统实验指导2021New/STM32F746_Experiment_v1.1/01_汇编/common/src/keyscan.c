/**************************************************************
Key Scan
**************************************************************/

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 

U8 Key_Scan_isr( void )
{
	if     ( (rGPFDAT&(1<< 0)) == 0 )		return 1 ;
	else if( (rGPFDAT&(1<< 2)) == 0 )		return 2 ;
	else return 0xff;
}

U8 Key_Scan( void )
{
	if     ( (rGPFDAT&(1<< 4)) == 0 )		return 4 ;
	else if( (rGPFDAT&(1<< 3)) == 0 )		return 3 ;
	
	else return 0xff;
}

static void __irq Key_ISR(void)
{
	U8 key;
	U32 r;

	EnterCritical(&r);

	if(rINTPND==BIT_EINT0) {
		ClearPending(BIT_EINT0);
	}
	if(rINTPND==BIT_EINT2) {
		ClearPending(BIT_EINT2);
	}

	key=Key_Scan_isr();
	if( key != 0xff )
	Uart_Printf( "Interrupt occur... Key%d is pressed!\n", key ) ;

	ExitCritical(&r);
}

void KeyScan_Test(void)
{
	U8 key;
	Uart_Printf("\nKey Scan Test, press ESC key to exit !\n");	

	rGPFCON &=~((3<<0)|(3<<4)|(3<<6)|(3<<8)) ;
	rGPFCON |= ((2<<0)|(2<<4)|(2<<6)|(2<<8)) ;		//GPF2,0 set EINT
	
//	rGPBCON &=~((3<<10)|(3<<12)|(3<<14)) ; //GPB5,6,7 set OutPut
	
	rEXTINT0 &= ~(7|(7<<8));	
	rEXTINT0 |= (2|(2<<8));	//set eint0,2,3 falling edge int

	ClearPending(BIT_EINT0|BIT_EINT2);
	pISR_EINT0 = pISR_EINT2 = (U32)Key_ISR;
	EnableIrq(BIT_EINT0|BIT_EINT2);	


	while(1)
	{
		key = Key_Scan();
		if( key != 0xff )
		{
			Uart_Printf( "Key%d is pressed!\n", key ) ;
			Delay(200);
		}
		if ( Uart_GetKey() == ESC_KEY ) break;
	}

	//while( Uart_GetKey() != ESC_KEY ) ;
	DisableIrq(BIT_EINT0|BIT_EINT2);	
}
