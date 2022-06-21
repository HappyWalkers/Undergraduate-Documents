/*************************************************************
*   ����ܶ�̬��ʾ����4λ���������ʾ000.0-999.9,
*************************************************************/

#include "Basic.h"
#include "LEDSmg.h"

void main(void)
{
#define CH_TIME     100     // ���ڿ�����ʾ�������ۼӵ��ٶȣ���ֵԽС������Խ��
#define BT_TIME     200     // ���ڿ���ÿһλ������ʾ��ʱ�䣬��ֵԽ��ʱ��Խ��

    uint16 num, cnt;

    // ����ϵͳ����ʱ��Ƶ��Ϊ32MHz
    SYSTEM_CLK_SET_32M_OSC_NOSPD;
    // ����ܿ��ƶ˿ڳ�ʼ��
    SmgInit();

    // ������ʱ���������ϸ�����֮�࡭��
    for( ; ; )
    {
        for(num=0; num<10000; num++)
        {
            for(cnt=0; cnt<CH_TIME; cnt++)
            {
                SmgDis(Smg1, num%10000/1000, 0);    // ��λ
                delay_us(BT_TIME);
                SmgDis(Smg2, num%1000/100, 0);      // ʮλ
                delay_us(BT_TIME);
                SmgDis(Smg3, num%100/10, 1);        // ��λ
                delay_us(BT_TIME);
                SmgDis(Smg4, num%10/1, 0);          // С����λ
                delay_us(BT_TIME);
            }
        }
    }
}

