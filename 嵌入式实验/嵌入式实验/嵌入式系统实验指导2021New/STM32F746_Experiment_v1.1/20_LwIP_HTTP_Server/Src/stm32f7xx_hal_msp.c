/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* ADC_MspInit */
void HAL_ADC_MspInit(ADC_HandleTypeDef *heth)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
  /* Enable GPIOF clock */
   __HAL_RCC_GPIOF_CLK_ENABLE();
   
   /* Configure PF10 as analog input */
  GPIO_InitStructure.Pin = GPIO_PIN_10;
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);
   
   /* ADC3 Periph clock enable */
   __HAL_RCC_ADC3_CLK_ENABLE();
}
