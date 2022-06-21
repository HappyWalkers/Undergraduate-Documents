/*********************************************************************************************
* File name	: 2410lib.c
* Author	: embest
* Descript	: s3c2410 function library 
* History
*			R.X.Huang, Programming modify, March 12, 2005
*********************************************************************************************/

/*------------------------------------------------------------------------------------------*/
/*	 								include files						 				    */
/*------------------------------------------------------------------------------------------*/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "2410lib.h"
#include "2410slib.h" 

/*------------------------------------------------------------------------------------------*/
/*	 								global variable						 				    */
/*------------------------------------------------------------------------------------------*/
//static int delayLoopCount = 400;
static int delayLoopCount = FCLK/10000/10;				// the default count value for delay 
unsigned int f_nWhichUart=0;							// UARTx

char Image$$RW_ZI$$ZI$$Limit[];
//extern char Image_RW_Limit[];
//void (*run)(void)=(void (*)(void))DOWNLOAD_ADDRESS;

/*********************************************************************************************
* name:		port_init
* func:		initialize io port for Embest teach kit ii
* para:		none
* ret:		none
* modify:	R.X.Huang, March 12, 2005, modify the port setting dedicate for Embest Arm Edu Kit
* comment:	
*********************************************************************************************/
void port_init(void)
{
    //CAUTION:Follow the configuration order for setting the ports. 
    // 1) setting control register (GPnCON)
    //    * (bitn) -- means this pin not use on circuit, and set as default function
    // 2) configure pull-up resistor (GPnUP)  
    // 3) setting value (GPnDAT)

    //32bit data bus configuration  
    //=== PORT A GROUP
    //Ports  : GPA22  GPA21  GPA20  GPA19  GPA18  GPA17  GPA16  GPA15  GPA14  GPA13  GPA12  
    //Signal : nFCE   GPA21  nFRE   nFWE   ALE    CLE    GPA16  nGCS4  nGCS3  nGCS2  nGCS1 
    //Setting: nFCE   Output nFRE   nFWE   ALE    CLE    Output nGCS4  nGCS3  nGCS2  nGCS1 
    //Binary : 1      *0      1,     1      1      1      *0,    1      1      1      1
    //----------------------------------------------------------------------------------------
    //Ports  : GPA11  GPA10   GPA9   GPA8   GPA7   GPA6   GPA5   GPA4   GPA3   GPA2   GPA1   GPA0
    //Signal : GPA11 ADDR25  ADDR24 ADDR23 ADDR22 ADDR21 ADDR20 ADDR19 ADDR18 ADDR17 ADDR16 ADDR0 
    //Binary : *0     1       1      1,     1      1      1      1,     1      1      1      1         
    rGPACON = 0x5ef7ff;

    //===* PORT B GROUP
    //Ports  : GPB10  GPB9   GPB8   GPB7   GPB6   GPB5    GPB4    GPB3   GPB2   GPB1  GPB0
    //Signal : GPB10  GPB9   GPB8   GPB7   GPB6   DIS_OFF L3CLOCK L3DATA L3MODE PWM2  PWM1
    //Setting: Output Output Output Output Output Output  Output  Output Output TOUT1 TOUT0 
    //Binary : 01,    01     *01,   *01    *01,   01      01,     01     01,    10    10  
    rGPBCON = 0x155559;
    rGPBUP  = 0x7ff;      // The pull up function is disabled GPB[10:0]

    //=== PORT C GROUP
    //Ports  : GPC15 GPC14 GPC13 GPC12 GPC11 GPC10 GPC9 GPC8 GPC7   GPC6   GPC5   GPC4 GPC3   GPC2  GPC1 GPC0
    //Signal : VD7   VD6   VD5   VD4   VD3   VD2   VD1  VD0  Output Output Output OUT   VFRAME VLINE VCLK LEND  
    //Binary : 10    10,   10    10,   10    10,   10   10,  *01    *01,   *01    01,  10     10,   10   10
    rGPCCON = 0xaaaa55aa;       
    rGPCUP  = 0xffff;     // The pull up function is disabled GPC[15:0] 

    //=== PORT D GROUP
    //Ports  : GPD15 GPD14 GPD13 GPD12 GPD11 GPD10 GPD9 GPD8 GPD7 GPD6 GPD5 GPD4 GPD3 GPD2 GPD1 GPD0
    //Signal : VD23  VD22  VD21  VD20  VD19  VD18  VD17 VD16 VD15 VD14 VD13 VD12 VD11 VD10 VD9  VD8
    //Binary : 10    10,   10    10,   10    10,   10   10,  10   10,  10   10,  10   10,  10   10
    rGPDCON = 0xaaaaaaaa;       
    rGPDUP  = 0xffff;     // The pull up function is disabled GPD[15:0]

    //=== PORT E GROUP
    //Ports  : GPE15  GPE14  GPE13  GPE12   GPE11   GPE10   GPE9    GPE8     GPE7  GPE6  GPE5   GPE4  
    //Signal : IICSDA IICSCL SPICLK SPIMOSI SPIMISO SDDATA3 SDDATA2 SDDATA1 SDDATA0 SDCMD SDCLK I2SSDO 
    //Binary : 10     10,    10     10,     10      10,     10      10,      10    10,   10     10,       
    //----------------------------------------------------------------------------------------
    //Ports  :  GPE3   GPE2  GPE1    GPE0    
    //Signal : I2SSDI CDCLK I2SSCLK I2SLRCK     
    //Binary :  10     10,    10      10 
    rGPECON = 0xa6aaaaaa;       
    rGPEUP  = 0xffff;     // The pull up function is disabled GPE[15:0]
	rGPEDAT = 0x2000;
    //=== PORT F GROUP
    //Ports  : GPF7   GPF6   GPF5   GPF4   GPF3    GPF2      GPF1    GPF0
    //Signal : LED_4  LED_3  LED_2  LED_1  PS2_INT CPLD_INT1 KEY_INT BUT_INT1
    //Setting: Output Output Output Output EINT3   EINT2     EINT1   EINT0
    //Binary : 01     01,    01     01,    10      10,       10      10
    rGPFCON = 0x55aa;
    rGPFUP  = 0xff;     // The pull up function is disabled GPF[7:0]

    //=== PORT G GROUP
    //Ports  : GPG15 GPG14 GPG13 GPG12 GPG11  GPG10  GPG9      GPG8      GPG7    GPG6    
    //Signal : nYPON YMON  nXPON XMON  GPG11  SD_CD  CPLD_INT3 CPLD_INT2 SPICLK1 SPIMOSI
    //Setting: nYPON YMON  nXPON XMON  Output Iutput EINT17    EINT17    SPICLK1 SPIMOSI1
    //Binary : 11    11,   11    11,   01     00,    10        10,       11      11
    //---------------------------------------------------------------------------------------
    //Ports  : GPG5     GPG4      GPG3     GPG2 GPG1    GPG0    
    //Signal : SPIMISO1 LCD_PWREN BUT_INT2 nSS0 NET_INT GPG0
    //Setting: SPIMISO1 LCD_PWRDN EINT11   nSS0 EINT9   Output
    //Binary : 11       11,       10       11,  10      *01
    rGPGCON = 0xff4af7b9;
    rGPGUP  = 0xffff;    // The pull up function is disabled GPG[15:0]

    //rGPGCON = (rGPGCON & 0xfffffcff) | (1<<8);	// GPG4 [9:8] 11  -> LCD_PWREN Enable
    // Eable LCD 
    // rGPGDAT = (rGPGDAT & 0xffef) | (1<<4);
    // close LCD 
    rGPGDAT = rGPGDAT & 0xffcf;

    //=== PORT H GROUP
    //Ports  : GPH10 GPH9     GPH8   GPH7  GPH6  GPH5 GPH4 GPH3 GPH2 GPH1  GPH0 
    //Signal : GPH10  CLKOUT0 SD_WP  CTS1  RTS1  RXD1 TXD1 RXD0 TXD0 nRTS0 nCTS0
    //Setting: Output CLKOUT0 GPH8   nCTS1 nRTS1 RXD1 TXD1 RXD0 TXD0 nRTS0 nCTS0
    //Binary : 10,    10      10,    11    11,   10   10,  10   10,  10    10
    rGPHCON = 0x2aaaaa;
    rGPHUP  = 0x7ff;    // The pull up function is disabled GPH[10:0]
    
}

