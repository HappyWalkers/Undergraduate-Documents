#ifndef	__SOUND_h__
#define	__SOUND_h__
//	write your header here
void PlaySnd(unsigned int SndIndex);

enum SndIndex{										// 所有语音资源的索引
	_LIANJIE_72K_SA,	 //0
	_FAIL_72K_SA,			//1
	_SUCCESS_72K_SA,	//2
	_AT_FINISH_72K_SA,	 //3
	_STATUS_INQ_72K_SA, 	 //4 网络状态查询
	_CUR_NET_72K_SA,	 //5  当前网络状态
	_ASS_72K_SA,	 //6	已连接
	_NO_ASS_72K_SA, 	 //7 未连接
};

#endif
