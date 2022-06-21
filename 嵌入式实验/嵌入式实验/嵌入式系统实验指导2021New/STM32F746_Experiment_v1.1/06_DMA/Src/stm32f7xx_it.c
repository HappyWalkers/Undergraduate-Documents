/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"

extern DMA_HandleTypeDef   DmaHandle;

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/* This function handles DMA stream interrupt request */
void DMA_INSTANCE_IRQHANDLER(void)
{
  /* Check the interrupt and clear flag */
  HAL_DMA_IRQHandler(&DmaHandle);
}
