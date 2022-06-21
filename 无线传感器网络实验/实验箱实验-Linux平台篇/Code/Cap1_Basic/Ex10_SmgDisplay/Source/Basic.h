/***********************************************************
**  FileName:         Basic.h
**  Introductions:    Sunplusapp CC2530 ZigBee Node Basic Functions & Options
**  Last Modify time: 2012.05.28
**  Modify:           传感器实验仪中LED标号更改
**  Author:           GuoZhenjiang	<zhenjiang.guo@sunplusapp.com>
***********************************************************/

#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2530.h>

//数据类型重命名
typedef char int8;
typedef int int16;
typedef unsigned int uint16;
typedef unsigned char uint8;

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

//扩展板上 LED_D8_D9 控制
#define LED_4_ON   (P2 &= 0XFE)
#define LED_5_ON   (P1 &= 0XFD)
#define LED_4_OFF  (P2 |= 0X01)
#define LED_5_OFF  (P1 |= 0X02)
#define LED_4_TURN (P2 ^= 0X01)
#define LED_5_TURN (P1 ^= 0X02)

/***********************************************************
**  CC2530片内含有16MHz RC振荡器，和32.768kHz RC振荡器。
**  未初始化系统始终时，默认使用内部16MHz的RC时钟源
**  定时器预分频后的速度不能高于系统预分频后的速度，否则不能运行。
***********************************************************/
typedef enum
{
  //系统时钟源选择项
  CPU_32kHz_RC  = 0X80,
  CPU_32kHz_XOC = 0X00,
  //系统RTC时钟源选择项
  CPU_16MHz_RC  = 0X40,
  CPU_32MHz_XOC = 0X00,
  //定时器预分频设置，后面的数字表示系统时钟源的多少分之一
  TSPD_1        = ( 0X00 << 3), //32MHz  @ System Clock = 32MHz;
  TSPD_2        = ( 0X01 << 3), //16MHz  @ System Clock = 32MHz;
  TSPD_4        = ( 0X02 << 3), //8MHz   @ System Clock = 32MHz;
  TSPD_8        = ( 0X03 << 3), //4MHz   @ System Clock = 32MHz;
  TSPD_16       = ( 0X04 << 3), //2MHz   @ System Clock = 32MHz;
  TSPD_32       = ( 0X05 << 3), //1MHz   @ System Clock = 32MHz;
  TSPD_64       = ( 0X06 << 3), //500kHz @ System Clock = 32MHz;
  TSPD_128      = ( 0X07 << 3), //250kHz @ System Clock = 32MHz;
  //系统时钟预分频设置，后面的数字表示系统时钟源的多少分之一
  CLKSPD_1      = 0X00, //32MHz  @ System Clock = 32MHz;
  CLKSPD_2      = 0X01, //16MHz  @ System Clock = 32MHz;
  CLKSPD_4      = 0X02, //8MHz   @ System Clock = 32MHz;
  CLKSPD_8      = 0X03, //4MHz   @ System Clock = 32MHz;
  CLKSPD_16     = 0X04, //2MHz   @ System Clock = 32MHz;
  CLKSPD_32     = 0X05, //1MHz   @ System Clock = 32MHz;
  CLKSPD_64     = 0X06, //500kHz @ System Clock = 32MHz;
  CLKSPD_128    = 0X07, //250kHz @ System Clock = 32MHz;
}ClkSet_t;

/***********************************************************
**  CC2530每个通用IO引脚都可以产生中断！
***********************************************************/
typedef enum
{
  //中断触发方式选择
  None,     //关闭相应中断
  Rising,   //上升沿触发
  Falling,  //下降沿触发
}IntSel_t;

//典型系统始终设置
#define SYSTEM_CLK_SET_32M_OSC_NOSPD SystemClockSet( CPU_32kHz_XOC, CPU_32MHz_XOC, TSPD_1, CLKSPD_1 )

//系统始终设置函数
void SystemClockSet( ClkSet_t RTC_Clk, ClkSet_t CPU_Clk, ClkSet_t T_Spd, ClkSet_t CPU_Spd );
//短暂延时函数
void delay_us(uint16 t);
//约10ms延时函数
void delay_10ms(uint16 num_10ms);


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