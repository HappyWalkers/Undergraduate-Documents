/**
  ******************************************************************************
  * @file    stm32756g_eval.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    21-September-2015
  * @brief   This file provides a set of firmware functions to manage LEDs, 
  *          push-buttons and COM ports available on STM32756G-EVAL and STM32746G-EVAL
  *          evaluation board(MB1167) from STMicroelectronics.
  *
  @verbatim
            This driver requires the stm32756g_eval_io.c/.h files to manage the 
            IO module resources mapped on the MFX IO expander.
            These resources are mainly LEDs, Joystick push buttons, SD detect pin, 
            USB OTG power switch/over current drive pins, Camera plug pin, Audio
            INT pin
            The use of the above eval resources is conditioned by the "USE_IOEXPANDER"
            preprocessor define which is enabled by default for the STM327x6G-EVAL
            boards Rev A. However for Rev B boards these resources are disabled by default
            (except LED1 and LED2) and to be able to use them, user must add "USE_IOEXPANDER"
            define in the compiler preprocessor configuration (or any header file that
            is processed before stm32756g_eval.h).
            On the STM327x6G-EVAL RevB LED1 and LED2 are directly mapped on GPIO pins,
            to avoid the unnecessary overhead of code brought by the use of MFX IO 
            expander when no further evaluation board resources are needed by the 
            application/example.
            For precise details on the use of the MFX IO expander, you can refer to
            the description provided within the stm32756g_eval_io.c file header
  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32756g_eval.h"
#include "stm32756g_eval_io.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32756G_EVAL
  * @{
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL STM32756G-EVAL LOW LEVEL
  * @{
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL_Private_TypesDefinitions STM32756G-EVAL LOW LEVEL Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL_Private_Defines STM32756G-EVAL LOW LEVEL Private Defines
  * @{
  */
/**
 * @brief STM32756G EVAL BSP Driver version number V1.0.1
   */
#define __STM32756G_EVAL_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32756G_EVAL_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32756G_EVAL_BSP_VERSION_SUB2   (0x01) /*!< [15:8]  sub2 version */
#define __STM32756G_EVAL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32756G_EVAL_BSP_VERSION         ((__STM32756G_EVAL_BSP_VERSION_MAIN << 24)\
                                             |(__STM32756G_EVAL_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32756G_EVAL_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32756G_EVAL_BSP_VERSION_RC))
/**
  * @}
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL_Private_Macros STM32756G-EVAL LOW LEVEL Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL_Private_Variables STM32756G-EVAL LOW LEVEL Private Variables
  * @{
  */
const uint32_t GPIO_PIN[LEDn] = {LED1_PIN,
                                 LED2_PIN,
                                 LED3_PIN,
                                 LED4_PIN};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT,
                                      TAMPER_BUTTON_GPIO_PORT,
                                      KEY_BUTTON_GPIO_PORT,
                                      JOY_SEL_PIN_GPIO_PORT,
                                      JOY_DOWN_PIN_GPIO_PORT,
                                      JOY_LEFT_PIN_GPIO_PORT,
                                      JOY_RIGHT_PIN_GPIO_PORT,
                                      JOY_UP_PIN_GPIO_PORT};

const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN,
                                      TAMPER_BUTTON_PIN,
                                      KEY_BUTTON_PIN,
                                      JOY_SEL_PIN,
                                      JOY_DOWN_PIN,
                                      JOY_LEFT_PIN,
                                      JOY_RIGHT_PIN,
                                      JOY_UP_PIN};

const uint16_t BUTTON_IRQn[BUTTONn] = {WAKEUP_BUTTON_EXTI_IRQn,
                                       TAMPER_BUTTON_EXTI_IRQn,
                                       KEY_BUTTON_EXTI_IRQn,
                                       JOY_SEL_PIN_EXTI_IRQn,
                                       JOY_DOWN_PIN_EXTI_IRQn,
                                       JOY_LEFT_PIN_EXTI_IRQn,
                                       JOY_RIGHT_PIN_EXTI_IRQn,
                                       JOY_UP_PIN_EXTI_IRQn};

USART_TypeDef* COM_USART[COMn] = {EVAL_COM1};

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT};

GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};

const uint16_t COM_TX_AF[COMn] = {EVAL_COM1_TX_AF};

const uint16_t COM_RX_AF[COMn] = {EVAL_COM1_RX_AF};

