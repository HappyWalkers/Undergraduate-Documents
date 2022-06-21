/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "system_init.h"
#include "cmsis_os.h"

osThreadId LEDThread1Handle, LEDThread2Handle;

static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);
void System_Init(void);

/* main function */
int main(void)
{
  System_Init();
  
  /* Initialize LED */
  BSP_LED_Init(LED1);
  
  /* Thread 1 definition */
  osThreadDef(Thread1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
  /* Thread 2 definition */
  osThreadDef(Thread2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
  /* Start thread 1 */
  LEDThread1Handle = osThreadCreate(osThread(Thread1), NULL);
  
  /* Start thread 2 */
  LEDThread2Handle = osThreadCreate(osThread(Thread2), NULL);
  
  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */
  for(;;);
}

/* Toggle LED1 thread*/
static void LED_Thread1(void const *argument)
{
  uint32_t count = 0;
  (void) argument;
  
  for(;;)
  {
    count = osKernelSysTick() + 5000;
    
    /* Toggle LED1 every 100 ms for 5 s */
    while (count >= osKernelSysTick())
    {
      BSP_LED_Toggle(LED1);
      
      osDelay(100);
    }
    
    /* Turn off LED1 */
    BSP_LED_Off(LED1);
    
    /* Suspend Thread 1 */
    osThreadSuspend(NULL);
    
    count = osKernelSysTick() + 5000;
    
    /* Toggle LED1 every 400 ms for 5 s */
    while (count >= osKernelSysTick())
    {
      BSP_LED_Toggle(LED1);
      
      osDelay(400);
    }
    
    /* Resume Thread 2 */
    osThreadResume(LEDThread2Handle); 
  }
}

/* Print to UART thread */
static void LED_Thread2(void const *argument)
{
  uint32_t count;
  (void) argument;
  
  for(;;)
  {
    count = osKernelSysTick() + 10000;
    
    /* Print to UART every 500 ms for 10 s */
    while (count >= osKernelSysTick())
    {
      printf("\r\nThread2 is running!\r\n");
      
      osDelay(500);
    }
    
    /* Resume Thread 1 */
    osThreadResume(LEDThread1Handle);
    
    /* Suspend Thread 2 */
    osThreadSuspend(NULL);  
  }
}
