/**
  中断处理程序
**/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  HAL_IncTick();
}
