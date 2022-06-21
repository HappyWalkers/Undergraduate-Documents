/**************************************************************************************************
  Filename:       OnBoard.c
  Revised:        $Date: 2008-03-18 15:14:17 -0700 (Tue, 18 Mar 2008) $
  Revision:       $Revision: 16604 $

  Description:    This file contains the UI and control for the
                  peripherals on the EVAL development board
  Notes:          This file targets the Chipcon CC2430DB/CC2430EB


  Copyright 2005-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED 揂S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "bcomdef.h"
#include "OnBoard.h"
#include "OSAL.h"
#include "OnBoard.h"

#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"//add 20131218 UART0Init


/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// Task ID not initialized
#define NO_TASK_ID 0xFF


/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
uint8 OnboardKeyIntEnable;


/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */
extern uint8 LL_PseudoRand( uint8 *randData, uint8 dataLen );

#if   defined FEATURE_ABL
#include "..\..\util\ABL\app\sbl_app.c"
#elif defined FEATURE_SBL
#include "..\..\util\SBL\app\sbl_app.c"
#elif defined FEATURE_EBL
#include "..\..\util\EBL\app\sbl_app.c"
#elif defined FEATURE_UBL_MSD
#include "..\..\util\UBL\soc_8051\usb_msd\app\ubl_app.c"
#else
void appForceBoot(void);
#endif

/*********************************************************************
 * LOCAL VARIABLES
 */

// Registered keys task ID, initialized to NOT USED.
static uint8 registeredKeysTaskID = NO_TASK_ID;
//Registered Serial task ID,initialized to NOT USED.
static uint8 registeredSerialTaskID = NO_TASK_ID;
/*********************************************************************
 * @fn      InitBoard()
 * @brief   Initialize the CC2540DB Board Peripherals
 * @param   level: COLD,WARM,READY
 * @return  None
 */
void InitBoard( uint8 level )
{
  if ( level == OB_COLD )
  {
    // Interrupts off
    osal_int_disable( INTS_ALL );
    // Turn all LEDs off
    HalLedSet( HAL_LED_ALL, HAL_LED_MODE_OFF );
    // Check for Brown-Out reset
//    ChkReset();
  }
  else  // !OB_COLD
  {
    /* Initialize Key stuff */
    OnboardKeyIntEnable = HAL_KEY_INTERRUPT_ENABLE;
    //OnboardKeyIntEnable = HAL_KEY_INTERRUPT_DISABLE;
    HalKeyConfig( OnboardKeyIntEnable, OnBoard_KeyCallback);
  }
}

/*********************************************************************
 * @fn        Onboard_rand
 *
 * @brief    Random number generator
 *
 * @param   none
 *
 * @return  uint16 - new random number
 *
 *********************************************************************/
uint16 Onboard_rand( void )
{
  uint16 randNum;

  LL_PseudoRand( (uint8 *)&randNum, 2 );

  return ( randNum );
}

/*********************************************************************
 * @fn      _itoa
 *
 * @brief   convert a 16bit number to ASCII
 *
 * @param   num -
 *          buf -
 *          radix -
 *
 * @return  void
 *
 *********************************************************************/
void _itoa(uint16 num, uint8 *buf, uint8 radix)
{
  char c,i;
  uint8 *p, rst[5];

  p = rst;
  for ( i=0; i<5; i++,p++ )
  {
    c = num % radix;  // Isolate a digit
    *p = c + (( c < 10 ) ? '0' : '7');  // Convert to Ascii
    num /= radix;
    if ( !num )
      break;
  }

  for ( c=0 ; c<=i; c++ )
    *buf++ = *p--;  // Reverse character order

  *buf = '\0';
}

/*********************************************************************
 *                        "Keyboard" Support
 *********************************************************************/

/*********************************************************************
 * Keyboard Register function
 *
 * The keyboard handler is setup to send all keyboard changes to
 * one task (if a task is registered).
 *
 * If a task registers, it will get all the keys. You can change this
 * to register for individual keys.
 *********************************************************************/
uint8 RegisterForKeys( uint8 task_id )
{
  // Allow only the first task
  if ( registeredKeysTaskID == NO_TASK_ID )
  {
    registeredKeysTaskID = task_id;
    return ( true );
  }
  else
    return ( false );
}
/*********************************************************************
 * @fn      OnBoard_SendKeys
 *
 * @brief   Send "Key Pressed" message to application.
 *
 * @param   keys  - keys that were pressed
 *          state - shifted
 *
 * @return  status
 *********************************************************************/
uint8 OnBoard_SendKeys( uint8 keys, uint8 state )
{
  keyChange_t *msgPtr;

  if ( registeredKeysTaskID != NO_TASK_ID )
  {
    // Send the address to the task
    msgPtr = (keyChange_t *)osal_msg_allocate( sizeof(keyChange_t) );
    if ( msgPtr )
    {
      msgPtr->hdr.event = KEY_CHANGE;
      msgPtr->state = state;
      msgPtr->keys = keys;

      osal_msg_send( registeredKeysTaskID, (uint8 *)msgPtr );
    }
    return ( SUCCESS );
  }
  else
    return ( FAILURE );
}

/*********************************************************************
 * @fn      OnBoard_KeyCallback
 *
 * @brief   Callback service for keys
 *
 * @param   keys  - keys that were pressed
 *          state - shifted
 *
 * @return  void
 *********************************************************************/
