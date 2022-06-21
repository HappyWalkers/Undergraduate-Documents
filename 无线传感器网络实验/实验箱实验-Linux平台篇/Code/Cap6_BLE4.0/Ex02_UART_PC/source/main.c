/*****************************************************************************
 *  file name:  main.c
 *  brief:      串口0周期性发送字符串“HelloWorld!”
 *  data:       2014.03.17
 *  update:     创建实验文件
 *  author:     <wei.song@sunplusapp.com>
*****************************************************************************/

#include "UART.h"
#include "hal_wait.h"
#include "string.h"
#define TESTTRING "HelloWorld!\n"

void main(void)
{
    // 设置系统时钟 启用32MHz外部晶振
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    while(CLKCONSTA & CLKCON_OSC)
        ;   // 等待时钟稳定

    // 初始化 LED端口(P2.0)
    P2SEL &= ~0x01;
    P2DIR |=  0x01;
    P2 |=  0x01;    // turn off LED after initlized.

    // 初始化UART0
    Init_UART0(BAUD_115200,PERCFG_U0CFG_ALT1);
    halMcuWaitMs(10);   // UART初始化后清除了接收中断标志 加上短暂延时，可消除第一次打印的乱码。
    while(1)
    {
        UART0_Send(TESTTRING, strlen(TESTTRING));
        P2 &= ~0x01;  // 正常运行后会看到P2.0端口连接的LED闪烁
        halMcuWaitMs(100);
        P2 |=  0x01;
        halMcuWaitMs(900);
    }
}