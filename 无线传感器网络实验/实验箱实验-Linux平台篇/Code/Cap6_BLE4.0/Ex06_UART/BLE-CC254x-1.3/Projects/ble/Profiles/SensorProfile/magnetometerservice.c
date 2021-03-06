/**************************************************************************************************
  Filename:       magnetometerservice.c
  Revised:        $Date: 2012-08-16 11:43:20 -0700 (Thu, 16 Aug 2012) $
  Revision:       $Revision: 31269 $

  Description:    Magnetometer Service


  Copyright 2012 Texas Instruments Incorporated. All rights reserved.

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
  PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
#include "linkdb.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"

#include "magnetometerservice.h"
#include "st_util.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// Magnetometer Service UUID
CONST uint8 magnetometerServUUID[TI_UUID_SIZE] =
{
  TI_UUID(MAGNETOMETER_SERV_UUID),
};

// Magnetometer Characteristic value Data UUID
CONST uint8 magnetometerDataUUID[TI_UUID_SIZE] =
{
  TI_UUID(MAGNETOMETER_DATA_UUID),
};

// Magnetometer Characteristic value Configuration UUID
CONST uint8 magnetometerCfgUUID[TI_UUID_SIZE] =
{
  TI_UUID(MAGNETOMETER_CONF_UUID),
};

// Magnetometer Characteristic value Period UUID
CONST uint8 magnetometerPerUUID[TI_UUID_SIZE] =
{
  TI_UUID(MAGNETOMETER_PERI_UUID),
};

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static magnetometerCBs_t *magnetometer_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */

// Magnetometer  Profile Service attribute
static CONST gattAttrType_t magnetometerService = { TI_UUID_SIZE, magnetometerServUUID };

// Magnetometer Characteristic Properties
static uint8 magnetometerDataProps = GATT_PROP_READ | GATT_PROP_NOTIFY;

static uint8 magnetometerData[MAGNETOMETER_DATA_LEN] = { 0, 0, 0, 0, 0, 0};

// Magnetometer Characteristic Configuration
static gattCharCfg_t magnetometerDataConfig[GATT_MAX_NUM_CONN];

// Magnetometer Characteristic User Description
static uint8 magnetometerDataUserDesp[10] = "Mag. Data\0";

// Magnetometer Characteristic Configuration Properties
static uint8 magnetometerCfgProps = GATT_PROP_READ | GATT_PROP_WRITE;

// Magnetometer Characteristic Configuration Value
static uint8 magnetometerCfg = 0;

// Magnetometer Characteristic Configuration User Description
static uint8 magnetometerCfgUserDesp[11] = "Mag. Conf.\0";

// Magnetometer Characteristic Period Properties
static uint8 magnetometerPerProps = GATT_PROP_READ | GATT_PROP_WRITE;

// Magnetometer Characteristic Period Value
static uint8 magnetometerPer = 0;

// Magnetometer Characteristic Period User Description
static uint8 magnetometerPerUserDesp[12] = "Mag. Period\0";


/*********************************************************************
 * Profile Attributes - Table
 */


static gattAttribute_t sensorMagnetometerAttrTbl[] =
{
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&magnetometerService             /* pValue */
  },

    // Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &magnetometerDataProps
    },

      // Characteristic Value "Data"
      {
        { TI_UUID_SIZE, magnetometerDataUUID },
        GATT_PERMIT_READ,
        0,
        magnetometerData
      },

      // Characteristic configuration
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)magnetometerDataConfig
      },

      // Characteristic User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        magnetometerDataUserDesp
      },

    // Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &magnetometerCfgProps
    },

      // Characteristic Value "Configuration"
      {
        { TI_UUID_SIZE, magnetometerCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &magnetometerCfg
      },

      // Characteristic User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        magnetometerCfgUserDesp
      },

          // Characteristic Declaration "Period"
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &magnetometerPerProps
    },

      // Characteristic Value "Period"
      {
        { TI_UUID_SIZE, magnetometerPerUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &magnetometerPer
      },

      // Characteristic User Description "Period"
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        magnetometerPerUserDesp
      },
};