void OnBoard_KeyCallback ( uint8 keys, uint8 state )
{
  uint8 shift;
  (void)state;

  // shift key (S1) is used to generate key interrupt
  // applications should not use S1 when key interrupt is enabled
  shift = (OnboardKeyIntEnable == HAL_KEY_INTERRUPT_ENABLE) ? false : ((keys & HAL_KEY_SW_6) ? true : false);

  if ( OnBoard_SendKeys( keys, shift ) != SUCCESS )
  {
    // Process SW1 here
    if ( keys & HAL_KEY_SW_1 )  // Switch 1
    {
    }
    // Process SW2 here
    if ( keys & HAL_KEY_SW_2 )  // Switch 2
    {
    }
    // Process SW3 here
    if ( keys & HAL_KEY_SW_3 )  // Switch 3
    {
    }
    // Process SW4 here
    if ( keys & HAL_KEY_SW_4 )  // Switch 4
    {
    }
    // Process SW5 here
    if ( keys & HAL_KEY_SW_5 )  // Switch 5
    {
    }
    // Process SW6 here
    if ( keys & HAL_KEY_SW_6 )  // Switch 6
    {
    }
  }

  /* If any key is currently pressed down and interrupt
     is still enabled, disable interrupt and switch to polling */
  if( keys != 0 )
  {
    if( OnboardKeyIntEnable == HAL_KEY_INTERRUPT_ENABLE )
    {
      OnboardKeyIntEnable = HAL_KEY_INTERRUPT_DISABLE;
      HalKeyConfig( OnboardKeyIntEnable, OnBoard_KeyCallback);
    }
  }
  /* If no key is currently pressed down and interrupt
     is disabled, enable interrupt and turn off polling */
  else
  {
    if( OnboardKeyIntEnable == HAL_KEY_INTERRUPT_DISABLE )
    {
      OnboardKeyIntEnable = HAL_KEY_INTERRUPT_ENABLE;
      HalKeyConfig( OnboardKeyIntEnable, OnBoard_KeyCallback);
    }
  }
}

/*********************************************************************
 * @fn      Onboard_soft_reset
 *
 * @brief   Effect a soft reset.
 *
 * @param   none
 *
 * @return  none
 *
 *********************************************************************/
__near_func void Onboard_soft_reset( void )
{
  HAL_DISABLE_INTERRUPTS();
  asm("LJMP 0x0");
}

#if   defined FEATURE_ABL
#elif defined FEATURE_SBL
#elif defined FEATURE_EBL
#elif defined FEATURE_UBL_MSD
#else
/*********************************************************************
 * @fn      appForceBoot
 *
 * @brief   Common force-boot function for the HCI library to invoke.
 *
 * @param   none
 *
 * @return  void
 *********************************************************************/
void appForceBoot(void)
{
  // Dummy function for HCI library that cannot depend on the SBL build defines.
}
#endif
uint8 RegisterForSerial(uint8 task_id)
{
  //Allow only the first task
  if(registeredSerialTaskID == NO_TASK_ID)
  {
    registeredSerialTaskID = task_id;
    return (true);
  }
  else
    return (false);
}
static uint32 lastTick;

#define SOP_STATE   0x00
#define DATA_STATE  0x01
#define STOP_STATE  0x02
static void SerialCallback(uint8 port,uint8 event)
{
  mtOSALSerialData_t *pMsgSerial;
  uint8 flag = 0,i,dataRecvIdx=0;
  uint8 buf[128];
  (void)event;
  if((lastTick + 200) <= osal_GetSystemClock())
  {                                     // 如果本次接收到的时间距离上次超过了0.1秒
    dataRecvIdx = 0;                    // 则清空计数器，重新接收卡号
  }
  lastTick = osal_GetSystemClock();       // 记录下当前的时间
  while(Hal_UART_RxBufLen(port))
  {
    uint8 restLen = Hal_UART_RxBufLen(port);
    HalUARTRead(port,&buf[dataRecvIdx],restLen);
    dataRecvIdx += restLen;  
    flag = 1;
  }
  if(flag == 1)
  { 
    pMsgSerial = (mtOSALSerialData_t *)osal_msg_allocate(sizeof(mtOSALSerialData_t)+dataRecvIdx+1);
    pMsgSerial->hdr.event = SERIAL_MSG;
    pMsgSerial->msg = (uint8 *)(pMsgSerial+1);
    osal_memset(pMsgSerial->msg,0,dataRecvIdx);
    pMsgSerial->msg[0] = dataRecvIdx;
    for(i=0;i<dataRecvIdx;i++)
    {
      pMsgSerial->msg[i+1] = buf[i];
    }
    osal_msg_send(registeredSerialTaskID,(uint8 *)pMsgSerial);
    osal_msg_deallocate((uint8 *)pMsgSerial);
  }
}
/*********************************************************************
 * @fn      uart0_init
 *
 * @brief   
 *
 * @param   uart  - 
 *
 * @return  void
 *********************************************************************/
void UartInit(void)
{
    halUARTCfg_t uartConfig;
    
    uartConfig.configured     = TRUE;
    uartConfig.baudRate       = HAL_UART_BR_115200;
    uartConfig.flowControl    = HAL_UART_FLOW_OFF;
    uartConfig.flowControlThreshold = MT_UART_THRESHOLD;
    uartConfig.rx.maxBufSize        = MT_UART_RX_BUFF_MAX;
    uartConfig.tx.maxBufSize        = MT_UART_TX_BUFF_MAX;
    uartConfig.idleTimeout          = MT_UART_IDLE_TIMEOUT;
    
    uartConfig.intEnable            = TRUE;
    uartConfig.callBackFunc         = SerialCallback;//NULL;
    
    HalUARTOpen(HAL_UART_PORT_0,&uartConfig);
}

/*********************************************************************
*********************************************************************/
