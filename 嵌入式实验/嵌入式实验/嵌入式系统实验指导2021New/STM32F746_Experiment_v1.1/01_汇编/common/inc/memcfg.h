//************************************************ 
// NAME    : memcfg.inc
// DESC	  : Memory bank configuration file
// Revision: 02.28.2002 ver 0.0
//************************************************

//Memory Area
//GCS6 16bit(16MB) SDRAM(0x0c000000-0x0cffffff)
//GCS7 16bit(16MB) SDRAM(0x0d000000-0x0dffffff)
//          or
//GCS6 32bit(32MB) SDRAM(0x0c000000-0x0dffffff)

#ifndef __MEMCFG_H
#define __MEMCFG_H
 
// BUSWIDTH : 16,32
#define BUSWIDTH    (32)

//64MB
// 0x30000000 ~ 0x30ffffff : Download Area (16MB) Cacheable
// 0x31000000 ~ 0x33feffff : Non-Cacheable Area
// 0x33ff0000 ~ 0x33ff47ff : Heap & RW Area
// 0x33ff4800 ~ 0x33ff7fff : FIQ ~ User Stack Area
// 0x33ff8000 ~ 0x33fffeff : Not Used Area
// 0x33ffff00 ~ 0x33ffffff : Exception & ISR Vector Table

#define _RAM_STARTADDRESS       0x30000000
#define _NONCACHE_STARTADDRESS	0x31000000
#define _ISR_STARTADDRESS       0x33ffff00     
#define _MMUTT_STARTADDRESS     0x33ff8000
#define _STACK_BASEADDRESS      0x33ff8000
#define HEAPEND                 0x33ff0000

//BWSCON
#define DW8			(0x0)
#define DW16			(0x1)
#define DW32			(0x2)
#define WAIT			(0x1<<2)
#define UBLB			(0x1<<3)

//BUSWIDTH=32

#define B1_BWSCON	 (DW32)
#define B2_BWSCON	 (DW16)
#define B3_BWSCON	 (DW16)
#define B4_BWSCON	 (DW16)
#define B5_BWSCON	 (DW16)
#define B6_BWSCON	 (DW32)
#define B7_BWSCON	 (DW32)
    

//BANK0CON 
#define B0_Tacs			0x0	//0clk
#define B0_Tcos			0x0	//0clk
#define B0_Tacc			0x7	//14clk
#define B0_Tcoh			0x0	//0clk
#define B0_Tah			0x0	//0clk
#define B0_Tacp			0x0	
#define B0_PMC			0x0	//normal

//BANK1CON
#define B1_Tacs			0x0	//0clk
#define B1_Tcos			0x0	//0clk
#define B1_Tacc			0x7	//14clk
#define B1_Tcoh			0x0	//0clk
#define B1_Tah			0x0	//0clk
#define B1_Tacp			0x0	
#define B1_PMC			0x0	//normal

//Bank 2 parameter
#define B2_Tacs			0x0	//0clk
#define B2_Tcos			0x0	//0clk
#define B2_Tacc			0x7	//14clk
#define B2_Tcoh			0x0	//0clk
#define B2_Tah			0x0	//0clk
#define B2_Tacp			0x0	
#define B2_PMC			0x0	//normal

//Bank 3 parameter
#define B3_Tacs			0x0	//0clk
#define B3_Tcos			0x0	//0clk
#define B3_Tacc			0x7	//14clk
#define B3_Tcoh			0x0	//0clk
#define B3_Tah			0x0	//0clk
#define B3_Tacp			0x0	
#define B3_PMC			0x0	//normal

//Bank 4 parameter
#define B4_Tacs			0x0	//0clk
#define B4_Tcos			0x0	//0clk
#define B4_Tacc			0x7	//14clk
#define B4_Tcoh			0x0	//0clk
#define B4_Tah			0x0	//0clk
#define B4_Tacp			0x0	
#define B4_PMC			0x0	//normal

//Bank 5 parameter
#define B5_Tacs			0x0	//0clk
#define B5_Tcos			0x0	//0clk
#define B5_Tacc			0x7	//14clk
#define B5_Tcoh			0x0	//0clk
#define B5_Tah			0x0	//0clk
#define B5_Tacp			0x0	
#define B5_PMC			0x0	//normal

//Bank 6 parameter
#define B6_MT			0x3	//SDRAM
//B6_Trcd			0x0	//2clk
#define B6_Trcd			0x1	//3clk
#define B6_SCAN			0x1	//9bit

//Bank 7 parameter
#define B7_MT			0x3	//SDRAM
//B7_Trcd			0x0	//2clk
#define B7_Trcd			0x1	//3clk
#define B7_SCAN			0x1	//9bit

//REFRESH parameter
#define REFEN	  	    0x1	//Refresh enable
#define TREFMD	  	    0x0	//CBR(CAS before RAS)/Auto refresh
#define Trp	  	        0x0	//2clk
#define Trc	  	        0x3	//7clk
		
#define Tchr			0x2	//3clk
#define REFCNT			1113	//period=15.6us, HCLK=60Mhz, (2048+1-15.6*60)


#endif

