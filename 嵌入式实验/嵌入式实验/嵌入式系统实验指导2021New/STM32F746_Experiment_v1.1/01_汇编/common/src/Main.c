/****************************************************************
 NAME: u2440mon.c
 DESC: u2440mon entry point,menu,download
 HISTORY:
 Mar.25.2002:purnnamu: S3C2400X profile.c is ported for S3C2410X.
 Mar.27.2002:purnnamu: DMA is enabled.
 Apr.01.2002:purnnamu: isDownloadReady flag is added.
 Apr.10.2002:purnnamu: - Selecting menu is available in the waiting loop. 
                         So, isDownloadReady flag gets not needed
                       - UART ch.1 can be selected for the console.
 Aug.20.2002:purnnamu: revision number change 0.2 -> R1.1       
 Sep.03.2002:purnnamu: To remove the power noise in the USB signal, the unused CLKOUT0,1 is disabled.
 ****************************************************************/
#define	GLOBAL_CLK		1

#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"
#include "mmu.h"
#include "profile.h"
#include "memtest.h"

//#include "usbmain.h"
//#include "usbout.h"
//#include "usblib.h"
//#include "2440usb.h"

extern char Image$$RO$$Limit[];
extern char Image$$RO$$Base[];
extern char Image$$RW$$Limit[];
extern char Image$$RW$$Base[];
extern char Image$$ZI$$Limit[];
extern char Image$$ZI$$Base[];

void Isr_Init(void);
void HaltUndef(void);
void HaltSwi(void);
void HaltPabort(void);
void HaltDabort(void);
void ClearMemory(void);


void Clk0_Enable(int clock_sel);	
void Clk1_Enable(int clock_sel);
void Clk0_Disable(void);
void Clk1_Disable(void);

extern void Lcd_Tft_LTV350QV_F05_Init(void) ;
extern void Lcd_Tft_LTV350QV_F05_Test( void ) ;
extern void Test_Lcd_VGA_640_480(void) ;
extern void Test_Lcd_VGA_800_600(void) ;
extern void Test_VGA_640_480(void) ;

extern void Test_Touchpanel(void) ;
extern void Test_Adc(void) ;		//adc test
extern void KeyScan_Test(void) ;
extern void RTC_Display(void) ;
extern void Test_MCP2510(void) ;
extern void Test_IrDa(void) ;
extern void Temperature(void) ;
extern void PlayMusicTest(void) ;
extern void RecordTest( void ) ;
extern void Camera_Test( void ) ;
extern void Test_Iic(void) ;
extern void Test_SDI(void) ;
extern void Led_test(void);

volatile U32 downloadAddress;

void (*restart)(void)=(void (*)(void))0x0;

volatile unsigned char *downPt;
volatile U32 downloadFileSize;
volatile U16 checkSum;
volatile unsigned int err=0;
volatile U32 totalDmaCount;

volatile int isUsbdSetConfiguration;

int download_run=0;
U32 tempDownloadAddress;
int menuUsed=0;

extern char Image$$RW$$Limit[];
U32 *pMagicNum=(U32 *)Image$$RW$$Limit;
int consoleNum;

static U32 cpu_freq;
static U32 UPLL;
static void cal_cpu_bus_clk(void)
{
	U32 val;
	U8 m, p, s;
	
	val = rMPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;

	//(m+8)*FIN*2 不要超出32位数!
	FCLK = ((m+8)*(FIN/100)*2)/((p+2)*(1<<s))*100;
	
	val = rCLKDIVN;
	m = (val>>1)&3;
	p = val&1;	
	val = rCAMDIVN;
	s = val>>8;
	
	switch (m) {
	case 0:
		HCLK = FCLK;
		break;
	case 1:
		HCLK = FCLK>>1;
		break;
	case 2:
		if(s&2)
			HCLK = FCLK>>3;
		else
			HCLK = FCLK>>2;
		break;
	case 3:
		if(s&1)
			HCLK = FCLK/6;
		else
			HCLK = FCLK/3;
		break;
	}
	
	if(p)
		PCLK = HCLK>>1;
	else
		PCLK = HCLK;
	
	if(s&0x10)
		cpu_freq = HCLK;
	else
		cpu_freq = FCLK;
		
	val = rUPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;
	UPLL = ((m+8)*FIN)/((p+2)*(1<<s));
	UCLK = (rCLKDIVN&8)?(UPLL>>1):UPLL;
}


