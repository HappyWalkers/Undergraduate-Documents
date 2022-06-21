/*
   主程序：系统上电后使对I2C接口进行配置，使用I2C接口将aTxBuffer中的内容写入EEPROM，
	 再将写入的数据从EEPROM中读出并发送至串口，比对写入和读出EEPROM的数据是否一致。
** EEPROM型号：AT24CM01
** 容量：131KB
** 页大小：256Byte
*/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup I2C_EEPROM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EEPROM_ADDRESS        0xA2
#define EEPROM_PAGESIZE       256   
#define START_WRITTING_ADDRESS	0x1F0

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define I2Cx_TIMEOUT_MAX                300
/* Maximum number of trials for HAL_I2C_IsDeviceReady() function */
#define EEPROM_MAX_TRIALS               300

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Buffer used for transmission */
//uint8_t aTxBuffer[] = " ****I2C EEPROM communication based on DMA****  ****I2C EEPROM communication based on DMA****  ****I2C EEPROM communication based on DMA**** ";
uint8_t aTxBuffer[] = "****I2C EEPROM communication based on DMA****\r\n****I2C EEPROM communication based on DMA****\r\n****I2C EEPROM communication based on DMA****\r\n";

/* Buffer used for reception */
char aRxBuffer[EEPROM_PAGESIZE * 2] = { 0 };	//  接收buffer空间大一些，防止DMA传输数据时把RAM数据覆盖掉

/* Useful variables during communication */
uint16_t Memory_Address;
uint16_t Start_Memory_Address;
int Remaining_Bytes;
/* Define idle bytes of an incomplete page of EEPROM */
unsigned int Idle_Bytes = 0;
/* Define bytes to write in an incomplete page of EEPROM */
unsigned int Write_Bytes = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
void UART_Config(void);
//HAL_StatusTypeDef I2C_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t* pMemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{	
  /* Enable the CPU Cache */
  CPU_CACHE_Enable();
  
  /* STM32F7xx HAL library initialization:
       - Configure the Flash ART accelerator on ITCM interface
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
  
  /* Configure the system clock to 216 MHz */
  SystemClock_Config();
  
  /* Configure LED1 */
  BSP_LED_Init(LED1);
	
	UART_Config();
  printf("\r\nSystem initialize success\r\n");

  /*##-1- Configure the I2C peripheral #######################################*/
  I2cHandle.Instance             = I2Cx;

  I2cHandle.Init.Timing          = EVAL_I2Cx_TIMING;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress1     = 0x00;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0x00;
  I2cHandle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* The board sends the message to EEPROM then reads it back */

  /*##-2- Start writing process ##############################################*/
  /* Initialize Remaining Bytes Value to TX Buffer Size */
  Remaining_Bytes = TXBUFFERSIZE;
  /* Initialize Memory address to 0 since EEPROM write will start from address 0 */
  Memory_Address = START_WRITTING_ADDRESS;
  
	/* If Memory_Address is not start of a page, write to an incomplete page */
	if ((Memory_Address & (EEPROM_PAGESIZE - 1)) != 0)
	{
		Idle_Bytes = EEPROM_PAGESIZE - (Memory_Address & (EEPROM_PAGESIZE - 1));
		Write_Bytes = Idle_Bytes > TXBUFFERSIZE ? TXBUFFERSIZE : Idle_Bytes;
		
		/* Write EEPROM_PAGESIZE */
    if(HAL_I2C_Mem_Write_DMA(&I2cHandle , (uint16_t)EEPROM_ADDRESS, Memory_Address, I2C_MEMADD_SIZE_16BIT, (uint8_t*)aTxBuffer, Write_Bytes)!= HAL_OK)
    {
      /* Writing process Error */
      Error_Handler();
    }

    /* Wait for the end of the transfer */
    /*  Before starting a new communication transfer, you need to check the current   
      state of the peripheral; if it's busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the 
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */  
    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
    {
    }

    /* Check if the EEPROM is ready for a new operation */
    while (HAL_I2C_IsDeviceReady(&I2cHandle, EEPROM_ADDRESS, EEPROM_MAX_TRIALS, I2Cx_TIMEOUT_MAX) == HAL_TIMEOUT);

    /* Wait for the end of the transfer */
    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
    {
    }

    /* Update Remaining bytes and Memory Address values */
    Remaining_Bytes -= Write_Bytes;
    Memory_Address += Write_Bytes;
	}
	
	/* Write the rest of data in TxBuffer */
  while (Remaining_Bytes > 0)
  {
    /* Write EEPROM_PAGESIZE */
    if(HAL_I2C_Mem_Write_DMA(&I2cHandle , (uint16_t)EEPROM_ADDRESS, Memory_Address, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(aTxBuffer + TXBUFFERSIZE - Remaining_Bytes), EEPROM_PAGESIZE)!= HAL_OK)
    {
      /* Writing process Error */
      Error_Handler();
    }

    /* Wait for the end of the transfer */
    /*  Before starting a new communication transfer, you need to check the current   
      state of the peripheral; if it抯 busy you need to wait for the end of current
      transfer before starting a new one.
      For simplicity reasons, this example is just waiting till the end of the 
      transfer, but application may perform other tasks while transfer operation
      is ongoing. */  
    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
    {
    }

    /* Check if the EEPROM is ready for a new operation */
    while (HAL_I2C_IsDeviceReady(&I2cHandle, EEPROM_ADDRESS, EEPROM_MAX_TRIALS, I2Cx_TIMEOUT_MAX) == HAL_TIMEOUT);

    /* Wait for the end of the transfer */
    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
    {
    }

    /* Update Remaining bytes and Memory Address values */
    Remaining_Bytes -= EEPROM_PAGESIZE;
    Memory_Address += EEPROM_PAGESIZE;
  }

	printf("\r\nWrite to EEPROM:\r\n%s\r\n", aTxBuffer);
	
  /*##-3- Start reading process ##############################################*/
  if (HAL_I2C_Mem_Read_DMA(&I2cHandle, (uint16_t)EEPROM_ADDRESS, START_WRITTING_ADDRESS, I2C_MEMADD_SIZE_16BIT, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
  {
    /* Reading process Error */
    Error_Handler();
  }

  /* Wait for the end of the transfer */
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
  {
  }
	
	aRxBuffer[RXBUFFERSIZE] = '\0';	// 添加字符串结束符
	printf("Read from EEPROM: \r\n%s\r\n", aRxBuffer);

  /* Infinite loop */
  while (1)
  {
		BSP_LED_Toggle(LED1);
		HAL_Delay(50);
  }
}

/**
  * @bwrief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
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

/**
  * @brief  Tx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report end of DMA Tx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Turn LED1 on: Transfer in transmission process is correct */
  BSP_LED_On(LED1);
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report end of DMA Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Transfer in reception process is correct */
}

/**
  * @brief  I2C error callbacks.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Transfer error in reception/transmission process */ 
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();

  /* Select SysClk as source of USART1 clocks */
  RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

  /* Enable USARTx clock */
  USARTx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

}

void UART_Config(void)
{
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = NONE parity
      - BaudRate = 115200 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance          = USARTx;
  
  UartHandle.Init.BaudRate     = 115200;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    while(1)
		{
		}
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF); 

  return ch;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