static I2C_HandleTypeDef hEvalI2c;

/**
  * @}
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL_Private_FunctionPrototypes  STM32756G_EVAL LOW LEVEL Private Function Prototypes
  * @{
  */
static void     I2Cx_MspInit(void);
static void     I2Cx_Init(void);
#if defined(USE_IOEXPANDER)
static void     I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t  I2Cx_Read(uint8_t Addr, uint8_t Reg);
#endif /* USE_IOEXPANDER */     

static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void     I2Cx_Error(uint8_t Addr);

#if defined(USE_IOEXPANDER)
/* IOExpander IO functions */
void            IOE_Init(void);
void            IOE_ITConfig(void);
void            IOE_Delay(uint32_t Delay);
void            IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t        IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void            IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);

/* MFX IO functions */
void            MFX_IO_Init(void);
void            MFX_IO_DeInit(void);
void            MFX_IO_ITConfig(void);
void            MFX_IO_Delay(uint32_t Delay);
void            MFX_IO_Write(uint16_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         MFX_IO_Read(uint16_t Addr, uint8_t Reg);
uint16_t        MFX_IO_ReadMultiple(uint16_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void            MFX_IO_Wakeup(void);
void            MFX_IO_EnableWakeupPin(void);
#endif /* USE_IOEXPANDER */

/* AUDIO IO functions */
void            AUDIO_IO_Init(void);
void            AUDIO_IO_DeInit(void);
void            AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint16_t        AUDIO_IO_Read(uint8_t Addr, uint16_t Reg);
void            AUDIO_IO_Delay(uint32_t Delay);

/* CAMERA IO functions */
void            CAMERA_IO_Init(void);
void            CAMERA_Delay(uint32_t Delay);
void     CAMERA_IO_Write(uint8_t addr, uint8_t reg, uint8_t value);
uint8_t  CAMERA_IO_Read(uint8_t addr, uint8_t reg);
//void            CAMERA_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
//uint16_t        CAMERA_IO_Read(uint8_t Addr, uint16_t Reg);

/* I2C EEPROM IO function */
void                EEPROM_IO_Init(void);
HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
/**
  * @}
  */

/** @defgroup STM32756G_EVAL_LOW_LEVEL_Private_Functions STM32756G_EVAL LOW LEVEL Private Functions
  * @{
  */ 

  /**
  * @brief  This method returns the STM32756G EVAL BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32756G_EVAL_BSP_VERSION;
}

/**
  * @brief  Configures Ethernet Interrupt.
  * @param  None
  * @retval None
  */
void BSP_Ethernet_ITConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
	/* Enable the GPIO EXTI clock */
	__GPIOI_CLK_ENABLE();
	__SYSCFG_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = GPIO_PIN_8;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
	
	/* Enable and set GPIO EXTI Interrupt to the lowest priority */
	HAL_NVIC_SetPriority((IRQn_Type)(EXTI9_5_IRQn), 0x0F, 0x00);
	HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI9_5_IRQn));
}

/**
  * @brief  Configures LED on GPIO and/or on MFX.
  * @param  Led: LED to be configured. 
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;
  GPIO_TypeDef*     gpio_led;
	//Actualy only one LED
	switch(Led)
	{
		case LED1:
			/* Enable the GPIO_LED clock */
      LED1_GPIO_CLK_ENABLE();
			gpio_led = LED1_GPIO_PORT;
			break;
		case LED2:
			/* Enable the GPIO_LED clock */
      LED2_GPIO_CLK_ENABLE();
			gpio_led = LED2_GPIO_PORT;
			break;
		case LED3:
			/* Enable the GPIO_LED clock */
      LED3_GPIO_CLK_ENABLE();
			gpio_led = LED3_GPIO_PORT;
			break;
		case LED4:
			/* Enable the GPIO_LED clock */
      LED4_GPIO_CLK_ENABLE();
			gpio_led = LED4_GPIO_PORT;
			break;
		default:
			break;
	}
	/* Configure the GPIO_LED pin */
	gpio_init_structure.Pin = GPIO_PIN[Led];
	gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Pull = GPIO_PULLUP;
	gpio_init_structure.Speed = GPIO_SPEED_HIGH;

	HAL_GPIO_Init(gpio_led, &gpio_init_structure);
	
	/* By default, turn off LED */
	HAL_GPIO_WritePin(gpio_led, GPIO_PIN[Led], GPIO_PIN_SET);
}


