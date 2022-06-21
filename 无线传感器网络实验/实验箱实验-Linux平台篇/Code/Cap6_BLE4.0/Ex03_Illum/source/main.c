/*****************************************************************************
 *  file name:  main.c
 *  brief:      ���նȴ�����״̬���(P0.0�˿�) ͨ��UART0��ӡ�����
 *  data:       2014.03.17
 *  update:     ����ʵ���ļ�
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

    // ����ϵͳʱ�� ����32MHz�ⲿ����
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    while(CLKCONSTA & CLKCON_OSC)
        ;   // �ȴ�ʱ���ȶ�

    // ��ʼ�� LED�˿�(P2.0)
    P2SEL &= ~0x01;
    P2DIR |=  0x01;
    P2 |=  0x01;    // turn off LED after initlized.

    // ADC ͨ��0 ��ʼ����ת������Ϊ12bits
    Init_ADC(CH0, Resolution_12);
    // UART0��ʼ��
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

        P2 &= ~0x01;  // �������к�ῴ��P2.0�˿����ӵ�LED��˸
        halMcuWaitMs(100);
        P2 |=  0x01;
        halMcuWaitMs(900);
    }
}