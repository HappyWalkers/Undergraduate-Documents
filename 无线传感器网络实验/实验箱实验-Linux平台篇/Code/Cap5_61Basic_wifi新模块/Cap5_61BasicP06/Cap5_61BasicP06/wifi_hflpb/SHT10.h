//======================================================
// 文件名称:   SHT10.h
// 功能描述：  温湿度传感器SHT10驱动头文件
// 维护记录：  
//				
//======================================================
#ifndef	__SHT10_h__
#define	__SHT10_h__
//	write your header here

#include "SPCE061A.h"
//I2C timeing

//	#define I2C_PORT		PORT_IOA
//	
//	#define I2C_D			C_Bit7
//	#define I2C_C			C_Bit8
//#define I2C_RST			C_Bit10

//#define I2C_D			(1<<7)	// IOA7
//#define I2C_C			(1<<8)	// IOA8

#define I2C_D			(1<<1)	//(1<<1)	// IOA1
#define I2C_C			(1<<0)	// IOA0
//	#if (I2C_PORT == PORT_IOA)
#define I2C_Dir		P_IOA_Dir
#define I2C_Attrib	P_IOA_Attrib
#define I2C_Buffer	P_IOA_Buffer
#define I2C_Data	P_IOA_Data
//	#elif (I2C_PORT == PORT_IOB)
//	#define I2C_Dir		P_IOB_Dir
//	#define I2C_Attrib	P_IOB_Attrib
//	#define I2C_Buffer	P_IOB_Buffer
//	#define I2C_Data	P_IOB_Data
//	#elif
//	#error Config I2C_PORT first!
//	#endif

#define CFG_WRITE(b)		(*I2C_Dir |= (b))
#define CFG_READ(b)			(*I2C_Dir &= ~(b))
#define MAKE_HIGH(b)		(*I2C_Buffer |= (b))
#define MAKE_LOW(b)			(*I2C_Buffer &= ~(b))
#define BIT_READ(b)			((*I2C_Data & (b)) ? 1 : 0)

#define DURATION1 	1

/*****************************************
******************************************/

#define SCLK_DIR_OUT 	CFG_WRITE(I2C_C)//(OEA |=0x01)
//#define RST_DIR_OUT		CFG_WRITE(I2C_RST)//(OEA |=0x04)
#define SDIO_DIR_IN 	CFG_READ(I2C_D),MAKE_HIGH(I2C_D)//	(OEA &=0xfd)
#define SDIO_DIR_OUT 	CFG_WRITE(I2C_D)//(OEA |=0x02)

#define SCLK_HIGH		MAKE_LOW(I2C_C)
#define SCLK_LOW		MAKE_HIGH(I2C_C)

#define SDIO_HIGH		MAKE_LOW(I2C_D)
#define SDIO_LOW		MAKE_HIGH(I2C_D)
#define READ_SDIO		BIT_READ(I2C_D)

//#define RST_HIGH		MAKE_LOW(I2C_RST)
//#define RST_LOW			MAKE_HIGH(I2C_RST)

/**************************************
***************************************/

#define DELAY(DURATION)		{volatile unsigned short i = DURATION; while(i--){*P_Watchdog_Clear=0x0001;*P_Watchdog_Clear=0x0001;}}


//SH10 Command 

#define CMD_RESERVED 			0x00			//保留
#define CMD_TEM_MES				0x03			//温度测量命令
#define CMD_HUMI_MES			0x05			//湿度测量命令
#define CMD_Read_STATUS_REG		0x07			//读状态寄存器
#define CMD_Write_STATUS_REG	0x06			//写状态寄存器
#define CMD_Soft_Reset			0x1E			//软复位


#define bitselect     0x01    //选择温度与湿度的低位读
#define noACK         0
#define ACK           1
#define HUMIDITY      2
#define TEMPERATURE   1

void I2c_Init(void);
void SHT10_Transstart(void);
char SHT10_WriteByte(unsigned char data);
char SHT10_ReadByte(unsigned char ack);
void SHT10_Connectionreset(void);
char SHT10_Softreset(void);
char SHT10_WriteStatusReg(unsigned char RegVlaue);
unsigned char SHT10_Measure(unsigned int *p_value, unsigned char *p_checksum, unsigned char mode);
//float SHT10_Calculate(unsigned int data,unsigned char mode);
void SHT10_init(unsigned int Initial_Reg);
int CalcRH(unsigned char dat);
int CalcT(unsigned int dat);
#endif
