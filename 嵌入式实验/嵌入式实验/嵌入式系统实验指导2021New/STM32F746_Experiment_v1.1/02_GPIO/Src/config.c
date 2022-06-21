/**
  GPIO���ó���
**/

#include "main.h"

static GPIO_InitTypeDef  GPIO_InitStruct;

void GPIO_Config(void)
{
/* Enable each GPIO Clock (to be able to program the configuration registers) */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure IOs in output push-pull mode to drive external LED */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;	// �������
  GPIO_InitStruct.Pull  = GPIO_PULLUP;					// ����
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;			// ����

  GPIO_InitStruct.Pin = GPIO_PIN_8;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);				// ����ΪPA8
}
