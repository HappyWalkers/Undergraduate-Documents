/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"

/* This function handles SysTick Handler. */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/* This function handles SDIO global interrupt request. */
void SDMMC1_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
  BSP_SD_IRQHandler();
}

/* This function handles DMA2 Stream 3 interrupt request. */
void DMA2_Stream3_IRQHandler(void)
{
  BSP_SD_DMA_Rx_IRQHandler();
}

