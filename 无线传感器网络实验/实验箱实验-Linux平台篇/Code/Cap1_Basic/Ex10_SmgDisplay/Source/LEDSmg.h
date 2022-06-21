/***********************************************************
**  FileName:         LEDSmg.h
**  Introductions:    CC2530 Sensor Instrument LED & SMG(�����) Function
**  Last Modify time: 2013.05.28
**  Modify:           �����С������ʾ�����Ѽ�����OK
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
// ����ܶ˿ڹ������üĴ���
#define PSEL_SMG_1  P1SEL
#define PSEL_SMG_2  P1SEL
#define PSEL_SMG_3  P1SEL
#define PSEL_SMG_4  P1SEL
// ����ܶ˿ڷ������üĴ���
#define PDIR_SMG_1  P1DIR
#define PDIR_SMG_2  P1DIR
#define PDIR_SMG_3  P1DIR
#define PDIR_SMG_4  P1DIR
// ���������˿ڼĴ���
#define POUT_SMG_1  P1
#define POUT_SMG_2  P1
#define POUT_SMG_3  P1
#define POUT_SMG_4  P1
// ������ܶ�Ӧ�˿ڵ�λ
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

// �������Ӧ��
typedef enum
{
    Smg1,
    Smg2,
    Smg3,
    Smg4,
    SmgAll,
    SmgNone,
}AvaliableSmg_t;

// С������ʾ����
#define SMG_POINT(x)    (x |= 0x80)

// 4��8�ι��������ͨ��74HC595���п���
#define PSEL_595    P1SEL   // 595���ڶ˿ڹ��ܿ��ƼĴ���
#define PDIR_595    P1DIR   // 595���ڶ˿ڷ�����ƼĴ���
#define PDAT_595    P1      // 595������ݼĴ���

#define BIT_SER_595 0
#define BIT_RCK_595 1
#define BIT_SCK_595 2

#define SER_595_H   PDAT_595 |= BIT_1(BIT_SER_595)     // 595������������
#define RCK_595_H   PDAT_595 |= BIT_1(BIT_RCK_595)     // 595�����������,�����ظ���,��������
#define SCK_595_H   PDAT_595 |= BIT_1(BIT_SCK_595)     // 595��������ʱ��,�����ظ���,��������

#define SER_595_L   PDAT_595 &= BIT_0(BIT_SER_595)
#define RCK_595_L   PDAT_595 &= BIT_0(BIT_RCK_595)
#define SCK_595_L   PDAT_595 &= BIT_0(BIT_SCK_595)

// LED��ˮ�Ƴ�ʼ��
void LEDInit(void);
// ����ܳ�ʼ��
void SmgInit(void);
// �ڵ�smgW�����������ʾ����smgD,��ѡ��С����
void SmgDis(AvaliableSmg_t smgW, uint8 smgD, uint8 isPoint);
// ͨ����ˮ����ʾ ledData
void LEDDis(uint8 ledData);

#endif  //__LEDSMG_H__