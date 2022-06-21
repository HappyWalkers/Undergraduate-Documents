/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"

extern QSPI_HandleTypeDef QSPIHandle;

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/* This function handles QUADSPI interrupt request */
void QUADSPI_IRQHandler(void)
{
  HAL_QSPI_IRQHandler(&QSPIHandle);
}
