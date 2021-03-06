/*****************************************************************************
 *  file name:  main.c
 *  brief:      P2.0端口上的LED D8(低有效) 周期性闪烁
 *  data:       2014.03.17
 *  update:     创建实验文件
 *  author:     <wei.song@sunplusapp.com>
*****************************************************************************/

#include "iocc2541.h"
// 延时函数声明
void delay_10ms(unsigned int num_10ms);

void main(void)
{
    P2SEL &= ~0x01; // &= 1111 1110 通用IO
    P2DIR |=  0x01; // |= 0000 0001 输出
    for( ; ; )
    {
        P2 &= ~0x01;    // 点亮P2.0端口上连接的LED D8
        delay_10ms(5);
        P2 |=  0x01;    // 熄灭LED D8
        delay_10ms(60);
    }
}

/***********************************************************
**  函数名称: delay_10ms
**  实现功能: 延时函数
**  入口参数: num_10ms:要延时值的 10ms 个数;
**  返回结果: None
***********************************************************/
void delay_10ms(unsigned int num_10ms)
{
  unsigned int i, j, k;
  for(i=0; i<num_10ms; i++)
    for(j=0; j<100; j++)
      for(k=0; k<100; k++)
        ;
}
