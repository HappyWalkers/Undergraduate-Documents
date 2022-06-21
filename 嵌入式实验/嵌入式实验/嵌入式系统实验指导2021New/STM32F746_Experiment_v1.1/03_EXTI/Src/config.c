#include "main.h"

void EXTI15_10_IRQHandler_Config(void);

/* Configures EXTI lines 15 to 10 (connected to PC.13 pin) in interrupt mode */
void EXTI15_10_IRQHandler_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOC clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();
	
  /* Configure PC.13 pin as input floating */
  //GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;				// �жϴ�����ʽ���½��ش���
	//GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;				// �жϴ�����ʽ�������ش���
	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;				// �жϴ�����ʽ�������½��ش���
  GPIO_InitStructure.Pull = GPIO_NOPULL;								// GPIO�ڲ�������������
  GPIO_InitStructure.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);						// ��ʼ��PC13

  /* Enable and set EXTI lines 15 to 10 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);						// �����ж����ȼ�
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);										// ���ж�
}
