#ifndef _LED_
#define _LED_

#include "SPCE061A.h"

typedef union{
	unsigned int W;
	struct{
		unsigned int bit0:1;
		unsigned int bit1:1;
		unsigned int bit2:1;
		unsigned int bit3:1;
		unsigned int bit4:1;
		unsigned int bit5:1;
		unsigned int bit6:1;
		unsigned int bit7:1;
		unsigned int bit8:1;
		unsigned int bit9:1;
		unsigned int bit10:1;
		unsigned int bit11:1;
		unsigned int bit12:1;
		unsigned int bit13:1;
		unsigned int bit14:1;
		unsigned int bit15:1;
	}A;  //}B;

}GEN_REG_DEF;


#define 	P_IOA_Data_ADDR   		0x7000
#define 	P_IOA_Buffer_ADDR		0x7001
#define 	P_IOA_Dir_ADDR 			0x7002
#define 	P_IOA_Attrib_ADDR		0x7003
#define 	P_IOA_Latch_ADDR		0x7004

/* B1. PortA register*/
#define MACRO_P_IOA_Data			((volatile GEN_REG_DEF *)(P_IOA_Data_ADDR))
#define MACRO_P_IOA_Buffer			((volatile GEN_REG_DEF *)(P_IOA_Buffer_ADDR))
#define MACRO_P_IOA_Dir				((volatile GEN_REG_DEF *)(P_IOA_Dir_ADDR))
#define MACRO_P_IOA_Attrib			((volatile GEN_REG_DEF *)(P_IOA_Attrib_ADDR))
#define MACRO_P_IOA_Latch				((volatile GEN_REG_DEF *)(P_IOA_Latch_ADDR))


#define 	P_IOB_Data_ADDR		0x7005
#define 	P_IOB_Buffer_ADDR	0x7006
#define 	P_IOB_Dir_ADDR		0x7007
#define 	P_IOB_Attrib_ADDR	0x7008

/* B2. PortB register*/
#define MACRO_P_IOB_Data			((volatile GEN_REG_DEF *)(P_IOB_Data_ADDR))
#define MACRO_P_IOB_Buffer			((volatile GEN_REG_DEF *)(P_IOB_Buffer_ADDR))
#define MACRO_P_IOB_Dir				((volatile GEN_REG_DEF *)(P_IOB_Dir_ADDR))
#define MACRO_P_IOB_Attrib			((volatile GEN_REG_DEF *)(P_IOB_Attrib_ADDR))



#define HIGH 1
#define LOW 0

#define SER MACRO_P_IOA_Buffer->A.bit8   //#define SER  MACRO_P_IOB_Buffer->B.bit0  //P1_0
#define RCK MACRO_P_IOA_Buffer->A.bit9  //#define RCK  MACRO_P_IOB_Buffer->B.bit1 //P1_1
#define SRCK MACRO_P_IOA_Buffer->A.bit10  //#define SRCK MACRO_P_IOB_Buffer->B.bit2 //P1_2 

#define BYTE_5 0x8000   //#define BYTE_5 0x80
#define LED1 0x01
#define LED2 0x02
#define LED3 0x04
#define LED4 0x08
#define LED5 0x10
#define LED6 0x20
#define LED7 0x40
#define LED8 0x80

void INIT_LED(void);
void LED_Printf(unsigned char data,unsigned char byte);

#endif