/*********************************************************************************************
* name:		uart_change_baud
* func:		Change uart baud rate
* para:		nChannel	-- 	input, UART0, UART1 or UART2
*			nBaud		--	input, baud rate
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_change_baud(int nChannel, int nBaud)
{
    if (nChannel == UART0)
	    rUBRDIV0=( (int)(PCLK/16./nBaud + 0.5) -1 );
    
    if (nChannel == UART1)
	    rUBRDIV1=( (int)(PCLK/16./nBaud) -1 );

    if (nChannel == UART2)
	    rUBRDIV2=( (int)(PCLK/16./nBaud) -1 );
}

/*********************************************************************************************
* name:		uart_init
* func:		initialize uart channel
* para:		nMainClk	-- 	input, the MCLK value of current system
*			nBaud		-- 	input, baud rate value for UARTx
*			nChannel	-- 	input, UART0, UART1 or UART2
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_init(int nMainClk, int nBaud, int nChannel)
{
    int i;
    
    if(nMainClk == 0)
    nMainClk    = PCLK;
    
    switch (nChannel)
    {
    	case UART0: 
			rUFCON0 = 0x0;   //UART channel 0 FIFO control register, FIFO disable
			rUMCON0 = 0x0;   //UART chaneel 0 MODEM control register, AFC disable
			rULCON0 = 0x3;   //Line control register : Normal,No parity,1 stop,8 bits
	// [10]       [9]     [8]     [7]          [6]      [5]        [4]         [3:2]          [1:0]
	// Clock Sel, Tx Int, Rx Int, Rx Time Out, Rx err,  Loop-back, Send break, Transmit Mode, Receive Mode
	// 0          1       0,      0            1        0          0,          01             01
	// PCLK       Level   Pulse   Disable      Generate Normal     Normal      Interrupt or Polling
			rUCON0  = 0x245;								// Control register
	//		rUBRDIV0=( (int)(nMainClk/16./nBaud) -1 );		// Baud rate divisior register 0
			rUBRDIV0=( (int)(nMainClk/16./nBaud+0.5) -1 );	// Baud rate divisior register 0    
			break;
			
		case UART1: 
			rUFCON1 = 0x0;   //UART channel 1 FIFO control register, FIFO disable
			rUMCON1 = 0x0;   //UART chaneel 1 MODEM control register, AFC disable
			rULCON1 = 0x3;
			rUCON1  = 0x245;
			rUBRDIV1=( (int)(nMainClk/16./nBaud) -1 );
			break;
			
    	case UART2: 
			rULCON2 = 0x3;
			rUCON2  = 0x245;
			rUBRDIV2=( (int)(nMainClk/16./nBaud) -1 );    
			rUFCON2 = 0x0;   //UART channel 2 FIFO control register, FIFO disable
			break;
			
		default:
			break;
	}

    for(i=0;i<100;i++);
    delay(400);
}

/*********************************************************************************************
* name:		uart_select
* func:		change uart channel
* para:		nChannel	-- 	input, UART0, UART1 or UART2
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_select(int nChannel)
{
    f_nWhichUart=nChannel;
}

/*********************************************************************************************
* name:		uart_txempty
* func:		Empty uart channel
* para:		nChannel	-- 	input, UART0, UART1 or UART2
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_txempty(int nChannel)
{
    if(nChannel==0)
        while(!(rUTRSTAT0 & 0x4)); //Wait until tx shifter is empty.
          
    else if(nChannel==1)
        while(!(rUTRSTAT1 & 0x4)); //Wait until tx shifter is empty.
        
    else if(nChannel==2)
        while(!(rUTRSTAT2 & 0x4)); //Wait until tx shifter is empty.
}

/*********************************************************************************************
* name:		uart_getch
* func:		Get a character from the uart
* para:		none
* ret:		get a char from uart channel
* modify:
* comment:		
*********************************************************************************************/
char uart_getch(void)
{
    if(f_nWhichUart==0)
    {       
        while(!(rUTRSTAT0 & 0x1)); //Receive data ready
        return RdURXH0();
    }
    else if(f_nWhichUart==1)
    {       
        while(!(rUTRSTAT1 & 0x1)); //Receive data ready
        return RdURXH1();
    }
    else if(f_nWhichUart==2)
    {
        while(!(rUTRSTAT2 & 0x1)); //Receive data ready
        return RdURXH2();
    }
	return NULL;
}

