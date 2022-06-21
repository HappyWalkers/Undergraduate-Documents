/**
  ������ϵͳ��ʼ����ʹ�ô���ͨ�Ŷ�Timer3���Զ����ؼĴ�����ARR����ֵ����ѡ��ͨ������Ԥ��Ƶ��
	��Timer3��ʱ��Ƶ������Ϊ10KHz�������úö�ʱ��������ʱ���жϡ�Timer3�ļ������Ĵ�����0��ʼ��10KHz��Ƶ�ʵ�����
	����ֵ����ARR�Ĵ����е���ֵʱ���������磬����ʱ���жϡ�
	ע�⣺�������У�ÿ����һ�ζ�ʱ���жϣ�LED����һ�����䣬��ģʽ1��LED��˸Ƶ��Ϊ0.5Hz��ģʽ2��LED��˸Ƶ��Ϊ5Hz
**/
#include "main.h"
#include "system_init.h"

#define TIMEOUT   1000000       // 1000 seconds

/* Prescaler declaration */
uint8_t uRxBuffer = '1';			// Ĭ��ѡ��ģʽ"1. 10000"
double ARRValue = 10000 - 1;// Ĭ��ARR�Ĵ���ֵΪ10000 - 1

extern UART_HandleTypeDef   UartHandle;
extern TIM_HandleTypeDef    TimHandle;

void System_Init(void);
void Timer_Config(uint16_t ARRValue);
    
/* main */
int main(void)
{
  System_Init();
	
	while (1) {
  
		printf("\n\r************************************\n\r");
		printf("* Timer counter frequency is 10KHz *\n\r* Upcounting mode                  *\n\r* Initial value is 0               *");
		printf("\n\r************************************\n\r");
		printf("\n\r Input data \n\r");

		uint8_t bef[10], aft[10], b = 0, a = 0;//bef:С����ǰ�����֣�aft��С���������֣�b��bef���±�a:aft�����±�
		uint8_t Flag = 1;//��־���ж��Ƿ���С����
		for (int i = 0; i < 10; ++ i ) {//����������ʮ���ַ�
			/* Receive data from UART */
			HAL_UART_Receive(&UartHandle, (uint8_t*)&uRxBuffer, 1, TIMEOUT);//���ܼ������룬���������uRxBuffer��������������ʾ���Զ���ĸ���
			printf("%c", uRxBuffer);//�����������ӡ�鿴
			if ((uRxBuffer >= '0' && uRxBuffer <= '9') || uRxBuffer == '.') { //�������ֵΪ0-9 ���� С���� �Ļ�
				if (uRxBuffer == '.'){//�������ΪС����
					Flag = 0;//��־λ��0����ʾ�Ѿ�����С����
					continue;//������һ��ѭ������ΪС���㲻��������ֵ�����
				}
				if (Flag) bef[b ++ ] = uRxBuffer - '0';//�����û����С���㣬�����ִ���bef
				else aft[a ++ ] = uRxBuffer - '0';//����С����֮�󣬽����ִ���aft
			} else break;//�����������ֵ����0-9����С���㣬���˳�ѭ��
		}
		printf("\n\r");//��ӡһ���س�����
		double ansbef = 0;//С����֮ǰ����ֵ
		for (int i = 0; i < b; ++ i) {//ѭ������С����֮ǰ��������ƴ��һ��
			ansbef = ansbef * 10 + bef[i];
		}
		
		double ansaft = 0;//С����֮�����ֵ
		for (int i = a - 1; i >= 0; -- i) {//ѭ������С����֮���������ƴ��һ��
			ansaft = ansaft * 0.1 + aft[i];
		}
		ansaft *= 0.1;//���һ��ѭ���꣬�ٳ���0.1
		
		ARRValue = ansbef + ansaft; //Ƶ�ʣ���С����֮ǰ��֮�������ƴ��һ��
		ARRValue = 1 / ARRValue;//���ڣ�Ƶ��֮��1����λ��1/10k s
		ARRValue *= 5000;//����
		
		printf("%lf", ARRValue);

		Timer_Config(ARRValue);	//ʹ��Tim3�������������ж�

		/* Start the TIM Base generation in interrupt mode */
		HAL_TIM_Base_Start_IT(&TimHandle);
		
		printf("\n\rExample finished\n\r");
	}
  
  while (1)
  {
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED1);
}
