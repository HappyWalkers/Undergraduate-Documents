/***********************************************************
**  FileName:         Basic.h
**  Introductions:    Sunplusapp CC2541 BLE Node Basic Functions & Options
**  Last Modify time: 2013.12.03
**  Modify:           �ۺ�������ʵ���������棨����4.0��
**  Author:           songwei	<wei.song@sunplusapp.com>
***********************************************************/

#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2541.h>
#include "ioCC2541_bitdef.h"

#define BIT(x)    ( 1 << x  ) //λ����
#define BIT_1(x)  (  BIT(x) ) //λ��1��
#define BIT_0(x)  (~(BIT(x))) //λ��0��

//�˿���Ϊ����ʱ�ڲ�������ѡ��
typedef enum
{
  Pull_None,  //��̬����
  Pull_Up,    //����ʹ��
  Pull_Down,  //����ʹ��
}PullSet_t;

////��չ���� LED_D8_D9 ����
//#define LED_4_ON   (P2 &= 0XFE)
//#define LED_5_ON   (P1 &= 0XFD)
//#define LED_4_OFF  (P2 |= 0X01)
//#define LED_5_OFF  (P1 |= 0X02)
//#define LED_4_TURN (P2 ^= 0X01)
//#define LED_5_TURN (P1 ^= 0X02)

/***********************************************************
**  CC2541ÿ��ͨ��IO���Ŷ����Բ����жϣ�
***********************************************************/
typedef enum
{
  //�жϴ�����ʽѡ��
  None,     //�ر���Ӧ�ж�
  Rising,   //�����ش���
  Falling,  //�½��ش���
}IntSel_t;


//��չ���� LED_4_5 ��ʼ��
void LED_4_5_PortInit(void);

//���ö˿�����ģʽ
void SetIOInput(uint8 group, uint8 bit, PullSet_t pull);
//���ö˿�Ϊ���
void SetIOOutput(uint8 group, uint8 bit);
//��ȡ�˿�����״̬
uint8 GetIOLevel(uint8 group, uint8 bit);
//���ö˿������ƽ
void SetIOLevel(uint8 group, uint8 bit, uint8 value);
//���ö˿��жϴ�����ʽ
void IOIntteruptSet(uint8 group, uint8 bit, IntSel_t trigger);


#endif//__BASIC_H__