/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be configured. 
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx 
  * @retval None
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;
  GPIO_TypeDef*     gpio_led;
	//Actualy only one LED
	switch(Led)
	{
		case LED1:
			gpio_led = LED1_GPIO_PORT;
			break;
		case LED2:
			gpio_led = LED2_GPIO_PORT;
			break;
		case LED3:
			gpio_led = LED3_GPIO_PORT;
			break;
		case LED4:
			gpio_led = LED4_GPIO_PORT;
			break;
		default:
			break;
	}
	/* Turn off LED */
	HAL_GPIO_WritePin(gpio_led, GPIO_PIN[Led], GPIO_PIN_RESET);
	/* Configure the GPIO_LED pin */
	gpio_init_structure.Pin = GPIO_PIN[Led];
	HAL_GPIO_DeInit(gpio_led, gpio_init_structure.Pin);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: LED to be set on 
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
	GPIO_TypeDef*     gpio_led;
	//Actualy only one LED
	switch(Led)
	{
		case LED1:
			gpio_led = LED1_GPIO_PORT;
			break;
		case LED2:
			gpio_led = LED2_GPIO_PORT;
			break;
		case LED3:
			gpio_led = LED3_GPIO_PORT;
			break;
		case LED4:
			gpio_led = LED4_GPIO_PORT;
			break;
		default:
			break;
	}
  HAL_GPIO_WritePin(gpio_led, GPIO_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED Off. 
  * @param  Led: LED to be set off
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
	GPIO_TypeDef*     gpio_led;
	//Actualy only one LED
	switch(Led)
	{
		case LED1:
			gpio_led = LED1_GPIO_PORT;
			break;
		case LED2:
			gpio_led = LED2_GPIO_PORT;
			break;
		case LED3:
			gpio_led = LED3_GPIO_PORT;
			break;
		case LED4:
			gpio_led = LED4_GPIO_PORT;
			break;
		default:
			break;
	}
	HAL_GPIO_WritePin(gpio_led, GPIO_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: LED to be toggled
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
	GPIO_TypeDef*     gpio_led;
	//Actualy only one LED
	switch(Led)
	{
		case LED1:
			gpio_led = LED1_GPIO_PORT;
			break;
		case LED2:
			gpio_led = LED2_GPIO_PORT;
			break;
		case LED3:
			gpio_led = LED3_GPIO_PORT;
			break;
		case LED4:
			gpio_led = LED4_GPIO_PORT;
			break;
		default:
			break;
	}
	HAL_GPIO_TogglePin(gpio_led, GPIO_PIN[Led]);
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button  
  *            @arg  BUTTON_KEY: Key Push Button
  * @param  Button_Mode: Button mode
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *            @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line 
  *                                    with interrupt generation capability
  * @note On STM32756G-EVAL evaluation board, the three buttons (Wakeup, Tamper
  *       and key buttons) are mapped on the same push button named "Wakeup/Tamper"
  *       on the board serigraphy.
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef gpio_init_structure;
  
  /* Enable the BUTTON clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    gpio_init_structure.Mode = GPIO_MODE_INPUT;
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    
    if(Button != BUTTON_WAKEUP)
    {
      gpio_init_structure.Mode = GPIO_MODE_IT_FALLING; 
    }
    else
    {
      gpio_init_structure.Mode = GPIO_MODE_IT_RISING;
    }
    
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button  
  *            @arg  BUTTON_KEY: Key Push Button
  * @note On STM32756G-EVAL evaluation board, the three buttons (Wakeup, Tamper
  *       and key buttons) are mapped on the same push button named "Wakeup/Tamper"
  *       on the board serigraphy.
  * @note PB DeInit does not disable the GPIO clock
  * @retval None
  */
void BSP_PB_DeInit(Button_TypeDef Button)
{
    GPIO_InitTypeDef gpio_init_structure;

    gpio_init_structure.Pin = BUTTON_PIN[Button];
    HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}


/**
  * @brief  Returns the selected button state.
  * @param  Button: Button to be checked
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button 
  *            @arg  BUTTON_KEY: Key Push Button
  * @note On STM32756G-EVAL evaluation board, the three buttons (Wakeup, Tamper
  *       and key buttons) are mapped on the same push button named "Wakeup/Tamper"
  *       on the board serigraphy.
  * @retval The Button GPIO pin value
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Configures COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1 
  *            @arg  COM2 
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  * @retval None
  */
void BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock */
  EVAL_COMx_TX_GPIO_CLK_ENABLE(COM);
  EVAL_COMx_RX_GPIO_CLK_ENABLE(COM);

  /* Enable USART clock */
  EVAL_COMx_CLK_ENABLE(COM);

  /* Configure USART Tx as alternate function */
  gpio_init_structure.Pin = COM_TX_PIN[COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Alternate = COM_TX_AF[COM];
  HAL_GPIO_Init(COM_TX_PORT[COM], &gpio_init_structure);

  /* Configure USART Rx as alternate function */
  gpio_init_structure.Pin = COM_RX_PIN[COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = COM_RX_AF[COM];
  HAL_GPIO_Init(COM_RX_PORT[COM], &gpio_init_structure);

  /* USART configuration */
  huart->Instance = COM_USART[COM];
  HAL_UART_Init(huart);
}

/**
  * @brief  DeInit COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1 
  *            @arg  COM2 
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  * @retval None
  */
void BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart)
{
  /* USART configuration */
  huart->Instance = COM_USART[COM];
  HAL_UART_DeInit(huart);

  /* Enable USART clock */
  EVAL_COMx_CLK_DISABLE(COM);

  /* DeInit GPIO pins can be done in the application 
     (by surcharging this __weak function) */

  /* GPIO pins clock, DMA clock can be shut down in the application 
     by surcharging this __weak function */
}

#if defined(USE_IOEXPANDER)
/**
  * @brief  Configures joystick GPIO and EXTI modes.
  * @param  JoyMode: Button mode.
  *          This parameter can be one of the following values:
  *            @arg  JOY_MODE_GPIO: Joystick pins will be used as simple IOs
  *            @arg  JOY_MODE_EXTI: Joystick pins will be connected to EXTI line 
  *                                 with interrupt generation capability  
  * @retval IO_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_JOY_Init(JOYMode_TypeDef Joy_Mode)
{
  uint8_t ret = 0;
  
  /* Initialize the IO functionalities */
  ret = BSP_IO_Init();
  
  /* Configure joystick pins in IT mode */
  if(Joy_Mode == JOY_MODE_EXTI)
  {
    /* Configure IO interrupt acquisition mode */
		BSP_PB_Init(BUTTON_JOY_SEL, BUTTON_MODE_EXTI);
		BSP_PB_Init(BUTTON_JOY_DOWN, BUTTON_MODE_EXTI);
		BSP_PB_Init(BUTTON_JOY_LEFT, BUTTON_MODE_EXTI);
		BSP_PB_Init(BUTTON_JOY_RIGHT, BUTTON_MODE_EXTI);
		BSP_PB_Init(BUTTON_JOY_UP, BUTTON_MODE_EXTI);
  }
  return ret; 
}

/**
  * @brief  DeInit joystick GPIOs.
  * @note   JOY DeInit does not disable the MFX, just set the MFX pins in Off mode
  * @retval None.
  */
void BSP_JOY_DeInit()
{
//    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_OFF);
}

/**
  * @brief  Returns the current joystick status.
  * @retval Code of the joystick key pressed
  *          This code can be one of the following values:
  *            @arg  JOY_NONE
  *            @arg  JOY_SEL
  *            @arg  JOY_DOWN
  *            @arg  JOY_LEFT
  *            @arg  JOY_RIGHT
  *            @arg  JOY_UP
  */
JOYState_TypeDef BSP_JOY_GetState(void)
{
	if(BSP_PB_GetState(BUTTON_JOY_SEL) == GPIO_PIN_RESET)
  {
		return(JOYState_TypeDef) JOY_SEL;
	}
	if(BSP_PB_GetState(BUTTON_JOY_DOWN) == GPIO_PIN_RESET)
  {
		return(JOYState_TypeDef) JOY_DOWN;
	}
	if(BSP_PB_GetState(BUTTON_JOY_LEFT) == GPIO_PIN_RESET)
  {
		return(JOYState_TypeDef) JOY_LEFT;
	}
	if(BSP_PB_GetState(BUTTON_JOY_RIGHT) == GPIO_PIN_RESET)
  {
		return(JOYState_TypeDef) JOY_RIGHT;
	}
	if(BSP_PB_GetState(BUTTON_JOY_UP) == GPIO_PIN_RESET)
  {
		return(JOYState_TypeDef) JOY_UP;
	}
	else
	{
		return(JOYState_TypeDef) JOY_NONE;
	}
}

/**
  * @brief  Check TS3510 touch screen presence
  * @retval Return 0 if TS3510 is detected, return 1 if not detected 
  */
uint8_t BSP_TS3510_IsDetected(void)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t error = 0;
  uint8_t a_buffer;
  
  uint8_t tmp_buffer[2] = {0x81, 0x08};
   
  /* Prepare for LCD read data */
  IOE_WriteMultiple(TS3510_I2C_ADDRESS, 0x8A, tmp_buffer, 2);

  status = HAL_I2C_Mem_Read(&hEvalI2c, TS3510_I2C_ADDRESS, 0x8A, I2C_MEMADD_SIZE_8BIT, &a_buffer, 1, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    error = (uint32_t)HAL_I2C_GetError(&hEvalI2c);

    /* I2C error occurred */
    I2Cx_Error(TS3510_I2C_ADDRESS);
    
    if(error == HAL_I2C_ERROR_AF)
    {
      return 1;
    }    
  }  
  return 0;
}
#endif /* USE_IOEXPANDER */

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/
/**
  * @brief  Initializes I2C MSP.
  * @retval None
  */
