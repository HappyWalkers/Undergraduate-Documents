//======================================================
// 文件名称：	Sound.c
// 功能描述：	语音播放函数
// 维护记录：	2006-08-30	v1.0
//======================================================

#include "spce061a.h"
//#include "A2000.h"
#include "sound/s480.h"

//=============================================================
// 语法格式：	void PlaySnd(int SndIndex);
// 实现功能：	播放一段语音
// 参数：		SndIndex - 待播报语音的序号
// 返回值：		无
//=============================================================
void PlaySnd(int SndIndex)
{
	SACM_S480_Initial(1);							// 初始化为自动播放
	SACM_S480_Play(SndIndex, 3, 3);				// 开始播放一段语音
	while((SACM_S480_Status()&0x0001)!= 0)			// 是否播放完毕？
	{
		SACM_S480_ServiceLoop();					// 解码并填充队列
		*P_Watchdog_Clear = 0x01;
	}
	SACM_S480_Stop();								// 停止播放
}



