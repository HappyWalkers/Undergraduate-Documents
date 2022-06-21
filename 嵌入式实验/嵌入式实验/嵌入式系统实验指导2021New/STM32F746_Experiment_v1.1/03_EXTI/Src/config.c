#include "main.h"

void EXTI15_10_IRQHandler_Config(void);

/* Configures EXTI lines 15 to 10 (connected to PC.13 pin) in interrupt mode */
void EXTI15_10_IRQHandler_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOC clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();
	
  /* Configure PC.13 pin as input floating */
  //GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;				// 中断触发方式：下降沿触发
	//GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;				// 中断触发方式：上升沿触发
	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;				// 中断触发方式：上升下降沿触发
  GPIO_InitStructure.Pull = GPIO_NOPULL;								// GPIO内部无上拉或下拉
  GPIO_InitStructure.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);						// 初始化PC13

  /* Enable and set EXTI lines 15 to 10 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);						// 设置中断优先级
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);										// 开中断
}