static void I2Cx_MspInit(void)
{
  GPIO_InitTypeDef  gpio_init_structure;
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();
  
  /* Configure I2C Tx as alternate function */
  gpio_init_structure.Pin = EVAL_I2Cx_SCL_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = EVAL_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);
  
  /* Configure I2C Rx as alternate function */
  gpio_init_structure.Pin = EVAL_I2Cx_SDA_PIN;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);
  
  /*** Configure the I2C peripheral ***/ 
  /* Enable I2C clock */
  EVAL_I2Cx_CLK_ENABLE();
  
  /* Force the I2C peripheral clock reset */  
  EVAL_I2Cx_FORCE_RESET(); 
  
  /* Release the I2C peripheral clock reset */  
  EVAL_I2Cx_RELEASE_RESET(); 
  
  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(EVAL_I2Cx_EV_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_EV_IRQn);
  
  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(EVAL_I2Cx_ER_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_ER_IRQn);
}

/**
  * @brief  Initializes I2C HAL.
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&hEvalI2c) == HAL_I2C_STATE_RESET)
  {
    hEvalI2c.Instance              = EVAL_I2Cx;
    hEvalI2c.Init.Timing           = EVAL_I2Cx_TIMING;
    hEvalI2c.Init.OwnAddress1      = 0;
    hEvalI2c.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    hEvalI2c.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    hEvalI2c.Init.OwnAddress2      = 0;
    hEvalI2c.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    hEvalI2c.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
    
    /* Init the I2C */
    I2Cx_MspInit();
    HAL_I2C_Init(&hEvalI2c);    
  }
}


