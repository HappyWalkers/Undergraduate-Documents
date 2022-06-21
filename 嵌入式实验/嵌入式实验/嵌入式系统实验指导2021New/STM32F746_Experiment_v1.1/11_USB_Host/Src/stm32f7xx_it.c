/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"

extern HCD_HandleTypeDef hhcd;

/* This function handles SysTick Handler */
void SysTick_Handler(void)
{
  HAL_IncTick(); 
  Toggle_Leds();
}

/* This function handles USB-On-The-Go FS/HS global interrupt request */
#ifdef USE_USB_FS
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler(void)
#endif
{
  HAL_HCD_IRQHandler(&hhcd);
}

/* This function handles External line 5 to 9 interrupt request */
void EXTI9_5_IRQHandler(void)
{
  if(BSP_PB_GetState(BUTTON_JOY_DOWN) == RESET)			//JOY_DOWN_PIN
	{
		HAL_GPIO_EXTI_IRQHandler(JOY_DOWN_PIN);
	}
	else if(BSP_PB_GetState(BUTTON_JOY_UP) == RESET)	//JOY_UP_PIN
	{
		HAL_GPIO_EXTI_IRQHandler(JOY_UP_PIN);
	}
	else																							//JOY_LEFT_PIN
	{
		HAL_GPIO_EXTI_IRQHandler(JOY_LEFT_PIN);
	}
}

/* This function handles External lines 15 to 10 interrupt request */
void EXTI15_10_IRQHandler(void)
{
	if(BSP_PB_GetState(BUTTON_JOY_SEL) == RESET)	//JOY_SEL_PIN
	{
		HAL_GPIO_EXTI_IRQHandler(JOY_SEL_PIN);
	}
	else																					//JOY_RIGHT_PIN
	{
		HAL_GPIO_EXTI_IRQHandler(JOY_RIGHT_PIN);
	}
}
