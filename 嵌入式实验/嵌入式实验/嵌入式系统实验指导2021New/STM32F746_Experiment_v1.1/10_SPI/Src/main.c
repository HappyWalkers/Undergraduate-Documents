#include "main.h"
#include "system_init.h"

__IO uint8_t CmdCplt, RxCplt, TxCplt, StatusMatch, TimeOut;
extern QSPI_HandleTypeDef QSPIHandle;
extern QSPI_CommandTypeDef sCommand;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT**** ";

/* Buffer used for reception */
uint8_t aRxBuf[BUFFERSIZE];

void System_Init(void);
void SPI_Config(void);
void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi);
void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi);

/* main */
int main(void)
{
  uint32_t address = 0;
  uint16_t index;
  __IO uint8_t step = 0;
  
  System_Init();
  
  /* Initialize LED1 mounted on board */
  BSP_LED_Init(LED1);
  
  /* Initialize QuadSPI */
  SPI_Config();
  
  while (1)
  {
    switch(step)
    {
      case 0:
        CmdCplt = 0;
        
        /* Initialize Reception buffer --------------------------------------- */
        for (index = 0; index < BUFFERSIZE; index++)
        {
          aRxBuf[index] = 0;
        }

        /* Enable write operations ------------------------------------------- */
        QSPI_WriteEnable(&QSPIHandle);

        /* Erasing Sequence -------------------------------------------------- */
        sCommand.Instruction = SECTOR_ERASE_CMD;
        sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
        sCommand.Address     = address;
        sCommand.DataMode    = QSPI_DATA_NONE;
        sCommand.DummyCycles = 0;

        HAL_QSPI_Command_IT(&QSPIHandle, &sCommand);

        step++;
        break;

      case 1:
        if(CmdCplt != 0)
        {
          CmdCplt = 0;
          StatusMatch = 0;

          /* Configure automatic polling mode to wait for end of erase ------- */  
          QSPI_AutoPollingMemReady(&QSPIHandle);

          step++;
        }
        break;
        
      case 2:
        if(StatusMatch != 0)
        {
          StatusMatch = 0;
          TxCplt = 0;
          
          /* Enable write operations ----------------------------------------- */
          QSPI_WriteEnable(&QSPIHandle);

          /* Writing Sequence ------------------------------------------------ */
          sCommand.Instruction = QUAD_IN_FAST_PROG_CMD;
          sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
          sCommand.DataMode    = QSPI_DATA_4_LINES;
          sCommand.NbData      = BUFFERSIZE;

          HAL_QSPI_Command(&QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

          HAL_QSPI_Transmit_IT(&QSPIHandle, aTxBuffer);

          step++;
        }
        break;

      case 3:
        if(TxCplt != 0)
        {
          TxCplt = 0;
          StatusMatch = 0;

          /* Configure automatic polling mode to wait for end of program ----- */  
          QSPI_AutoPollingMemReady(&QSPIHandle);
        
          step++;
        }
        break;
        
      case 4:
        if(StatusMatch != 0)
        {
          StatusMatch = 0;
          RxCplt = 0;

          /* Configure Volatile Configuration register (with new dummy cycles) */
          QSPI_DummyCyclesCfg(&QSPIHandle);
          
          /* Reading Sequence ------------------------------------------------ */
          sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
          sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

          HAL_QSPI_Command(&QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

          HAL_QSPI_Receive_IT(&QSPIHandle, aRxBuf);
          step++;
        }
        break;
        
      case 5:
        if (RxCplt != 0)
        {
          RxCplt = 0;
          BSP_LED_Toggle(LED1);
          while (1)
          {
          }
        }
        break;
        
      default :
        break;
    }
  }
}

/* Command completed callbacks */
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  CmdCplt++;
}

/* Rx Transfer completed callbacks */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  RxCplt++;
}

/* Tx Transfer completed callbacks */
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  TxCplt++; 
}

/* Status Match callbacks */
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
  StatusMatch++;
}