#if defined(USE_IOEXPANDER)
/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
  */
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&hEvalI2c, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 100); 

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @retval Read data
  */
static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;
  
  status = HAL_I2C_Mem_Read(&hEvalI2c, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 1000);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
  return Value;   
}
#endif /* USE_IOEXPANDER */

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  if(Addr == EXC7200_I2C_ADDRESS)
  {
    status = HAL_I2C_Master_Receive(&hEvalI2c, Addr, Buffer, Length, 1000);  
  }
  else
  {
    status = HAL_I2C_Mem_Read(&hEvalI2c, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);
  }

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    I2Cx_Error(Addr);
  }
  return status;    
}

/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&hEvalI2c, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
  * @brief  Checks if target device is ready for communication. 
  * @note   This function is used with Memory devices
  * @param  DevAddress: Target device address
  * @param  Trials: Number of trials
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (HAL_I2C_IsDeviceReady(&hEvalI2c, DevAddress, Trials, 1000));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the I2C communication bus */
  HAL_I2C_DeInit(&hEvalI2c);
  
  /* Re-Initialize the I2C communication bus */
  I2Cx_Init();
}

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK IOE ***********************************/
#if defined(USE_IOEXPANDER)
/**
  * @brief  Initializes IOE low level.
  * @retval None
  */
void IOE_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  Configures IOE low level interrupt.
  * @retval None
  */
void IOE_ITConfig(void)
{
  /* STMPE811 IO expander IT config done by BSP_TS_ITConfig function */
}

