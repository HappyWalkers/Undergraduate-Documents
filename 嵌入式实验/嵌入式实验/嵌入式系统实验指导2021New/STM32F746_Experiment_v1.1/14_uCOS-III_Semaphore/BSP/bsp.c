/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                          STM32746G-PROTO
*                                         Evaluation Board
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_MODULE
#include  <os.h>
#include  <bsp.h>

#include  <stm32f7xx_hal.h>
#include "stm32756g_eval.h"
#include "lcd_log.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Texts to print out by UART */	
char text[40];

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	
extern void EXTI0_IRQHandler(void);

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/

#define  BSP_REG_DEM_CR                       (*(CPU_REG32 *)0xE000EDFC)
#define  BSP_REG_DWT_CR                       (*(CPU_REG32 *)0xE0001000)
#define  BSP_REG_DWT_CYCCNT                   (*(CPU_REG32 *)0xE0001004)
#define  BSP_REG_DBGMCU_CR                    (*(CPU_REG32 *)0xE0042004)

/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/

#define  BSP_DBGMCU_CR_TRACE_IOEN_MASK                   0x10
#define  BSP_DBGMCU_CR_TRACE_MODE_ASYNC                  0x00
#define  BSP_DBGMCU_CR_TRACE_MODE_SYNC_01                0x40
#define  BSP_DBGMCU_CR_TRACE_MODE_SYNC_02                0x80
#define  BSP_DBGMCU_CR_TRACE_MODE_SYNC_04                0xC0
#define  BSP_DBGMCU_CR_TRACE_MODE_MASK                   0xC0

#define  BSP_BIT_DEM_CR_TRCENA                    DEF_BIT_24

#define  BSP_BIT_DWT_CR_CYCCNTENA                 DEF_BIT_00

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                               BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*
*               (2) CPU instruction / data tracing requires the use of the following pins :
*                   (a) (1) Aysynchronous     :  PB[3]
*                       (2) Synchronous 1-bit :  PE[3:2]
*                       (3) Synchronous 2-bit :  PE[4:2]
*                       (4) Synchronous 4-bit :  PE[6:2]
*
*                   (c) The application may wish to adjust the trace bus width depending on I/O
*                       requirements.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    RCC_OscInitTypeDef  RCC_OscInitStruct;
    RCC_ClkInitTypeDef  RCC_ClkInitStruct;

    BSP_IntInit();
                                                               
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState       = RCC_HSI_OFF;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM       = 25u;
//    RCC_OscInitStruct.PLL.PLLN       = 432u;					/* PLLCLK    = (HSE / PLLM) * PLLN      = 432MHz.       */
//    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2; /* SYSCLK    = PLLCLK / PLLP            = 216MHz.       */
//    RCC_OscInitStruct.PLL.PLLQ       = 9u;						
		RCC_OscInitStruct.PLL.PLLN       = 400u;					/* PLLCLK    = (HSE / PLLM) * PLLN      = 400MHz.       */
    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2; /* SYSCLK    = PLLCLK / PLLP            = 200MHz.       */
    RCC_OscInitStruct.PLL.PLLQ       = 8u;						
		HAL_RCC_OscConfig(&RCC_OscInitStruct);

    if(HAL_PWREx_EnableOverDrive() != HAL_OK) {                 /* Activate the OverDrive to reach the 216 Mhz Freq     */
        while (DEF_TRUE) {
            ;
        }
    }

    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_SYSCLK |
                                       RCC_CLOCKTYPE_HCLK   |
                                       RCC_CLOCKTYPE_PCLK1  |
                                       RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;         /* HCLK    = AHBCLK  = PLL / AHBPRES(1) = 216MHz.       */
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;           /* APB1CLK = AHBCLK  / APB1DIV(4)       = 54MHz (max).  */
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;           /* APB2CLK = AHBCLK  / APB2DIV(2)       = 108MHz.       */
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);

    BSP_LED_Init(LED1);                                             /* Init LED1.                                           */
		EXTILine0_Config();																					/* Configure EXTI Line0                                 */
		BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_GPIO);								/* Configure TAMPER Button                              */
#ifdef TRACE_EN                                                 /* See project / compiler preprocessor options.         */
    BSP_CPU_REG_DBGMCU_CR |=  BSP_DBGMCU_CR_TRACE_IOEN_MASK;    /* Enable tracing (see Note #2).                        */
    BSP_CPU_REG_DBGMCU_CR &= ~BSP_DBGMCU_CR_TRACE_MODE_MASK;    /* Clr trace mode sel bits.                             */
    BSP_CPU_REG_DBGMCU_CR |=  BSP_DBGMCU_CR_TRACE_MODE_SYNC_04; /* Cfg trace mode to synch 4-bit.                       */
#endif
}


/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    CPU_INT32U  hclk_freq;


    hclk_freq = HAL_RCC_GetHCLKFreq();
    return (hclk_freq);
}


/*
*********************************************************************************************************
*                                            HAL_InitTick()
*
* Description : This function has been overwritten from the STM32F4xx HAL libraries because Micrium's RTOS
*               has its own Systick initialization and because it is recomended to initialize the tick after
*               multi-tasking has started.
*
* Argument(s) : TickPriority          Tick interrupt priority.
*
* Return(s)   : HAL_OK.
*
* Caller(s)   : HAL_InitTick ()) is called automatically at the beginning of the program after reset by
*               HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
*
* Note(s)     : none.
*********************************************************************************************************
*/

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    HAL_NVIC_SetPriorityGrouping(0);

    if (OSRunning > 0u) {                                       /*Check if multi-tasking has started.                   */
        BSP_Tick_Init();
    }

    return (HAL_OK);
}


/*
*********************************************************************************************************
*                                            BSP_Tick_Init()
*
* Description : Initialize all the peripherals that required OS Tick services (OS initialized)
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void BSP_Tick_Init (void)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */

#if (OS_VERSION >= 30000u)
    cnts  = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;       /* Determine nbr SysTick increments.                    */
#else
    cnts  = cpu_clk_freq / (CPU_INT32U)OS_TICKS_PER_SEC;        /* Determine nbr SysTick increments.                    */
#endif

    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */
}

/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __GPIOA_CLK_ENABLE();
  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
//  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
//  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	BSP_IntVectSet(EXTI0_IRQn, EXTI0_IRQHandler);
  BSP_IntEn(EXTI0_IRQn);
}

/**
  * @brief  Configurates the BSP.
  * @param  None
  * @retval None
  */
void BSP_LCD_Config(void)
{
  /* Initialize the LCD */
  BSP_LCD_Init();
  
  /* Initialise the LCD Layers */
  BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
  
  /* Set LCD Foreground Layer  */
  BSP_LCD_SelectLayer(1);
  
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  
  /* Initialize LCD Log module */
  LCD_LOG_Init();
  
  /* Show Header and Footer texts */
  LCD_LOG_SetHeader((uint8_t *)"uCOS-III Semaphores Example");
  LCD_LOG_SetFooter((uint8_t *)"STM327x6G-EVAL board");
	
	BSP_LCD_DisplayStringAtLine(4, (uint8_t *)"> Testing Method:");
	BSP_LCD_DisplayStringAtLine(5, (uint8_t *)"1: Connect the Serial Cable to The DB9 Connector.");
	BSP_LCD_DisplayStringAtLine(6, (uint8_t *)"2: Run hypertrm.exe.");
	BSP_LCD_DisplayStringAtLine(7, (uint8_t *)"3: BaudRate = 115200.");
	BSP_LCD_DisplayStringAtLine(8, (uint8_t *)"4: Hardware Flow Control Disabled.");
}

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