/*********************************************************************
 * LOCAL FUNCTIONS
 */
static uint8 magnetometer_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen );
static bStatus_t magnetometer_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset );
static void magnetometer_HandleConnStatusCB( uint16 connHandle, uint8 changeType );

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Magnetometer Profile Service Callbacks
CONST gattServiceCBs_t magnetometerCBs =
{
  magnetometer_ReadAttrCB,  // Read callback function pointer
  magnetometer_WriteAttrCB, // Write callback function pointer
  NULL                      // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      Magnetometer_AddService
 *
 * @brief   Initializes the Sensor Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t Magnetometer_AddService( uint32 services )
{
  uint8 status = SUCCESS;

  GATTServApp_InitCharCfg( INVALID_CONNHANDLE, magnetometerDataConfig );

  // Register with Link DB to receive link status change callback
  VOID linkDB_Register( magnetometer_HandleConnStatusCB );

  if ( services & MAGNETOMETER_SERVICE )
  {
    // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( sensorMagnetometerAttrTbl,
                                          GATT_NUM_ATTRS( sensorMagnetometerAttrTbl ),
                                          &magnetometerCBs );
  }

  return ( status );
}


/*********************************************************************
 * @fn      Magnetometer_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t Magnetometer_RegisterAppCBs( magnetometerCBs_t *appCallbacks )
{
  if ( magnetometer_AppCBs == NULL )
  {
    if ( appCallbacks != NULL )
    {
      magnetometer_AppCBs = appCallbacks;
    }

    return ( SUCCESS );
  }

  return ( bleAlreadyInRequestedMode );
}


/*********************************************************************
 * @fn      Magnetometer_SetParameter
 *
 * @brief   Set a Sensor Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to right
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t Magnetometer_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;

  switch ( param )
  {
    case MAGNETOMETER_DATA:
      if ( len == MAGNETOMETER_DATA_LEN )
      {
        VOID osal_memcpy( magnetometerData, value, MAGNETOMETER_DATA_LEN );
        // See if Notification has been enabled
        GATTServApp_ProcessCharCfg( magnetometerDataConfig, magnetometerData, FALSE,
                                   sensorMagnetometerAttrTbl, GATT_NUM_ATTRS( sensorMagnetometerAttrTbl ),
                                   INVALID_TASK_ID );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MAGNETOMETER_CONF:
      if ( len == sizeof ( uint8 ) )
      {
        magnetometerCfg = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MAGNETOMETER_PERI:
      if ( len == sizeof ( uint8 ) )
      {
        magnetometerPer = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
        break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn      Magnetometer_GetParameter
 *
 * @brief   Get a Sensor Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t Magnetometer_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;

  switch ( param )
  {
    case MAGNETOMETER_DATA:
      VOID osal_memcpy( value, magnetometerData, MAGNETOMETER_DATA_LEN );
      break;

    case MAGNETOMETER_CONF:
      *((uint8*)value) = magnetometerCfg;
      break;

    case MAGNETOMETER_PERI:
      *((uint8*)value) = magnetometerPer;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn          magnetometer_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 *
 * @return      Success or Failure
 */
