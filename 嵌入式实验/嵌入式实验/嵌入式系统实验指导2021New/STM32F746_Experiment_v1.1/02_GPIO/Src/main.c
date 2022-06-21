/**
  主程序：系统上电初始化后对GPIO中的PA8进行配置，将其配置为输出端口并控制LED闪烁。
**/
#include "main.h"
#include "system_init.h"

/* Private variables */
uint16_t delay = 100;

void System_Init(void);
void GPIO_Config(void);

/* main */
int main(void)
{
  System_Init();
  
  GPIO_Config();
  
  printf("\n\rExample finished\n\r");
	
  /* Toggle IOs in an infinite loop */
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
    /* Insert delay */
    HAL_Delay(delay);
  }
}
