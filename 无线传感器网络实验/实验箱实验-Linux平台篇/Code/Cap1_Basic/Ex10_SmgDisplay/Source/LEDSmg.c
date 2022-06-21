/***********************************************************
**  FileName:         LEDSmg.c
**  Introductions:    CC2530 Sensor Instrument LED & SMG(�����) Function
**  Last Modify time: 2013.05.28
**  Modify:           �����С������ʾ�����Ѽ�����OK
**  Author:           GuoZhenjiang <zhenjiang.guo@sunplusapp.com>
***********************************************************/

#include "LEDSmg.h"

// ���������0-F��ѡ
//                          0     1     2     3     4     5     6     7     8     9     A     b     C     d     E     F
unsigned char SmgNum[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5e, 0x79, 0x71};

/************************************************************
 * @fn		:HC595PortInit
 * @brief	:74HC595��ؿ��ƶ˿ڳ�ʼ��
 * @param	:None
 * @return	:None
 */
void HC595PortInit(void)
{
    // 74HC595��ؿ��ƶ˿ڳ�ʼ��
    PSEL_595 &= BIT_0(BIT_SER_595);
    PSEL_595 &= BIT_0(BIT_RCK_595);
    PSEL_595 &= BIT_0(BIT_SCK_595);

    PDIR_595 |= BIT_1(BIT_SER_595);
    PDIR_595 |= BIT_1(BIT_RCK_595);
    PDIR_595 |= BIT_1(BIT_SCK_595);
}

/************************************************************
 * @fn		:HC595Output
 * @brief	:74HC595���8λ��������
 * @param	:data:ͨ��595�������������
 * @return	:None
 */
void HC595Output(uint8 data)
{
    uint8 i;
    RCK_595_L;
    for(i=0; i<8; i++)
    {
        SCK_595_L;
        delay_us(1);
        if(data & (0x80 >> i))
            SER_595_H;
        else
            SER_595_L;
        SCK_595_H;
    }
    RCK_595_H;
}

/************************************************************
 * @fn		:LEDInit
 * @brief	:LED��ؿ��ƶ˿ڳ�ʼ��,��ʼ��������LEDϨ��
 * @param	:None
 * @return	:None
 */
void LEDInit(void)
{
    // LED��ˮ����ؿ��ƶ˿ڳ�ʼ��
    PSEL_LED &= BIT_0(BIT_LED);
    PDIR_LED |= BIT_1(BIT_LED);
    // 595�˿ڳ�ʼ��
    HC595PortInit();
    // ����LED��������λ,Ϩ������LED
    LED_OFF;
}

/************************************************************
 * @fn		:SmgInit
 * @brief	:�������ؿ��ƶ˿ڳ�ʼ��,��ʼ������������ܱ����
 * @param	:None
 * @return	:None
 */
void SmgInit(void)
{
    // ��ؿ��ƶ˿ڳ�ʼ��
    PSEL_SMG_1 &= BIT_0(BIT_SMG_1);
    PSEL_SMG_2 &= BIT_0(BIT_SMG_2);
    PSEL_SMG_3 &= BIT_0(BIT_SMG_3);
    PSEL_SMG_4 &= BIT_0(BIT_SMG_4);

    PDIR_SMG_1 |= BIT_1(BIT_SMG_1);
    PDIR_SMG_2 |= BIT_1(BIT_SMG_2);
    PDIR_SMG_3 |= BIT_1(BIT_SMG_3);
    PDIR_SMG_4 |= BIT_1(BIT_SMG_4);
    
    P1SEL &= ~0X80;
    P1DIR |= 0X80;
    P1_7=0;
    // 595�˿ڳ�ʼ��
    HC595PortInit();
    // �����ʾ
    SEL_SMG_NONE;
}

/************************************************************
 * @fn		:SmgDis
 * @brief	:�ڵ�smgW�����������ʾ����smgD,��ѡ��С����
 * @param	:smgW λѡ, smgD ��ѡ, isPoint �Ƿ���ʾС����
 * @return	:None
 */
void SmgDis( AvaliableSmg_t smgW, uint8 smgD, uint8 isPoint)
{
    // ������Ӱ,ʹ���������λѡ��Ч
    SEL_SMG_NONE;
    // С�����жϣ�������ܶ�ѡ�ź�
    if(isPoint)
        HC595Output(SmgNum[smgD] | 0x80);
    else
        HC595Output(SmgNum[smgD]);
    // �������λѡ�ź�
    switch(smgW)
    {
        case Smg1:      SEL_SMG_1;      break;
        case Smg2:      SEL_SMG_2;      break;
        case Smg3:      SEL_SMG_3;      break;
        case Smg4:      SEL_SMG_4;      break;
        case SmgAll:    SEL_SMG_ALL;    break;
        case SmgNone:   SEL_SMG_NONE;   break;
        default :       SEL_SMG_NONE;   break;
    }
}

/************************************************************
 * @fn		:SmgDis
 * @brief	:ͨ����ˮ����ʾ ledData
 * @param	:ledData:�͵�8��LED������ʾ������
 * @return	:None
 */
void LEDDis(uint8 ledData)
{
    // ��Ϩ������LED
    LED_OFF;
    // ͨ��595�Ͳ�������
    HC595Output(ledData);
    LED_ON;
}
