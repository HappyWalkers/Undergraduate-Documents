/*********************************************************************************************
* File name	: sys_init.c
* Author	: embest
* Descript	: Embest s3ceb2410 system initialization. 
* History
*			R.X.Huang, Programming start, March 12, 2005
*********************************************************************************************/

/*------------------------------------------------------------------------------------------*/
/*	 								include files						 				    */
/*------------------------------------------------------------------------------------------*/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "2410lib.h"
/*------------------------------------------------------------------------------------------*/
/*	 								global variable						 				    */
/*------------------------------------------------------------------------------------------*/
int nCNT;								// control sign

/*------------------------------------------------------------------------------------------*/
/*	 								function declare					 				    */
/*------------------------------------------------------------------------------------------*/
// for debugging
void break_point(void);
void debug_undef(void);
void debug_swi(void);
void debug_abort(void);
void debug_fiq(void);

/*********************************************************************************************
* name:		break_point, debug_xxxx
* func:		states the exception has occured.
* para:		none
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void break_point(void)
{
	int i;	
	char m = 200;
	uart_printf("!!!Enter break point.");	

	rGPFCON=0x5500;                  //PORTF7/6/5/4 OUTPUT
	rGPFUP=0;                        //PULL-UP ENABLE 
	while(m) {
		rGPFDAT=0;
		beep(1);
		for(i=0;i<20000;i++);
		rGPFDAT=0xF0;
		beep(0);
		for(i=0;i<20000;i++);		
		m--;
	}
}

void debug_undef(void)
{
	uart_printf("!!!Enter UNDEFINED exception. %d\r\n", nCNT+=1);	
	break_point();
}

void debug_swi(void)
{
	uart_printf("!!!Enter SWI exception. %d\r\n", nCNT+=1);	
	break_point();
}

void debug_abort_d(void)
{
	uart_printf("!!!Enter Data ABORT exception. %d\r\n", nCNT+=1);	
	break_point();
}

void debug_abort_p(void)
{
    uart_printf("!!!Enter Prefetch ABORT exception. %d\r\n", nCNT+=1);	
    break_point();
}

void debug_fiq(void)
{
	uart_printf("!!!Enter FIQ exception. %d\r\n", nCNT+=1);	
	break_point();
}

/*********************************************************************************************
* name:		interrupts_init
* func:		Initialze interrupts and set interrupt vector routine
* para:		none
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void interrupts_init(void)
{
    rINTMOD     = 0x0;                     // All=IRQ mode
    rSRCPND     = rSRCPND;                 // clear all interrupt
    rINTPND     = rINTPND;                 // clear all interrupt
    rINTMSK     = BIT_ALLMSK;              // All interrupt is masked.
    rINTSUBMSK  = BIT_SUB_ALLMSK;          // All sub-interrupt is masked.

// External interrupt will be falling edge triggered. 
    rEXTINT0 = 0x22222222;    // EINT[7:0]
    rEXTINT1 = 0x22222222;    // EINT[15:8]
    rEXTINT2 = 0x22222222;    // EINT[23:16]

//	pISR_RESET                             //reserved
	pISR_UNDEF     	= (unsigned) debug_undef;
	pISR_SWI       	= (unsigned) debug_swi;
	pISR_PABORT    	= (unsigned) debug_abort_d;
	pISR_DABORT    	= (unsigned) debug_abort_d;
//	pISR_RESERVED                          //not used
//	pISR_IRQ       	= (unsigned) 0;        //reserved
	pISR_FIQ       	= (unsigned) debug_fiq;

	pISR_EINT0      = (unsigned) break_point;    
	pISR_EINT1     	= (unsigned) break_point;
	pISR_EINT2     	= (unsigned) break_point;
	pISR_EINT3     	= (unsigned) break_point;
	pISR_EINT4_7   	= (unsigned) break_point;
	pISR_EINT8_23  	= (unsigned) break_point;
	pISR_NOTUSED6  	= (unsigned) break_point;
	pISR_BAT_FLT   	= (unsigned) break_point;
	pISR_TICK      	= (unsigned) break_point;
	pISR_WDT       	= (unsigned) break_point;
	pISR_TIMER0    	= (unsigned) break_point;
	pISR_TIMER1    	= (unsigned) break_point;
	pISR_TIMER2    	= (unsigned) break_point;
	pISR_TIMER3    	= (unsigned) break_point;
	pISR_TIMER4    	= (unsigned) break_point;
	pISR_UART2     	= (unsigned) break_point;
	pISR_LCD       	= (unsigned) break_point;
	pISR_DMA0      	= (unsigned) break_point;
	pISR_DMA1      	= (unsigned) break_point;
	pISR_DMA2      	= (unsigned) break_point;
	pISR_DMA3      	= (unsigned) break_point;
	pISR_SDI       	= (unsigned) break_point;
	pISR_SPI0      	= (unsigned) break_point;
	pISR_UART1     	= (unsigned) break_point;
	pISR_NOTUSED24 	= (unsigned) break_point;
	pISR_USBD      	= (unsigned) break_point;
    pISR_USBH      	= (unsigned) break_point;
    pISR_IIC       	= (unsigned) break_point;
    pISR_UART0     	= (unsigned) break_point;
    pISR_SPI1      	= (unsigned) break_point;
    pISR_RTC       	= (unsigned) break_point;
    pISR_ADC       	= (unsigned) break_point;
    pISR_ADC       	= (unsigned) break_point;
                
}//interrupts_init

/*********************************************************************************************
* name:		sys_init
* func:		Initilaize interrupt, port and UART
* para:		none
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void sys_init()
{
//#ifdef DEBUG
//	MMU_DisableICache();
//#else
//	MMU_EnableICache();
//#endif
//	MMU_EnableDCache();
	//MMU_DisableDCache();

	change_clock_divider(1,1);					// 1:2:4
	change_value_MPLL(M_MDIV,M_PDIV,M_SDIV);	// Fin=12MHz FCLK=202.8MHz
	delay(0);									// adjust the delay count
	port_init();
	beep(1);
	interrupts_init();
	uart_init(PCLK, 115200, UART0);
	uart_init(PCLK, 115200, UART1);
#ifdef CLK124_200M
	change_value_MPLL(88,1,1);					// Fin=12MHz FCLK=192MHz
	uart_init(192000000/4, 115200, UART0);
	uart_init(192000000/4, 115200, UART1);
#endif
	
	uart_select(UART0);
	uart_printf ("\n boot success...\n\n");
	delay(500);
	beep(0);
}//sys_init

