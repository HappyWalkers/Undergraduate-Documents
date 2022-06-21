/*****************************************************************************
 *  file name:  main.c
 *  brief:      ����0�����Է����ַ�����HelloWorld!��
 *  data:       2014.03.17
 *  update:     ����ʵ���ļ�
 *  author:     <wei.song@sunplusapp.com>
*****************************************************************************/

#include "UART.h"
#include "hal_wait.h"
#include "string.h"
#define TESTTRING "HelloWorld!\n"

void main(void)
{
    // ����ϵͳʱ�� ����32MHz�ⲿ����
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    while(CLKCONSTA & CLKCON_OSC)
        ;   // �ȴ�ʱ���ȶ�

    // ��ʼ�� LED�˿�(P2.0)
    P2SEL &= ~0x01;
    P2DIR |=  0x01;
    P2 |=  0x01;    // turn off LED after initlized.

    // ��ʼ��UART0
    Init_UART0(BAUD_115200,PERCFG_U0CFG_ALT1);
    halMcuWaitMs(10);   // UART��ʼ��������˽����жϱ�־ ���϶�����ʱ����������һ�δ�ӡ�����롣
    while(1)
    {
        UART0_Send(TESTTRING, strlen(TESTTRING));
        P2 &= ~0x01;  // �������к�ῴ��P2.0�˿����ӵ�LED��˸
        halMcuWaitMs(100);
        P2 |=  0x01;
        halMcuWaitMs(900);
    }
}