void Temp_function() { Uart_Printf("\nPlease input 1-13 to select test!!!\n"); }

struct {
	void (*fun)(void);
	char *tip;
}CmdTip[] = {
				{ Temp_function, "Please input 1-13 to select test" } ,
				{ BUZZER_PWM_Test, "Test PWM" } ,
				{ RTC_Display, "RTC time display" } ,
				{ Test_Adc, "Test ADC" } ,
				{ Led_test, "Test LED"},
				{ KeyScan_Test, "Test interrupt and key scan" } ,
				{ Test_Touchpanel, "Test Touchpanel" } ,
				{ Lcd_Tft_LTV350QV_F05_Test, "Test LCD 320*240" } ,
				//{ Test_VGA_640_480, "Test LCD 640*480" } ,
				{ Test_Iic, "Test IIC EEPROM" } ,
				{ Test_IrDa, "Test IrDA" } ,
				{ Temperature, "Test temperature" } ,
				{ PlayMusicTest, "UDA1341 play music" } ,
				{ RecordTest, "UDA1341 record voice" } ,
			//	{ Test_SDI, "Test SD Card" } ,
				{ Camera_Test, "Camera Preview Test " } ,
				{ 0, 0}						
			};


void Main(void)
{
	char *mode;
	int i;
	U8 key;
	U32 mpll_val = 0 ;
	//U32 divn_upll = 0 ;
    
	#if ADS10   
//	__rt_lib_init(); //for ADS 1.0
	#endif

	Port_Init();
	
	Isr_Init();
	
	i = 2 ;	//don't use 100M!
		//boot_params.cpu_clk.val = 3;
	switch ( i ) {
	case 0:	//200
		key = 14;
		mpll_val = (100<<12)|(2<<4)|(2);
		break;
	case 1:	//300
		key = 14;
		mpll_val = (60<<12)|(1<<4)|(1);
		break;
	case 2:	//400
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);
		break;
	case 3:	//440!!!
		key = 14;
		mpll_val = (102<<12)|(1<<4)|(1);
		break;
	default:
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);
		break;
	}
	
	//init FCLK=400M, so change MPLL first
	ChangeMPllValue((mpll_val>>12)&0xff, (mpll_val>>4)&0x3f, mpll_val&3);
	ChangeClockDivider(key, 12);
	cal_cpu_bus_clk();
	
	consoleNum = 0;	// Uart 1 select for debug. 
	Uart_Init( 0,115200 );
	Uart_Select( consoleNum );
	
	Beep(2000, 100);
	
	Uart_SendByte('\n');
	Uart_Printf("<***********************************************>\n");
	Uart_Printf("           TE-2440 Test Program VER1.0\n");
	Uart_Printf("                www.witech.com.cn\n");
	Uart_Printf("      Build time is: %s  %s\n", __DATE__ , __TIME__  );
    Uart_Printf( "          Image$$RO$$Base  = 0x%x\n", Image$$RO$$Base );
	Uart_Printf( "          Image$$RO$$Limit = 0x%x\n", Image$$RO$$Limit );
	Uart_Printf( "          Image$$RW$$Base  = 0x%x\n", Image$$RW$$Base );
	Uart_Printf( "          Image$$RW$$Limit = 0x%x\n", Image$$RW$$Limit );
    Uart_Printf( "          Image$$ZI$$Base  = 0x%x\n", Image$$ZI$$Base );
    Uart_Printf( "          Image$$ZI$$Limit = 0x%x\n", Image$$ZI$$Limit );
	Uart_Printf("<***********************************************>\n");

	rMISCCR=rMISCCR&~(1<<3); // USBD is selected instead of USBH1 
	rMISCCR=rMISCCR&~(1<<13); // USB port 1 is enabled.


	rDSC0 = 0x2aa;
	rDSC1 = 0x2aaaaaaa;
	//Enable NAND, USBD, PWM TImer, UART0,1 and GPIO clock,
	//the others must be enabled in OS!!!
	rCLKCON = 0xfffff0;
	



	MMU_Init();	

	pISR_SWI=(_ISR_STARTADDRESS+0xf0);	//for pSOS

	Led_Display(0x6);

