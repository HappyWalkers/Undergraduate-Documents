#ifndef	__SOUND_h__
#define	__SOUND_h__
//	write your header here
void PlaySnd(unsigned int SndIndex);

enum SndIndex{										// ����������Դ������
	_LIANJIE_72K_SA,	 //0
	_FAIL_72K_SA,			//1
	_SUCCESS_72K_SA,	//2
	_AT_FINISH_72K_SA,	 //3
	_STATUS_INQ_72K_SA, 	 //4 ����״̬��ѯ
	_CUR_NET_72K_SA,	 //5  ��ǰ����״̬
	_ASS_72K_SA,	 //6	������
	_NO_ASS_72K_SA, 	 //7 δ����
};

#endif