//====================================================================
char uart_getkey(void)
{
    if(f_nWhichUart==0)
    {       
        if(rUTRSTAT0 & 0x1)    //Receive data ready
            return RdURXH0();
        else
            return 0;
    }
    else if(f_nWhichUart==1)
    {
        if(rUTRSTAT1 & 0x1)    //Receive data ready
            return RdURXH1();
        else
            return 0;
    }
    else if(f_nWhichUart==2)
    {       
        if(rUTRSTAT2 & 0x1)    //Receive data ready
            return RdURXH2();
        else
            return 0;
    }    
	return NULL;
}

/*********************************************************************************************
* name:		uart_getstring
* func:		Get string from uart channel and store the result to input address (*pString)
* para:		pString	-- 	input, string
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_getstring(char *pString)
{
    char *string2 = pString;
    char c;
    while((c = uart_getch())!='\r')
    {
        if(c=='\b')
        {
            if( (int)string2 < (int)pString )
            {
                uart_printf("\b \b");
                pString--;
            }
        }
        else 
        {
            *pString++ = c;
            uart_sendbyte(c);
        }
    }
    *pString='\0';
    uart_sendbyte('\n');
}

/*********************************************************************************************
* name:		uart_getintnum
* func:		Get a numerical (Dec - default or Hex fromat) from the uart, with or without a signed
* para:		none
* ret:		nResult: the valid number which user input from uart
* 					-- Dec format number (default)
* 					-- Hex format number ('H/h' suffix or '0x' ahead)
* modify:
* comment:		
*********************************************************************************************/
int uart_getintnum(void)
{
    char str[30];
    char *pString = str;
    int base     = 10;
    int minus    = 0;
    int nResult   = 0;
    int lastIndex;    
    int i;
    
    uart_getstring(pString);
    
    if(pString[0]=='-')
    {
        minus = 1;
        pString++;
    }
    
    if(pString[0]=='0' && (pString[1]=='x' || pString[1]=='X'))
    {
        base    = 16;
        pString += 2;
    }
    
    lastIndex = strlen(pString) - 1;
    
    if(lastIndex<0)
        return -1;
    
    if(pString[lastIndex]=='h' || pString[lastIndex]=='H' )
    {
        base = 16;
        pString[lastIndex] = 0;
        lastIndex--;
    }

    if(base==10)
    {
        nResult = atoi(pString);
        nResult = minus ? (-1*nResult):nResult;
    }
    else
    {
        for(i=0;i<=lastIndex;i++)
        {
            if(isalpha(pString[i]))
            {
                if(isupper(pString[i]))
                    nResult = (nResult<<4) + pString[i] - 'A' + 10;
                else
                    nResult = (nResult<<4) + pString[i] - 'a' + 10;
            }
            else
                nResult = (nResult<<4) + pString[i] - '0';
        }
        nResult = minus ? (-1*nResult):nResult;
    }
    return nResult;
}