#if USBDMA
	mode="DMA";
#else
	mode="Int";
#endif

	// CLKOUT0/1 select.
	//Uart_Printf("CLKOUT0:MPLL in, CLKOUT1:RTC clock.\n");
	//Clk0_Enable(0);	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0
	//Clk1_Enable(2);	// 0:MPLLout, 1:UPLL, 2:RTC, 3:HCLK, 4:PCLK, 5:DCLK1	
	Clk0_Disable();
	Clk1_Disable();
	
	mpll_val = rMPLLCON;

	Lcd_Tft_LTV350QV_F05_Init() ;		// LCD initial
	
	download_run=1; //The default menu is the Download & Run mode.

	while(1)
	{
		U8 idx;
	
		Uart_Printf("\nPlease select function : \n");	
		for(i=0; CmdTip[i].fun!=0; i++)
			Uart_Printf("%d : %s\n", i, CmdTip[i].tip);
		idx = Uart_GetIntNum_GJ() ;	
		if(idx<i)
		{
			(*CmdTip[idx].fun)();
			Delay(20);
			Uart_Init( 0,115200 );
		}	
	}	  	

}

void Isr_Init(void)
{
	pISR_UNDEF=(unsigned)HaltUndef;
	pISR_SWI  =(unsigned)HaltSwi;
	pISR_PABORT=(unsigned)HaltPabort;
	pISR_DABORT=(unsigned)HaltDabort;
	rINTMOD=0x0;	  // All=IRQ mode
	rINTMSK=BIT_ALLMSK;	  // All interrupt is masked.

	//pISR_URXD0=(unsigned)Uart0_RxInt;	
	//rINTMSK=~(BIT_URXD0);   //enable UART0 RX Default value=0xffffffff

#if 1
	//pISR_USBD =(unsigned)IsrUsbd;
	//pISR_DMA2 =(unsigned)IsrDma2;
#else
	pISR_IRQ =(unsigned)IsrUsbd;	
		//Why doesn't it receive the big file if use this. (???)
		//It always stops when 327680 bytes are received.
#endif	
	//ClearPending(BIT_DMA2);
	//ClearPending(BIT_USBD);
	//rINTMSK&=~(BIT_USBD);  
   
	//pISR_FIQ,pISR_IRQ must be initialized
}


void HaltUndef(void)
{
	Uart_Printf("Undefined instruction exception!!!\n");
	while(1);
}

void HaltSwi(void)
{
	Uart_Printf("SWI exception!!!\n");
	while(1);
}

void HaltPabort(void)
{
	Uart_Printf("Pabort exception!!!\n");
	while(1);
}

void HaltDabort(void)
{
	Uart_Printf("Dabort exception!!!\n");
	while(1);
}


void ClearMemory(void)
{
	//int i;
	//U32 data;
	int memError=0;
	U32 *pt;
	
	Uart_Printf("Clear Memory (%xh-%xh):WR",_RAM_STARTADDRESS,HEAPEND);

	pt=(U32 *)_RAM_STARTADDRESS;
	while((U32)pt < HEAPEND)
	{
		*pt=(U32)0x0;
		pt++;
	}
	
	if(memError==0)Uart_Printf("\b\bO.K.\n");
}

void Clk0_Enable(int clock_sel)	
{	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0
	rMISCCR = rMISCCR&~(7<<4) | (clock_sel<<4);
	rGPHCON = rGPHCON&~(3<<18) | (2<<18);
}
void Clk1_Enable(int clock_sel)
{	// 0:MPLLout, 1:UPLL, 2:RTC, 3:HCLK, 4:PCLK, 5:DCLK1	
	rMISCCR = rMISCCR&~(7<<8) | (clock_sel<<8);
	rGPHCON = rGPHCON&~(3<<20) | (2<<20);
}
void Clk0_Disable(void)
{
	rGPHCON = rGPHCON&~(3<<18);	// GPH9 Input
}
void Clk1_Disable(void)
{
	rGPHCON = rGPHCON&~(3<<20);	// GPH10 Input
}

