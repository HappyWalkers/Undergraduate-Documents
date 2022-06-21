/*****************************************************************************
 *  file name:  main.c
 *  brief:      ����������״̬���(P0.0�˿�) ͨ��UART0��ӡ�����
 *  data:       2014.03.17
 *  update:     ����ʵ���ļ�
 *  author:     <wei.song@sunplusapp.com>
*****************************************************************************/

/*****************************************************************************
    �������������������P0.0�˿�
*****************************************************************************/

#include "hal_wait.h"
#include "UART.h"
#include "Basic.h"
#include "string.h"

#define SENDSTRING  "\r\nThe Hall Sensor Value is:"

void main(void)
{
    uint8 hallSensorValue = 0;

    // ����ϵͳʱ�� ����32MHz�ⲿ����
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    while(CLKCONSTA & CLKCON_OSC)
        ;   // �ȴ�ʱ���ȶ�

    // ��ʼ�� LED�˿�(P2.0)
    P2SEL &= ~0x01;
    P2DIR |=  0x01;
    P2 |=  0x01;    // turn off LED after initlized.

    //��ʼ������������IOP0.0
    SetIOInput(0, 0, Pull_Up);

    //��ʼ��UART0��������115200
    Init_UART0(BAUD_115200,PERCFG_U0CFG_ALT1);

    while(1)
    {
        hallSensorValue = GetIOLevel(0, 0);

        UART0_Send(SENDSTRING, strlen(SENDSTRING));
        UART0_Dis_uNum((uint16)hallSensorValue);
        P2 &= ~0x01;  // �������к�ῴ��P2.0�˿����ӵ�LED��˸
        halMcuWaitMs(100);
        P2 |=  0x01;
        halMcuWaitMs(900);
    }
}