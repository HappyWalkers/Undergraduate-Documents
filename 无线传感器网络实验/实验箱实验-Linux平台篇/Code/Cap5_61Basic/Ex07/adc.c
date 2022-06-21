//======================================================
// �ļ�����:   adc.c
// ����������  SPCE061Aģ��ת��������
// ά����¼��  2011-12-12	
//				
//======================================================
#include "SPCE061A.h"

/***************************************************************************
//��API ��ʽ����void ADC_Init(void)
//������˵������ADC��ʼ��
//����    �������ޣ�
//���� �� ֵ�����ޣ�
//��ʹ�þ�������ADC_Init();
***************************************************************************/
void ADC_Init(void)
{
	*P_ADC_MUX_Ctrl = C_ADC_MUX_IOA6;                   
}
/***************************************************************************
//��API ��ʽ����unsigned int AD(void)
//������˵����������һ��ADCת��
//����    �������ޣ�
//���� �� ֵ����ADת�������
//��ʹ�þ�������uiDATA =AD();
***************************************************************************/
unsigned int AD(void)
{
	unsigned int uiDATA;
	while(!(*P_ADC_MUX_Ctrl&0x8000));
	uiDATA = *P_ADC_LINEIN_Data;
	return(uiDATA&0xffc0);
}
/***************************************************************************
//��API ��ʽ����float Get_GuangzhaoSensor_Result(void)
//������˵�������ɼ�һ�ι��մ�����������
//����    �������ޣ�
//���� �� ֵ������������ĵ�ѹ��
//��ʹ�þ�������uiDATA =AD();
***************************************************************************/
float Get_GuangzhaoSensor_Result(void)
{
	unsigned long int uiDATA;
	unsigned int i;
	float fVoltage;
	ADC_Init();				//AD��ʼ��
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