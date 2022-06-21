//======================================================
//  The information contained herein is the exclusive property of
//  SUNPLUSAPP Technology Co. And shall not be distributed, reproduced,
//  or disclosed in whole in part without prior written permission.
//  (C) COPYRIGHT 2011  SUNPLUSAPP TECHNOLOGY CO.
//  ALL RIGHTS RESERVED
//  The entire notice above must be reproduced on all authorized copies.
//========================================================
//============================================================
//  工程名称：	Ex_?
//  功能描述：	WiFi模块AT指令测试实验
//		1) 首先发送+++进入AT模式,成功播报"成功",否则播报"失败"
//		2)	AT联机指令成功语音播报"连接成功"，否则语音播报"连接失败"；
//		3)	查询网络状态成功，语音播报当前状态，失败则播报"网络状态查询失败"；
//		4)	3条AT指令测试完毕后，语音播报"AT指令测试完毕"。

//  涉及的库：	CMacro1016.lib
//				sacmv26e.lib
//            	
//  组成文件：	main.c、
//			wifi.c文件, wifi.h头文件、
//			uart.c文件, uart.h头文件、
//			isr.c、hardware.asm
//			Sound.c文件、Sound.h头文件、
//			s480.h头文件和s480.inc头文件
//	硬件连接：
//	维护记录：	2011-12-5 v1.0
//===============================================
#include	"wifi/wifi.h"
#include	"sound/sound.h"

int main()
{
	int res;
	*P_SystemClock = C_Fosc_49M | C_Fosc | C_StrongMode;
	*P_INT_Ctrl = C_IRQ5_2Hz|C_IRQ4_1KHz;						//开2Hz中断，用来定时清看门狗和延时
	__asm("IRQ ON");
	// 初始化Wifi
	Wifi_BasicInit();

	if(Wifi_GotoAtMode() == 1)  							  	// 发送+++a进入AT指令
	{
		PlaySnd(_SUCCESS_72K_SA);								//语音播报 成功
	}
	else
	{
		PlaySnd(_FAIL_72K_SA);								//语音播报 失败
	}

	if(Wifi_Check() == 1)  							  			// 发送AT查询模块状态
	{
		PlaySnd(_LIANJIE_72K_SA);								//语音播报 连接成功
		PlaySnd(_SUCCESS_72K_SA);
	}
	else
	{
		PlaySnd(_LIANJIE_72K_SA);								//语音播报 连接失败
		PlaySnd(_FAIL_72K_SA);
	}

	res = Wifi_CheckLink();              						 // 查询模块状态
	if(res >= 0)
	{
		PlaySnd(_CUR_NET_72K_SA);								//语音播报 当前网络状态
		PlaySnd(res == 1 ? _ASS_72K_SA : _NO_ASS_72K_SA);
	}
	else
	{
		PlaySnd(_STATUS_INQ_72K_SA);							//语音播报 网络查询状态失败
		PlaySnd(_FAIL_72K_SA);
	}

	PlaySnd(_AT_FINISH_72K_SA); 								//语音播报 AT指令测试完毕

	while(1)
	{
		*P_Watchdog_Clear = 0x0001;// Within a certain period, 0.75 seconds, watchdog  counter  must  be  cleared
	}
}