/**
  * @brief  IOE writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
  */
void IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  IOE reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @retval Read data
  */
uint8_t IOE_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  IOE reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  IOE writes multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval None
  */
void IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
  I2Cx_WriteMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  IOE delay 
  * @param  Delay: Delay in ms
  * @retval None
  */
void IOE_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}
#endif /* USE_IOEXPANDER */

/********************************* LINK MFX ***********************************/

#if defined(USE_IOEXPANDER)
/**
  * @brief  Initializes MFX low level.
  * @retval None
  */
void MFX_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  DeInitializes MFX low level.
  * @retval None
  */
void MFX_IO_DeInit(void)
{
}

/**
  * @brief  Configures MFX low level interrupt.
  * @retval None
  */
void MFX_IO_ITConfig(void)
{
  static uint8_t mfx_io_it_enabled = 0;
  GPIO_InitTypeDef  gpio_init_structure;
  
  if(mfx_io_it_enabled == 0)
  {
    mfx_io_it_enabled = 1;
    /* Enable the GPIO EXTI clock */
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    
    gpio_init_structure.Pin   = GPIO_PIN_8;
    gpio_init_structure.Pull  = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_LOW;
    gpio_init_structure.Mode  = GPIO_MODE_IT_RISING;
    HAL_GPIO_Init(GPIOI, &gpio_init_structure);
    
    /* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(EXTI9_5_IRQn), 0x0F, 0x0F);
    HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI9_5_IRQn));
  }
}

/**
  * @brief  MFX writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
  */
void MFX_IO_Write(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write((uint8_t) Addr, Reg, Value);
}

/**
  * @brief  MFX reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @retval Read data
  */
uint8_t MFX_IO_Read(uint16_t Addr, uint8_t Reg)
{
  return I2Cx_Read((uint8_t) Addr, Reg);
}

/**
  * @brief  MFX reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t MFX_IO_ReadMultiple(uint16_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple((uint8_t)Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  MFX delay 
  * @param  Delay: Delay in ms
  * @retval None
  */
void MFX_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
  * @brief  Used by Lx family but requested for MFX component compatibility.
  * @retval None
  */
void MFX_IO_Wakeup(void) 
{
}

/**
  * @brief  Used by Lx family but requested for MXF component compatibility.
  * @retval None
  */
void MFX_IO_EnableWakeupPin(void) 
{
}

#endif /* USE_IOEXPANDER */

/********************************* LINK AUDIO *********************************/

/**
  * @brief  Initializes Audio low level.
  * @retval None
  */
void AUDIO_IO_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  Deinitializes Audio low level.
  * @param  None
  * @retval None
  */
void AUDIO_IO_DeInit(void)
{
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  * @retval None
  */
void AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value)
{
  uint16_t tmp = Value;
  
  Value = ((uint16_t)(tmp >> 8) & 0x00FF);
  
  Value |= ((uint16_t)(tmp << 8)& 0xFF00);
  
  I2Cx_WriteMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 2);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Data to be read
  */
uint16_t AUDIO_IO_Read(uint8_t Addr, uint16_t Reg)
{
  uint16_t read_value = 0, tmp = 0;
  
  I2Cx_ReadMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 2); 
  
  tmp = ((uint16_t)(read_value >> 8) & 0x00FF);
  
  tmp |= ((uint16_t)(read_value << 8)& 0xFF00);
  
  read_value = tmp;
  
  return read_value;
}

/**
  * @brief  AUDIO Codec delay 
  * @param  Delay: Delay in ms
  * @retval None
  */
void AUDIO_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

#if defined(USE_IOEXPANDER)
/********************************* LINK CAMERA ********************************/

/**
  * @brief  Initializes Camera low level.
  * @retval None
  */
void CAMERA_IO_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  Camera writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
  */
void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @retval Read data
  */
uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Camera delay 
  * @param  Delay: Delay in ms
  * @retval None
  */
void CAMERA_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}
#endif /* USE_IOEXPANDER */
/******************************** LINK I2C EEPROM *****************************/

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @retval None
  */
void EEPROM_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Write data to I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Read data from I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_ReadMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Checks if target device is ready for communication. 
  * @note   This function is used with Memory devices
  * @param  DevAddress: Target device address
  * @param  Trials: Number of trials
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (I2Cx_IsDeviceReady(DevAddress, Trials));
}

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */    
    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
