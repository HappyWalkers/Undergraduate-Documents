/*************************************************************
*   数码管动态显示，在4位数码管上显示000.0-999.9,
*************************************************************/

#include "Basic.h"
#include "LEDSmg.h"

void main(void)
{
#define CH_TIME     100     // 用于控制显示的数字累加的速度，该值越小，增加越快
#define BT_TIME     200     // 用于控制每一位数字显示的时间，该值越大，时间越长

    uint16 num, cnt;

    // 设置系统工作时钟频率为32MHz
    SYSTEM_CLK_SET_32M_OSC_NOSPD;
    // 数码管控制端口初始化
    SmgInit();

    // 粗略延时，并不是严格的秒表之类……
    for( ; ; )
    {
        for(num=0; num<10000; num++)
        {
            for(cnt=0; cnt<CH_TIME; cnt++)
            {
                SmgDis(Smg1, num%10000/1000, 0);    // 百位
                delay_us(BT_TIME);
                SmgDis(Smg2, num%1000/100, 0);      // 十位
                delay_us(BT_TIME);
                SmgDis(Smg3, num%100/10, 1);        // 个位
                delay_us(BT_TIME);
                SmgDis(Smg4, num%10/1, 0);          // 小数点位
                delay_us(BT_TIME);
            }
        }
    }
}

