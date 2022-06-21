
//========================================================
//	工程名称：	ex2_S480_Auto
//	功能描述：	
//				通过S480自动方式播放语音资源
//	涉及的库：	CMacro1016.lib
//				sacmv26e.lib
//	组成文件：	main.c
//				hardware.asm  isr.asm
//				hardware.inc  s480.inc
//				s480.h
//	硬件连接：	
//	维护记录：
//========================================================

//========================================================
//	文件名称：	main.c
//	功能描述：	通过S480自动方式播放语音资源
//	维护记录：
//========================================================

#include "s480.h"
#include "hardware.h"

#define P_Watchdog_Clear		(volatile unsigned int *)0x7012

void PlaySnd_Auto(unsigned int uiSndIndex,unsigned int uiDAC_Channel);

//========================================================
//	语法格式：	int main(void)
//	实现功能：	调用语音播放函数，通过自动方式播放语音资源
//	参数：		无
//	返回值：	无
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
//	语法格式：	void PlaySnd_Auto(unsigned int uiSndIndex,
//								unsigned int uiDAC_Channel)
//	实现功能：	通过自动方式播放语音资源
//	参数：		1.uiSndIndex：语音资源序号 
//				2.uiDAC_Channel：语音播放通道
//	返回值：	无
//========================================================

void PlaySnd_Auto(unsigned int uiSndIndex,unsigned int uiDAC_Channel)
{
	SACM_S480_Initial(1);						//初始化为自动播放方式
	SACM_S480_Play(uiSndIndex,uiDAC_Channel,3);	//播放
	while((SACM_S480_Status() & 0x0001) != 0)
	{											//判断播放状态，如还在播放则继续循环
		SACM_S480_ServiceLoop();				//播放系统服务程序
		*P_Watchdog_Clear = 0x0001;			
	}	
	SACM_S480_Stop();							//停止播放
}