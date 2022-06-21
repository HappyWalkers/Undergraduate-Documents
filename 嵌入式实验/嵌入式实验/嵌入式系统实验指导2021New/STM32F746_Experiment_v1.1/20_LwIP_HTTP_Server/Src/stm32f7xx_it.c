/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "main.h"
#include "stm32f7xx_it.h"

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  /* Update the LocalTime by adding 1 ms each SysTick interrupt */
  HAL_IncTick();
}

/* This function handles External line 8 interrupt request */
void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(MFX_IRQOUT_PIN);
}