/*********************************************************************************************
* name:		uart_sendbyte
* func:		Send one byte to uart channel
* para:		nData	-- 	input, byte
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_sendbyte(int nData)
{
    if(f_nWhichUart==0)
    {
        if(nData=='\n')
        {
            while(!(rUTRSTAT0 & 0x2));
            delay(10);					//because the slow response of hyper_terminal 
            WrUTXH0('\r');
        }
        while(!(rUTRSTAT0 & 0x2));		//Wait until THR is empty.
        delay(10);
        WrUTXH0(nData);
    }
    else if(f_nWhichUart==1)
    {
        if(nData=='\n')
        {
            while(!(rUTRSTAT1 & 0x2));
            delay(10);					//because the slow response of hyper_terminal 
            rUTXH1 = '\r';
        }
        while(!(rUTRSTAT1 & 0x2));		//Wait until THR is empty.
        delay(10);
        rUTXH1 = nData;
    }   
    else if(f_nWhichUart==2)
    {
        if(nData=='\n')
        {
            while(!(rUTRSTAT2 & 0x2));
            delay(10);					//because the slow response of hyper_terminal 
            rUTXH2 = '\r';
        }
        while(!(rUTRSTAT2 & 0x2));		//Wait until THR is empty.
        delay(10);
        rUTXH2 = nData;
    }       
}               

/*********************************************************************************************
* name:		uart_sendstring
* func:		Send string to uart channel
* para:		pString	-- 	input, string
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void uart_sendstring(char *pString)
{
    while(*pString)
        uart_sendbyte(*pString++);
}

/*********************************************************************************************
* name:		uart_printf
* func:		print format string
* para:		fmt	-- 	input,  
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
//If you don't use vsprintf(), the code size is reduced very much.
void uart_printf(char *fmt,...)
{
    va_list ap;
    char pString[256];

    va_start(ap,fmt);
    vsprintf(pString,fmt,ap);
    uart_sendstring(pString);
    va_end(ap);
}

void beep(int nBeepStatus)
{
	if (nBeepStatus==0)
		rGPBDAT |= 0x1;
	else
		rGPBDAT &= 0x7fe;

}
/*********************************************************************************************
* name:		timer_start
* func:		start timer
* para:		nDivider	-- 	input, 0:16us,1:32us 2:64us 3:128us
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void timer_start(int divider)  //0:16us,1:32us 2:64us 3:128us
{
    rWTCON = ((PCLK/1000000-1)<<8)|(divider<<3); //Watch-dog timer control register
    rWTDAT = 0xffff;							 //Watch-dog timer data register
    rWTCNT = 0xffff;							 //Watch-dog count register

	//Watch-dog timer enable & interrupt  disable
//	rWTCON = rWTCON |(1<<5) & !(1<<2);	 //?
    rWTCON = rWTCON | (1<<5) | ~(1<<2);  //May 06, 2002 SOP
}

/*********************************************************************************************
* name:		timer_stop
* func:		stop timer
* para:		none
* ret:			--	int, timer count
* modify:
* comment:		
*********************************************************************************************/
int timer_stop(void)
{
    rWTCON = ((PCLK/1000000-1)<<8);
    return (0xffff - rWTCNT);
}


