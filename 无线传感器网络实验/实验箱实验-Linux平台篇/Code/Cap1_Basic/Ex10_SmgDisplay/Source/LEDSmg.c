/***********************************************************
**  FileName:         LEDSmg.c
**  Introductions:    CC2530 Sensor Instrument LED & SMG(数码管) Function
**  Last Modify time: 2013.05.28
**  Modify:           数码管小数点显示有误，已检查更新OK
**  Author:           GuoZhenjiang <zhenjiang.guo@sunplusapp.com>
***********************************************************/

#include "LEDSmg.h"

// 共阴数码管0-F段选
//                          0     1     2     3     4     5     6     7     8     9     A     b     C     d     E     F
unsigned char SmgNum[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5e, 0x79, 0x71};

/************************************************************
 * @fn		:HC595PortInit
 * @brief	:74HC595相关控制端口初始化
 * @param	:None
 * @return	:None
 */
void HC595PortInit(void)
{
    // 74HC595相关控制端口初始化
    PSEL_595 &= BIT_0(BIT_SER_595);
    PSEL_595 &= BIT_0(BIT_RCK_595);
    PSEL_595 &= BIT_0(BIT_SCK_595);

    PDIR_595 |= BIT_1(BIT_SER_595);
    PDIR_595 |= BIT_1(BIT_RCK_595);
    PDIR_595 |= BIT_1(BIT_SCK_595);
}

/************************************************************
 * @fn		:HC595Output
 * @brief	:74HC595输出8位并行数据
 * @param	:data:通过595并行输出的数据
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
 * @brief	:LED相关控制端口初始化,初始化后所有LED熄灭
 * @param	:None
 * @return	:None
 */
void LEDInit(void)
{
    // LED流水灯相关控制端口初始化
    PSEL_LED &= BIT_0(BIT_LED);
    PDIR_LED |= BIT_1(BIT_LED);
    // 595端口初始化
    HC595PortInit();
    // 共阴LED公共端置位,熄灭所有LED
    LED_OFF;
}

/************************************************************
 * @fn		:SmgInit
 * @brief	:数码管相关控制端口初始化,初始化后所有数码管被清除
 * @param	:None
 * @return	:None
 */
void SmgInit(void)
{
    // 相关控制端口初始化
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
    // 595端口初始化
    HC595PortInit();
    // 清除显示
    SEL_SMG_NONE;
}

/************************************************************
 * @fn		:SmgDis
 * @brief	:在第smgW个数码管上显示数字smgD,可选的小数点
 * @param	:smgW 位选, smgD 段选, isPoint 是否显示小数点
 * @return	:None
 */
void SmgDis( AvaliableSmg_t smgW, uint8 smgD, uint8 isPoint)
{
    // 抑制重影,使所有数码管位选无效
    SEL_SMG_NONE;
    // 小数点判断，送数码管段选信号
    if(isPoint)
        HC595Output(SmgNum[smgD] | 0x80);
    else
        HC595Output(SmgNum[smgD]);
    // 送数码管位选信号
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
 * @brief	:通过流水灯显示 ledData
 * @param	:ledData:送到8个LED并行显示的数据
 * @return	:None
 */
void LEDDis(uint8 ledData)
{
    // 先熄灭所有LED
    LED_OFF;
    // 通过595送并行数据
    HC595Output(ledData);
    LED_ON;
}
