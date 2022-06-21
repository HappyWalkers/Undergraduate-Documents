/*****************************************************************************
 *  file name:  main.c
 *  brief:      霍尔传感器状态检测(P0.0端口) 通过UART0打印检测结果
 *  data:       2014.03.17
 *  update:     创建实验文件
 *  author:     <wei.song@sunplusapp.com>
*****************************************************************************/

/*****************************************************************************
    霍尔传感器输出连接在P0.0端口
*****************************************************************************/

#include "hal_wait.h"
#include "UART.h"
#include "Basic.h"
#include "string.h"

#define SENDSTRING  "\r\nThe Hall Sensor Value is:"

void main(void)
{
    uint8 hallSensorValue = 0;

    // 设置系统时钟 启用32MHz外部晶振
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    while(CLKCONSTA & CLKCON_OSC)
        ;   // 等待时钟稳定

    // 初始化 LED端口(P2.0)
    P2SEL &= ~0x01;
    P2DIR |=  0x01;
    P2 |=  0x01;    // turn off LED after initlized.

    //初始化霍尔传感器IOP0.0
    SetIOInput(0, 0, Pull_Up);

    //初始化UART0，波特率115200
    Init_UART0(BAUD_115200,PERCFG_U0CFG_ALT1);

    while(1)
    {
        hallSensorValue = GetIOLevel(0, 0);

        UART0_Send(SENDSTRING, strlen(SENDSTRING));
        UART0_Dis_uNum((uint16)hallSensorValue);
        P2 &= ~0x01;  // 正常运行后会看到P2.0端口连接的LED闪烁
        halMcuWaitMs(100);
        P2 |=  0x01;
        halMcuWaitMs(900);
    }
}