//========================[ MPLL ]=================================
void change_value_MPLL(int nMdiv,int nPdiv,int nSdiv)
{
    rMPLLCON = (nMdiv<<12) | (nPdiv<<4) | nSdiv;
}


//========================[ HCLK, PCLK ]===========================
void change_clock_divider(int nHdiv,int nPdiv)
{
     // nHdiv,nPdiv FCLK:HCLK:PCLK
     //     0,0         1:1:1 
     //     0,1         1:1:2 
     //     1,0         1:2:2
     //     1,1         1:2:4
    rCLKDIVN = (nHdiv<<1) | nPdiv;    
    
//    if(nHdiv)
//        MMU_SetAsyncBusMode();
//    else 
//        MMU_SetFastBusMode();
}


//========================**[ UPLL ]==============================*
void ChangeUPllValue(int nMdiv,int nPdiv,int nSdiv)
{
    rUPLLCON = (nMdiv<<12) | (nPdiv<<4) | nSdiv;
}


//========================*[ General Library ]=====================*
/*void * smalloc(unsigned nByte) 
//Very simple; Use malloc() & free() like Stack
//void *malloc_pt=Image_RW_Limit;
{
    void *pReturnPt = Image_RW_Limit;

    malloc_pt = (int *)malloc_pt+nByte/4+((nByte%4)>0); //To align 4byte

    if( (int)malloc_pt > HEAPEND )
    {
        malloc_pt = pReturnPt;
        return NULL;
    }
    return pReturnPt;
}		  

//-------------------------------------------------------------------
void sfree(void *pString)
{
    malloc_pt = pString;
}			 */

/*********************************************************************************************
* name:		delay
* func:		delay time
* para:		nTime -- input, nTime=0: nAdjust the delay function by WatchDog timer.
*						    nTime>0: the number of loop time, 100us resolution.
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void delay(int nTime)
{
      // time=0: adjust the Delay function by WatchDog timer.
      // time>0: the number of loop time
      // resolution of time is 100us.
    int i,adjust=0;
    if(nTime==0)
    {
        nTime   = 200;
        adjust = 1;
        delayLoopCount = 400;
		//PCLK/1M,Watch-dog disable,1/64,interrupt disable,reset disable
        rWTCON = ((PCLK/1000000-1)<<8)|(2<<3); 
        rWTDAT = 0xffff;                              //for first update
        rWTCNT = 0xffff;                              //resolution=64us @any PCLK 
        rWTCON = ((PCLK/1000000-1)<<8)|(2<<3)|(1<<5); //Watch-dog timer start
    }
    for(;nTime>0;nTime--)
        for(i=0;i<delayLoopCount;i++);
    if(adjust==1)
    {
        rWTCON = ((PCLK/1000000-1)<<8)|(2<<3);   //Watch-dog timer stop
        i = 0xffff - rWTCNT;                     //1count->64us, 200*400 cycle runtime = 64*i us
        delayLoopCount = 8000000/(i*64);         //200*400:64*i=1*x:100 -> x=80000*100/(64*i)   
    }
}

/*********************************************************************************************
* name:		__gccmain
* func:		the entry point of gcc library
* para:		none
* ret:		none
* modify:
* comment:		
*********************************************************************************************/
void __gccmain(void)
{
}
