/*********************************************************************************************
* File name	: 2410lib.h
* Author	: embest
* Descript	: S3C2410 Define Address Register 
* History
*			R.X.Huang, Programming modify, March 12, 2005
*********************************************************************************************/

/*------------------------------------------------------------------------------------------*/
/*	 								include files						 				    */
/*------------------------------------------------------------------------------------------*/
#include "def.h"
#include "memcfg.h"
#include "option.h"
#include "register.h"
#include "2410addr.h"

#ifndef __2410lib_h__
#define __2410lib_h__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------*/
/*	 								constant define						 				    */
/*------------------------------------------------------------------------------------------*/
#define DOWNLOAD_ADDRESS _RAM_STARTADDRESS
#define DEBUG_OUT uart_printf

#define min(x1,x2) (((x1)<(x2))? (x1):(x2))
#define max(x1,x2) (((x1)>(x2))? (x1):(x2))

#define ONESEC0 (62500)				// 16us resolution, max 1.04 sec
#define ONESEC1 (31250)				// 32us resolution, max 2.09 sec
#define ONESEC2 (15625)				// 64us resolution, max 4.19 sec
#define ONESEC3 (7812)				//128us resolution, max 8.38 sec
#define ONESEC4 (PCLK/128/(0xff+1))	// @60Mhz, 128*4us resolution, max 32.53 sec

#define NULL 0
#define LCD   0xDD					// LCD symbol
#define UART0 0x0					// UART symbol
#define UART1 0x1
#define UART2 0xBB
//INT32T g_nTimeout;					// timeout value
//UINT32T g_nKeyPress;				// the SB1202/SB1203 press signal

#define EnterPWDN(clkcon) ((void (*)(int))0x20)(clkcon)
void StartPointAfterPowerOffWakeUp(void); // purnnamu:Mar.29.2002
void sys_init(void);
// 2410lib.c
void delay(int time);				// Watchdog Timer is used.
void beep(int nBeepStatus); 
//void *malloc_pt;//=Image_RW_Limit;
//void (*restart)(void);//=(void (*)(void))0x0;
//void (*run)(void);

//void * smalloc(unsigned nbyte); 
//void sfree(void *pt);

void port_init(void);
void uart_select(int ch);
void uart_txempty(int ch);
void uart_init(int nMainClk, int nBaud, int nChannel);
char uart_getch(void);
char uart_getkey(void);
int  uart_getintnum(void);
void uart_sendbyte(int data);
void uart_printf(char *fmt,...);
void uart_sendstring(char *pt);

void timer_start(int divider);		// Watchdog Timer is used.
int  timer_stop(void);				// Watchdog Timer is used.

void led_display(int data);

void change_value_MPLL(int m,int p,int s);
void change_clock_divider(int hdivn,int pdivn);
void ChangeUPllValue(int m,int p,int s);

#ifdef __cplusplus
}
#endif

#endif  //__2410lib_h__

