/***********************************************************
**  FileName:         Basic.h
**  Introductions:    Sunplusapp CC2541 BLE Node Basic Functions & Options
**  Last Modify time: 2013.12.03
**  Modify:           综合物联网实验箱升级版（蓝牙4.0）
**  Author:           songwei	<wei.song@sunplusapp.com>
***********************************************************/

#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2541.h>
#include "ioCC2541_bitdef.h"

#define BIT(x)    ( 1 << x  ) //位屏蔽
#define BIT_1(x)  (  BIT(x) ) //位置1用
#define BIT_0(x)  (~(BIT(x))) //位清0用

//端口作为输入时内部上下拉选择
typedef enum
{
  Pull_None,  //三态输入
  Pull_Up,    //上拉使能
  Pull_Down,  //下拉使能
}PullSet_t;

////扩展板上 LED_D8_D9 控制
//#define LED_4_ON   (P2 &= 0XFE)
//#define LED_5_ON   (P1 &= 0XFD)
//#define LED_4_OFF  (P2 |= 0X01)
//#define LED_5_OFF  (P1 |= 0X02)
//#define LED_4_TURN (P2 ^= 0X01)
//#define LED_5_TURN (P1 ^= 0X02)

/***********************************************************
**  CC2541每个通用IO引脚都可以产生中断！
***********************************************************/
typedef enum
{
  //中断触发方式选择
  None,     //关闭相应中断
  Rising,   //上升沿触发
  Falling,  //下降沿触发
}IntSel_t;


//扩展板上 LED_4_5 初始化
void LED_4_5_PortInit(void);

//设置端口输入模式
void SetIOInput(uint8 group, uint8 bit, PullSet_t pull);
//设置端口为输出
void SetIOOutput(uint8 group, uint8 bit);
//获取端口输入状态
uint8 GetIOLevel(uint8 group, uint8 bit);
//设置端口输出电平
void SetIOLevel(uint8 group, uint8 bit, uint8 value);
//设置端口中断触发方式
void IOIntteruptSet(uint8 group, uint8 bit, IntSel_t trigger);


#endif//__BASIC_H__