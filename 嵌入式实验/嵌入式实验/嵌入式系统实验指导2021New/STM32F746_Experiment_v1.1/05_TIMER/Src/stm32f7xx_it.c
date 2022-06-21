/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"

extern TIM_HandleTypeDef  TimHandle;

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/* This function handles TIM interrupt request */
void TIMx_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Enable peripheral clock #################################*/
  /* TIMx Peripheral clock enable */
  TIMx_CLK_ENABLE();
  
  /*##-2- Configure the NVIC for TIMx ########################################*/
  /* Set the TIMx priority */
  HAL_NVIC_SetPriority(TIMx_IRQn, 3, 0);

  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIMx_IRQn);
}
