#include "main.h"
#include "UART_Config.h"

/* UART handler declaration */
UART_HandleTypeDef Uart_Handle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Retargets the C library printf function to the USART */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&Uart_Handle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

void UART_Config(void)
{	
  /* Configure the UART peripheral */
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit    = One Stop bit
      - Parity      = NONE parity
      - BaudRate    = 115200 baud
      - Hardware flow control disabled */
  Uart_Handle.Instance        = USARTx;									// 选择串口
  Uart_Handle.Init.BaudRate   = 115200;									// 波特率：115200
  Uart_Handle.Init.WordLength = UART_WORDLENGTH_8B;			// 数据位：8位
  Uart_Handle.Init.StopBits   = UART_STOPBITS_1;				// 停止位：1位
  Uart_Handle.Init.Parity     = UART_PARITY_NONE;				// 奇偶校验：无
  Uart_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;		// 数据流控制：无
  Uart_Handle.Init.Mode       = UART_MODE_TX_RX;				// 串口模式：收发
  
  HAL_UART_Init(&Uart_Handle);
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Activate the OverDrive to reach the 216 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}

void Sys_Init(void)
{
	/* STM32F7xx HAL library initialization */
  HAL_Init();

  /* Configure the system clock to 216 MHz */
  SystemClock_Config();
	
  /* Configure the GPIO for LED1 */
  BSP_LED_Init(LED1);
}
