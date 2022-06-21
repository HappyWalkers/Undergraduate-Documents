/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/* This function handles external lines 15 to 10 interrupt request */
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(TAMPER_BUTTON_PIN);
}
