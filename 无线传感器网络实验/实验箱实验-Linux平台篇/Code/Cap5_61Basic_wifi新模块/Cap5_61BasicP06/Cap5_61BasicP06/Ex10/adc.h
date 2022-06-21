//======================================================
// 文件名称:   adc.h
// 功能描述：  SPCE061A模数转换器驱动头文件
// 维护记录：  2011-12-12	
//				
//======================================================
#ifndef	__ADC_h__
#define	__ADC_h__
//	write your header here
//void Delay(unsigned int Delays);
void ADC_Init(void);
unsigned int AD(void);
float Get_GuangzhaoSensor_Result(void);

#endif
