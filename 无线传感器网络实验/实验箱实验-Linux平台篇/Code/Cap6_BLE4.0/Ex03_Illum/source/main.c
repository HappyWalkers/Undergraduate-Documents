/*****************************************************************************
 *  file name:  main.c
 *  brief:      光照度传感器状态检测(P0.0端口) 通过UART0打印检测结果
 *  data:       2014.03.17
 *  update:     创建实验文件
 *  author:     <wei.song@sunplusapp.com>
*****************************************************************************/

#include "ioCC2541_bitdef.h"
#include "ioCC2541.h"
#include "hal_wait.h"
#include "UART.h"
#include "Adc.h"
#include "string.h"

#define SENDSTRING  "\r\nThe illum Percentage is:"

void main(void)
{
    uint16  adc_result=0;
    uint16  ADC_Res_Per = 0;

    // 设置系统时钟 启用32MHz外部晶振
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    while(CLKCONSTA & CLKCON_OSC)
        ;   // 等待时钟稳定

    // 初始化 LED端口(P2.0)
    P2SEL &= ~0x01;
    P2DIR |=  0x01;
    P2 |=  0x01;    // turn off LED after initlized.

    // ADC 通道0 初始化，转换精度为12bits
    Init_ADC(CH0, Resolution_12);
    // UART0初始化
    Init_UART0(BAUD_115200, PERCFG_U0CFG_ALT1);

    while(1)
    {
        adc_result = 2047- ADC_Convert(Resolution_12);

        //100/2048=0.0488282.~0.05=5/100
        ADC_Res_Per =(adc_result*5) / 100;

        if(ADC_Res_Per > 100)
            ADC_Res_Per = 100;
        else if(ADC_Res_Per <= 0)
            ADC_Res_Per = 0;

        UART0_Send(SENDSTRING,strlen(SENDSTRING));
        UART0_Dis_uNum(ADC_Res_Per);

        P2 &= ~0x01;  // 正常运行后会看到P2.0端口连接的LED闪烁
        halMcuWaitMs(100);
        P2 |=  0x01;
        halMcuWaitMs(900);
    }
}