//======================================================
//  The information contained herein is the exclusive property of
//  SUNPLUSAPP Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNPLUSAPP TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  �������ƣ�	Ex_?
//  ����������	WiFiģ��ATָ�����ʵ��
//		1) ���ȷ���+++����ATģʽ,�ɹ�����"�ɹ�",���򲥱�"ʧ��"
//		2)	AT����ָ��ɹ���������"���ӳɹ�"��������������"����ʧ��"��
//		3)	��ѯ����״̬�ɹ�������������ǰ״̬��ʧ���򲥱�"����״̬��ѯʧ��"��
//		4)	3��ATָ�������Ϻ���������"ATָ��������"��

//  �漰�Ŀ⣺	CMacro1016.lib
//				sacmv26e.lib
//            	
//  ����ļ���	main.c��
//			wifi.c�ļ�, wifi.hͷ�ļ���
//			uart.c�ļ�, uart.hͷ�ļ���
//			isr.c��hardware.asm
//			Sound.c�ļ���Sound.hͷ�ļ���
//			s480.hͷ�ļ���s480.incͷ�ļ�
//	Ӳ�����ӣ�
//	ά����¼��	2011-12-5 v1.0
//===============================================
#include	"wifi/wifi.h"
#include	"sound/sound.h"

int main()
{
	int res;
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	*P_INT_Ctrl = C_IRQ5_2Hz|C_IRQ4_1KHz;						//��2Hz�жϣ�������ʱ�忴�Ź�����ʱ
	__asm("IRQ ON");
	// ��ʼ��Wifi
	Wifi_BasicInit();

	if(Wifi_GotoAtMode() == 1)  							  	// ����+++a����ATָ��
	{
		PlaySnd(_SUCCESS_72K_SA);								//�������� �ɹ�
	}
	else
	{
		PlaySnd(_FAIL_72K_SA);								//�������� ʧ��
	}

	if(Wifi_Check() == 1)  							  			// ����AT��ѯģ��״̬
	{
		PlaySnd(_LIANJIE_72K_SA);								//�������� ���ӳɹ�
		PlaySnd(_SUCCESS_72K_SA);
	}
	else
	{
		PlaySnd(_LIANJIE_72K_SA);								//�������� ����ʧ��
		PlaySnd(_FAIL_72K_SA);
	}

	res = Wifi_CheckLink();              						 // ��ѯģ��״̬
	if(res >= 0)
	{
		PlaySnd(_CUR_NET_72K_SA);								//�������� ��ǰ����״̬
		PlaySnd(res == 1 ? _ASS_72K_SA : _NO_ASS_72K_SA);
	}
	else
	{
		PlaySnd(_STATUS_INQ_72K_SA);							//�������� �����ѯ״̬ʧ��
		PlaySnd(_FAIL_72K_SA);
	}

	PlaySnd(_AT_FINISH_72K_SA); 								//�������� ATָ��������

	while(1)
	{
		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared
	}
}
