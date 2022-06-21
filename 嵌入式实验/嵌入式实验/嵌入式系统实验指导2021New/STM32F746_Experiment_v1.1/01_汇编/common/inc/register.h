/*********************************************************************************************
* File name	: register.h
* Author	: embest
* Descript	: S3C2410 Define Address Register 
* History
*			R.X.Huang, Programming modify, March 12, 2005
*********************************************************************************************/

#ifndef _S3C2410_REG_H
#define _S3C2410_REG_H

#define GPIO(Nb)	(0x00000001 << Nb)
#define GPIO0		GPIO (0)   /* GPIO  [0]				*/
#define GPIO1		GPIO (1)   /* GPIO  [1]				*/
#define GPIO2		GPIO (2)   /* GPIO  [2]				*/
#define GPIO3		GPIO (3)   /* GPIO  [3]				*/
#define GPIO4		GPIO (4)   /* GPIO  [4]				*/
#define GPIO5		GPIO (5)   /* GPIO  [5]				*/
#define GPIO6		GPIO (6)   /* GPIO  [6]				*/
#define GPIO7		GPIO (7)   /* GPIO  [7]				*/
#define GPIO8		GPIO (8)   /* GPIO  [8]				*/
#define GPIO9		GPIO (9)   /* GPIO  [9]				*/
#define GPIO10		GPIO (10)  /* GPIO [10]				*/
#define GPIO11		GPIO (11)  /* GPIO [11]				*/
#define GPIO12		GPIO (12)  /* GPIO [12]				*/
#define GPIO13		GPIO (13)  /* GPIO [13]				*/
#define GPIO14		GPIO (14)  /* GPIO [14]				*/
#define GPIO15		GPIO (15)  /* GPIO [15]				*/
#define GPIO16		GPIO (16)  /* GPIO [16]				*/
#define GPIO17		GPIO (17)  /* GPIO [17]				*/


#define INTMSK		0x4A000008
#define INTPND		0x4A000010
#define INTSUBMSK	0x4A00001C
#define WTCON		0x53000000
#define LOCKTIME	0x4C000000
#define MPLLCON		0x4C000004
#define UPLLCON		0x4C000008
#define CLKDIVN		0x4C000014
#define BWSCON		0x48000000
#define REFRESH		0x48000024
#define BANKSIZE	0x48000028
#define GPFCON		0x56000050
#define GPFDAT		0x56000054
#define GPFUP		0x56000058

#define MISCCR		0x56000080
#define SCK_NORMAL	(0x7<<17)

#define GSTATUS0	0x560000AC
#define GSTATUS1	0x560000B0
#define GSTATUS2	0x560000B4
#define GSTATUS3	0x560000B8
#define GSTATUS4	0x560000BC    

#endif