static uint8 magnetometer_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen )
{
  uint16 uuid;
  bStatus_t status = SUCCESS;

  // If attribute permissions require authorization to read, return error
  if ( gattPermitAuthorRead( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }

  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if (utilExtractUuid16(pAttr,&uuid) == FAILURE)
  {
    // Invalid handle
    *pLen = 0;
    return ATT_ERR_INVALID_HANDLE;
  }

  switch ( uuid )
  {
    // No need for "GATT_SERVICE_UUID" or "GATT_CLIENT_CHAR_CFG_UUID" cases;
    // gattserverapp handles those reads
    case MAGNETOMETER_DATA_UUID:
      *pLen = MAGNETOMETER_DATA_LEN;
      VOID osal_memcpy( pValue, pAttr->pValue, MAGNETOMETER_DATA_LEN );
      break;

    case MAGNETOMETER_CONF_UUID:
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
      break;

    case MAGNETOMETER_PERI_UUID:
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
      break;

    default:
      *pLen = 0;
      status = ATT_ERR_ATTR_NOT_FOUND;
      break;
  }

  return ( status );
}

/*********************************************************************
* @fn      magnetometer_WriteAttrCB
*
* @brief   Validate attribute data prior to a write operation
*
* @param   connHandle - connection message was received on
* @param   pAttr - pointer to attribute
* @param   pValue - pointer to data to be written
* @param   len - length of data
* @param   offset - offset of the first octet to be written
* @param   complete - whether this is the last packet
* @param   oper - whether to validate and/or write attribute value
*
* @return  Success or Failure
*/
static bStatus_t magnetometer_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                           uint8 *pValue, uint8 len, uint16 offset )
{
  uint16 uuid;
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;

  // If attribute permissions require authorization to write, return error
  if ( gattPermitAuthorWrite( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }

  if (utilExtractUuid16(pAttr,&uuid) == FAILURE)
  {
    // Invalid handle
    return ATT_ERR_INVALID_HANDLE;
  }

  switch ( uuid )
  {
    case MAGNETOMETER_DATA_UUID:
      //Should not get here
      break;

    case MAGNETOMETER_CONF_UUID:
      // Validate the value
      // Make sure it's not a blob oper
      if ( offset == 0 )
      {
        if ( len != 1 )
        {
          status = ATT_ERR_INVALID_VALUE_SIZE;
        }
      }
      else
      {
        status = ATT_ERR_ATTR_NOT_LONG;
      }

      // Write the value
      if ( status == SUCCESS )
      {
        uint8 *pCurValue = (uint8 *)pAttr->pValue;
        *pCurValue = pValue[0];

        if( pAttr->pValue == &magnetometerCfg )
        {
          notifyApp = MAGNETOMETER_CONF;
        }
      }
      break;

    case MAGNETOMETER_PERI_UUID:
      // Validate the value
      // Make sure it's not a blob oper
      if ( offset == 0 )
      {
        if ( len != 1 )
        {
          status = ATT_ERR_INVALID_VALUE_SIZE;
        }
      }
      else
      {
        status = ATT_ERR_ATTR_NOT_LONG;
      }

      // Write the value
      if ( status == SUCCESS )
      {
        uint8 *pCurValue = (uint8 *)pAttr->pValue;

        *pCurValue = pValue[0];
        if( pAttr->pValue == &magnetometerPer )
        {
          notifyApp = MAGNETOMETER_PERI;
        }
      }
      break;

    case GATT_CLIENT_CHAR_CFG_UUID:
      status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                              offset, GATT_CLIENT_CFG_NOTIFY );
      break;

    default:
      // Should never get here!
      status = ATT_ERR_ATTR_NOT_FOUND;
      break;
  }

  // If a charactersitic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && magnetometer_AppCBs && magnetometer_AppCBs->pfnMagnetometerChange )
  {
    magnetometer_AppCBs->pfnMagnetometerChange( notifyApp );
  }

  return ( status );
}

/*********************************************************************
 * @fn          magnetometer_HandleConnStatusCB
 *
 * @brief       Sensor Profile link status change handler function.
 *
 * @param       connHandle - connection handle
 * @param       changeType - type of change
 *
 * @return      none
 */
static void magnetometer_HandleConnStatusCB( uint16 connHandle, uint8 changeType )
{
  // Make sure this is not loopback connection
  if ( connHandle != LOOPBACK_CONNHANDLE )
  {
    // Reset Client Char Config if connection has dropped
    if ( ( changeType == LINKDB_STATUS_UPDATE_REMOVED )      ||
         ( ( changeType == LINKDB_STATUS_UPDATE_STATEFLAGS ) &&
           ( !linkDB_Up( connHandle ) ) ) )
    {
      GATTServApp_InitCharCfg( connHandle, magnetometerDataConfig );
    }
  }
}


/*********************************************************************
*********************************************************************/
