/***************************************************************
ѧϰunSP IDE���ɿ���������ѧϰ�û�����C���Գ���ı�д��
ʵ�ֹ��ܣ���1��100�����ۼӣ����Ѽ����������ڱ���Sum�С�
ʵ�����󣺴򿪱����۲촰�ڹ۲����Sum�ı仯���ۼӽ���ʱ����SumΪ5050��16���Ʊ�ʾΪ0x13BA����
***************************************************************/
#include "SPCE061A.h"

int main()
{
	int Sum=0;
	unsigned char i;

	for(i=0;i<=100;i++)
		Sum += i;
	while(1)
	{
		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared
	}
}
