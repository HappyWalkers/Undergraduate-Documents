/**
  主程序：系统上电初始化后对LED1进行初始化，配置PC13作为外部中断源并开启中断，产生中断后点亮/熄灭LED。
**/
#include "main.h"
#include "system_init.h"

void System_Init(void);
void EXTI15_10_IRQHandler_Config(void);

/* main */
int main(void)
{
  System_Init();
  
  /* Initialize LED1 mounted on board */
  BSP_LED_Init(LED1);
  
  /* Configure EXTI15_10 (connected to PC.13 pin) in interrupt mode */
  EXTI15_10_IRQHandler_Config();
  
  while (1)
  {
  }
}

/* EXTI line detection callbacks, GPIO_Pin: Specifies the pins connected EXTI line */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)			//此处定义了HAL_GPIO_EXTI_Callback函数，原使用__weak  定义的函数被忽略?
{
  if (GPIO_Pin == GPIO_PIN_13)
  {
    /* Toggle LED1 */
    BSP_LED_Toggle(LED1);
    
    printf("\n\rLED1 switched\n\r");
  }
}
