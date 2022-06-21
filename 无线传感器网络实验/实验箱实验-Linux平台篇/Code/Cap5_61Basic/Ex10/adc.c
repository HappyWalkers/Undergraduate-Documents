//======================================================
// 文件名称:   adc.c
// 功能描述：  SPCE061A模数转换器驱动
// 维护记录：  2011-12-12	
//				
//======================================================
#include "SPCE061A.h"

/***************************************************************************
//【API 格式】：void ADC_Init(void)
//【功能说明】：ADC初始化
//【参    数】：无；
//【返 回 值】：无；
//【使用举例】：ADC_Init();
***************************************************************************/
void ADC_Init(void)
{
	*P_ADC_MUX_Ctrl = C_ADC_MUX_IOA6;                   
}
/***************************************************************************
//【API 格式】：unsigned int AD(void)
//【功能说明】：进行一次ADC转换
//【参    数】：无；
//【返 回 值】：AD转换结果；
//【使用举例】：uiDATA =AD();
***************************************************************************/
unsigned int AD(void)
{
	unsigned int uiDATA;
	while(!(*P_ADC_MUX_Ctrl&0x8000));
	uiDATA = *P_ADC_LINEIN_Data;
	return(uiDATA&0xffc0);
}
/***************************************************************************
//【API 格式】：float Get_GuangzhaoSensor_Result(void)
//【功能说明】：采集一次光照传感器的数据
//【参    数】：无；
//【返 回 值】：光敏电阻的电压；
//【使用举例】：uiDATA =AD();
***************************************************************************/
float Get_GuangzhaoSensor_Result(void)
{
	unsigned long int uiDATA;
	unsigned int i;
	float fVoltage;
	ADC_Init();				//AD初始化
	fVoltage=0.0;	
	*P_ADC_Ctrl = C_ADC_EN;
//		uiDATA = *P_ADC_LINEIN_Data;
	uiDATA =AD();
	uiDATA = 0;
	for(i=0;i<16;i++)
	{
		*P_Watchdog_Clear = 0x0001;
		uiDATA+=AD();
	}
	uiDATA >>=4;
	fVoltage = (float)uiDATA/(0xffc0)*5.0;
	return fVoltage;
}