
//========================================================
//	�������ƣ�	ex2_S480_Auto
//	����������	
//				ͨ��S480�Զ���ʽ����������Դ
//	�漰�Ŀ⣺	CMacro1016.lib
//				sacmv26e.lib
//	����ļ���	main.c
//				hardware.asm  isr.asm
//				hardware.inc  s480.inc
//				s480.h
//	Ӳ�����ӣ�	
//	ά����¼��
//========================================================

//========================================================
//	�ļ����ƣ�	main.c
//	����������	ͨ��S480�Զ���ʽ����������Դ
//	ά����¼��
//========================================================

#include "s480.h"
#include "hardware.h"

#define P_Watchdog_Clear		(volatile unsigned int *)0x7012

void PlaySnd_Auto(unsigned int uiSndIndex,unsigned int uiDAC_Channel);

//========================================================
//	�﷨��ʽ��	int main(void)
//	ʵ�ֹ��ܣ�	�����������ź�����ͨ���Զ���ʽ����������Դ
//	������		��
//	����ֵ��	��
//========================================================

int main(void)
{
	while(1)
	{
		PlaySnd_Auto(0,3);
		PlaySnd_Auto(1,3);
		PlaySnd_Auto(2,3);
		*P_Watchdog_Clear = 0x0001;
	}
}

//========================================================
//	�﷨��ʽ��	void PlaySnd_Auto(unsigned int uiSndIndex,
//								unsigned int uiDAC_Channel)
//	ʵ�ֹ��ܣ�	ͨ���Զ���ʽ����������Դ
//	������		1.uiSndIndex��������Դ��� 
//				2.uiDAC_Channel����������ͨ��
//	����ֵ��	��
//========================================================

void PlaySnd_Auto(unsigned int uiSndIndex,unsigned int uiDAC_Channel)
{
	SACM_S480_Initial(1);						//��ʼ��Ϊ�Զ����ŷ�ʽ
	SACM_S480_Play(uiSndIndex,uiDAC_Channel,3);	//����
	while((SACM_S480_Status() & 0x0001) != 0)
	{											//�жϲ���״̬���绹�ڲ��������ѭ��
		SACM_S480_ServiceLoop();				//����ϵͳ�������
		*P_Watchdog_Clear = 0x0001;			
	}	
	SACM_S480_Stop();							//ֹͣ����
}