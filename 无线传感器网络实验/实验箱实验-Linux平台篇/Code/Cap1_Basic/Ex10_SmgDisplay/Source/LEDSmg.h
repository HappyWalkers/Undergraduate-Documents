/***********************************************************
**  FileName:         LEDSmg.h
**  Introductions:    CC2530 Sensor Instrument LED & SMG(数码管) Function
**  Last Modify time: 2013.05.28
**  Modify:           数码管小数点显示有误，已检查更新OK
**  Author:           GuoZhenjiang <zhenjiang.guo@sunplusapp.com>
***********************************************************/

#ifndef __LEDSMG_H__
#define __LEDSMG_H__

#include "Basic.h"

#define PSEL_LED    P2SEL
#define PDIR_LED    P2DIR
#define BIT_LED     0
#define POUT_LED    P2
#define LED_ON      POUT_LED &= BIT_0(BIT_LED)
#define LED_OFF     POUT_LED |= BIT_1(BIT_LED)
// 数码管端口功能设置寄存器
#define PSEL_SMG_1  P1SEL
#define PSEL_SMG_2  P1SEL
#define PSEL_SMG_3  P1SEL
#define PSEL_SMG_4  P1SEL
// 数码管端口方向设置寄存器
#define PDIR_SMG_1  P1DIR
#define PDIR_SMG_2  P1DIR
#define PDIR_SMG_3  P1DIR
#define PDIR_SMG_4  P1DIR
// 数码管输出端口寄存器
#define POUT_SMG_1  P1
#define POUT_SMG_2  P1
#define POUT_SMG_3  P1
#define POUT_SMG_4  P1
// 各数码管对应端口的位
#define BIT_SMG_1   3
#define BIT_SMG_2   4
#define BIT_SMG_3   5
#define BIT_SMG_4   6

#define SEL_SMG_NONE    do{ POUT_SMG_1 &= ~BIT_0(BIT_SMG_1);\
                            POUT_SMG_2 &= ~BIT_0(BIT_SMG_2);\
                            POUT_SMG_3 &= ~BIT_0(BIT_SMG_3);\
                            POUT_SMG_4 &= ~BIT_0(BIT_SMG_4);\
                          }while(0)
#define SEL_SMG_ALL     do{ POUT_SMG_1 |= BIT_1(BIT_SMG_1);\
                            POUT_SMG_2 |= BIT_1(BIT_SMG_2);\
                            POUT_SMG_3 |= BIT_1(BIT_SMG_3);\
                            POUT_SMG_4 |= BIT_1(BIT_SMG_4);\
                          }while(0)
#define SEL_SMG_1       do{ SEL_SMG_NONE;  POUT_SMG_1 |= BIT_1(BIT_SMG_1); }while(0)
#define SEL_SMG_2       do{ SEL_SMG_NONE;  POUT_SMG_2 |= BIT_1(BIT_SMG_2); }while(0)
#define SEL_SMG_3       do{ SEL_SMG_NONE;  POUT_SMG_3 |= BIT_1(BIT_SMG_3); }while(0)
#define SEL_SMG_4       do{ SEL_SMG_NONE;  POUT_SMG_4 |= BIT_1(BIT_SMG_4); }while(0)

// 和上面对应的
typedef enum
{
    Smg1,
    Smg2,
    Smg3,
    Smg4,
    SmgAll,
    SmgNone,
}AvaliableSmg_t;

// 小数点显示操作
#define SMG_POINT(x)    (x |= 0x80)

// 4个8段共阴数码管通过74HC595串行控制
#define PSEL_595    P1SEL   // 595所在端口功能控制寄存器
#define PDIR_595    P1DIR   // 595所在端口方向控制寄存器
#define PDAT_595    P1      // 595输出数据寄存器

#define BIT_SER_595 0
#define BIT_RCK_595 1
#define BIT_SCK_595 2

#define SER_595_H   PDAT_595 |= BIT_1(BIT_SER_595)     // 595串行输入数据
#define RCK_595_H   PDAT_595 |= BIT_1(BIT_RCK_595)     // 595并行输出所存,上升沿更新,其他保持
#define SCK_595_H   PDAT_595 |= BIT_1(BIT_SCK_595)     // 595串行输入时钟,上升沿更新,其他保持

#define SER_595_L   PDAT_595 &= BIT_0(BIT_SER_595)
#define RCK_595_L   PDAT_595 &= BIT_0(BIT_RCK_595)
#define SCK_595_L   PDAT_595 &= BIT_0(BIT_SCK_595)

// LED流水灯初始化
void LEDInit(void);
// 数码管初始化
void SmgInit(void);
// 在第smgW个数码管上显示数字smgD,可选的小数点
void SmgDis(AvaliableSmg_t smgW, uint8 smgD, uint8 isPoint);
// 通过流水灯显示 ledData
void LEDDis(uint8 ledData);

#endif  //__LEDSMG_H__