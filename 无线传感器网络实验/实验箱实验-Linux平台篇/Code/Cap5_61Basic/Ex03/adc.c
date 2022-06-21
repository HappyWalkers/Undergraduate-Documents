#include "SPCE061A.H"
/******************************************************
【API 格式】：void ADC_Init(void)
【功能说明】：ADC初始化函数;
【参    数】：无；
【返 回 值】：无；
【使用举例】：ADC_Init ();
******************************************************/
void ADC_Init(void)
{
	*P_ADC_MUX_Ctrl = C_ADC_MUX_IOA0;
	*P_ADC_Ctrl = C_ADC_EN;
}
/******************************************************	
【API 格式】：unsigned int Get_ADC_Data(void);
【功能说明】：获取ADC转换结果(10位);
【参    数】：无；
【返 回 值】：ADC转换结果；
【使用举例】：Result= Get_ADC_Data ();
******************************************************/
unsigned int Get_ADC_Data(void)
{
	unsigned int uiDATA;
	while(!(*P_ADC_MUX_Ctrl&0x8000));
	uiDATA = *P_ADC_LINEIN_Data;
	uiDATA >>= 6;
	return(uiDATA);
}
///***************************************************************************
////【API 格式】：float Get_GuangzhaoSensor_Result(void)
////【功能说明】：采集一次光照传感器的数据
////【参    数】：无；
////【返 回 值】：光敏电阻的电压；
////【使用举例】：uiDATA =AD();
//***************************************************************************/
//	unsigned long int uiDATA;
//	unsigned int i;
//	float fVoltage;
//	ADC_Init();				//AD初始化
//	*P_ADC_Ctrl = C_ADC_EN;
//
//	uiDATA =AD();			//忽略第一次转换结果
//	uiDATA = 0;
//	for(i=0;i<16;i++)
//	{
//		*P_Watchdog_Clear = 0x0001;
//		uiDATA+=AD();
//	}
//	uiDATA >>=4;
//}