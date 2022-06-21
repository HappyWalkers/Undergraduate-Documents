//============================================================================
//	文件名称：	UART.c
//	功能描述：	串口驱动程序
//	维护记录：	lijian<lijian@sunplusapp.com>	2010-4-12
//==========================================================================
#include "UART.h"

#undef USE_TXINT
volatile struct {
	void (*ProcessRxByte)(unsigned char ch);
#ifdef USE_TXINT
	volatile const unsigned char *txBuf;
	volatile int txLen;
#endif
} UART_INFO;

//=============================================================
// 语法格式：	void UART_Init(void)
// 实现功能：	初始化串口驱动,默认波特率9600
// 参数：		无
// 返回值：		无
//=============================================================
void UART_Init(void (*ProcessRxByte)(unsigned char ch))
{
	UART_INFO.ProcessRxByte = ProcessRxByte;
	*P_IOB_Attrib = (*P_IOB_Attrib & ~(1<<7)) | (1<<10);
	*P_IOB_Buffer |= ((1<<7) | (1<<10));
	*P_IOB_Dir = (*P_IOB_Dir & ~(1<<7)) | (1<<10);
	*P_UART_BaudScalarLow = 0x0000;							// Baudrate 9600
	*P_UART_BaudScalarHigh = 0x0005;
	*P_UART_Command1 = C_UART_RX_INT | C_UART_PARITY_DIS
#ifdef USE_TXINT
		| C_UART_TX_INT
#endif
		;	// Enable Rx interrupt
	*P_UART_Command2 = C_UART_RX_EN | C_UART_TX_EN;			// Enable Rx, Tx
}

static const unsigned int BaudRateTable[MaxBaudRate] = {
	[BaudRate300]    = 0xA000,
	[BaudRate600]    = 0x5000,
	[BaudRate1200]   = 0x2800,
	[BaudRate2400]   = 0x1400,
	[BaudRate4096]   = 0x0BB8,
	[BaudRate4800]   = 0x0A00,
	[BaudRate9600]   = 0x0500,
	[BaudRate14400]  = 0x0355,
	[BaudRate19200]  = 0x0280,
	[BaudRate28800]  = 0x01AA,
	[BaudRate38400]  = 0x0140,
	[BaudRate57600]  = 0x00D5,
	[BaudRate115200] = 0x006B,
};
//=============================================================
// 语法格式：	void UART_BaudSet(BAUDRATE nBaudRate)
// 实现功能：	设置串口波特率
// 参数：		nBaudRate - 波特率
// 返回值：		无
//=============================================================
void UART_BaudSet(BAUDRATE nBaudRate)
{
	*P_UART_BaudScalarLow = BaudRateTable[nBaudRate];
	*P_UART_BaudScalarHigh = BaudRateTable[nBaudRate] >> 8;
}

//=============================================================
// 语法格式：	int UART_Send(PBYTE buf, int size)
// 实现功能：	发送数据
// 参数：		buf - 发送缓冲区首地址
//				size - 发送数据量（字节）
// 返回值：		0表示成功, -1表示失败
//=============================================================
int UART_Send(const void *buf, int size)
{
#ifdef USE_TXINT
	UART_INFO.txBuf = (const unsigned char *)buf;
	UART_INFO.txLen = size;
	*P_UART_Command1 = C_UART_TX_INT | C_UART_RX_INT | C_UART_PARITY_DIS;
	while(UART_INFO.txLen > 0);
#else
	const unsigned char *p = (const unsigned char *)buf;
	while(size-- > 0)
	{
		while(!(*P_UART_Command2 & C_UART_TX_RDY));
		*P_UART_Data = *p++;
	}
#endif
	return 0;
}

//=============================================================
// 语法格式：	int UART_Send_String(const char *str)
// 实现功能：	发送字符串
// 参数：		str - 发送缓冲区首地址
// 返回值：		0表示成功, -1表示失败
//=============================================================
int UART_Send_String(const char *str)
{
#ifdef USE_TXINT
	UART_INFO.txBuf = str;
	UART_INFO.txLen = strlen(str);
	*P_UART_Command1 = C_UART_TX_INT | C_UART_RX_INT | C_UART_PARITY_DIS;
	while(UART_INFO.txLen > 0);
#else
	while(*str != '\0')
	{
		while(!(*P_UART_Command2 & C_UART_TX_RDY));
		*P_UART_Data = *str++;
	}
#endif
	return 0;
}

//=============================================================
// 语法格式：	void IRQ7(void)
// 实现功能：	串口中断
// 参数：		无
// 返回值：		无
//=============================================================
void IRQ7(void)__attribute__((ISR));
void IRQ7(void)
{
	if(*P_UART_Command2 & C_UART_RX_RDY)
	{
		// 在这里可以处理接收到的数据
		(*UART_INFO.ProcessRxByte)(*P_UART_Data);
	}
#ifdef USE_TXINT
	else
	{
		if(UART_INFO.txLen-- > 0)
		
			*P_UART_Data = *UART_INFO.txBuf++;
		else
			*P_UART_Command1 = C_UART_RX_INT | C_UART_PARITY_DIS;
	}
#endif
}
