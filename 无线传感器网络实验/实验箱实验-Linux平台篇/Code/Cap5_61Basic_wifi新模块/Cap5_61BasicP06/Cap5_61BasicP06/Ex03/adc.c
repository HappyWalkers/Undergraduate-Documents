#include "SPCE061A.H"
/******************************************************
��API ��ʽ����void ADC_Init(void)
������˵������ADC��ʼ������;
����    �������ޣ�
���� �� ֵ�����ޣ�
��ʹ�þ�������ADC_Init ();
******************************************************/
void ADC_Init(void)
{
	*P_ADC_MUX_Ctrl = C_ADC_MUX_IOA0;
	*P_ADC_Ctrl = C_ADC_EN;
}
/******************************************************	
��API ��ʽ����unsigned int Get_ADC_Data(void);
������˵��������ȡADCת�����(10λ);
����    �������ޣ�
���� �� ֵ����ADCת�������
��ʹ�þ�������Result= Get_ADC_Data ();
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
////��API ��ʽ����float Get_GuangzhaoSensor_Result(void)
////������˵�������ɼ�һ�ι��մ�����������
////����    �������ޣ�
////���� �� ֵ������������ĵ�ѹ��
////��ʹ�þ�������uiDATA =AD();
//***************************************************************************/
//	unsigned long int uiDATA;
//	unsigned int i;
//	float fVoltage;
//	ADC_Init();				//AD��ʼ��
//	*P_ADC_Ctrl = C_ADC_EN;
//
//	uiDATA =AD();			//���Ե�һ��ת�����
//	uiDATA = 0;
//	for(i=0;i<16;i++)
//	{
//		*P_Watchdog_Clear = 0x0001;
//		uiDATA+=AD();
//	}
//	uiDATA >>=4;
//}