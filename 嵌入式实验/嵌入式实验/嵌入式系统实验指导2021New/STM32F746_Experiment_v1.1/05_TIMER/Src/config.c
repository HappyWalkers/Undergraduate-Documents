#include "main.h"

/* TIM handle declaration */
TIM_HandleTypeDef    TimHandle;
uint32_t uwPrescalerValue = 0;

void Timer_Config(uint16_t ARRValue)
{
  /* Compute the prescaler value to have TIMx counter clock equal to 10000 Hz */
  uwPrescalerValue = (uint32_t)((SystemCoreClock / 2) / 10000) - 1;

  /* Set TIMx instance */
  TimHandle.Instance = TIMx;

  /* Initialize TIMx peripheral */
  TimHandle.Init.Period            = ARRValue;						// ����ARR�Ĵ���
  TimHandle.Init.Prescaler         = uwPrescalerValue;		// ����Ԥ��Ƶ
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;	// ��������ģʽ
  TimHandle.Init.RepetitionCounter = 0;
  
  /* Timer Initialize */
  HAL_TIM_Base_Init(&TimHandle);													// ��ʼ��Timer3�����������õ���HAL_TIM_Base_Init
	//��HAL_TIM_Base_Init�����HAL_TIM_Base_MspInit�����жϣ� HAL_NVIC_SetPriority(TIMx_IRQn, 3, 0);HAL_NVIC_EnableIRQ(TIMx_IRQn);
    /* Initialize LED1 mounted on board */
  BSP_LED_Init(LED1);
  
}
