
#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2530.h>

//数据类型重命名
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned int uint16;
typedef unsigned char uint8;

//LED_D8_D9 操作
#define SET_LED_D8 (P2 &= 0XFE)  //点亮LED_D8
#define SET_LED_D9 (P1 &= 0XFD)  //点亮LED_D9
#define CLR_LED_D8 (P2 |= 0X01)  //熄灭LED_D8
#define CLR_LED_D9 (P1 |= 0X02)  //熄灭LED_D9

#define LED_D8_TURN (P2 ^= 0X01)  //改变LED_D8状态（亮变灭，灭变亮）
#define LED_D9_TURN (P1 ^= 0X02)  //改变LED_D9状态（亮变灭，灭变亮）

//微秒级短暂延时函数
void delay(uint);
//约10ms延时函数
void Delay(uint n);

//LED_D8_D9 端口初始化函数
void LEDPortInit(void);

//ADC通道0以8采样位获取输入
uint8 GetCh08bitADC(void);

//设置端口为三态输入
void SetIOInput(uint8 group, uint8 bit);
//设置端口为通用输出IO口
void SetIOOutput(uint8 group, uint8 bit);
//获取IO口输入电平状态
uint8 GetIOLevel(uint8 group, uint8 bit);
//设置IO端口输出电平状态
void SetIOLevel(uint8 group, uint8 bit, uint8 value);


#endif//__BASIC_H__