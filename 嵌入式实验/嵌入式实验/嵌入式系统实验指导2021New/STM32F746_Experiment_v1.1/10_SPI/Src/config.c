#include "main.h"

QSPI_HandleTypeDef QSPIHandle;
QSPI_CommandTypeDef sCommand;

/* Initialize QuadSPI */
void SPI_Config()
{
  QSPIHandle.Instance = QUADSPI;
  HAL_QSPI_DeInit(&QSPIHandle);
        
  /* ClockPrescaler set to 2, so QSPI clock = 216MHz / (2+1) = 72MHz */
  QSPIHandle.Init.ClockPrescaler     = 2;
  QSPIHandle.Init.FifoThreshold      = 4;
  QSPIHandle.Init.SampleShifting     = QSPI_SAMPLE_SHIFTING_NONE;
  QSPIHandle.Init.FlashSize          = QSPI_FLASH_SIZE;
  QSPIHandle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  QSPIHandle.Init.ClockMode          = QSPI_CLOCK_MODE_0;

  HAL_QSPI_Init(&QSPIHandle);

  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode         = QSPI_SIOO_INST_EVERY_CMD;
}

/* This function send a Write Enable and wait it is effective */
void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Enable write operations */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = WRITE_ENABLE_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_NONE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode         = QSPI_SIOO_INST_EVERY_CMD;

  HAL_QSPI_Command(&QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
  
  /* Configure automatic polling mode to wait for write enabling */  
  sConfig.Match           = 0x02;
  sConfig.Mask            = 0x02;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  sCommand.Instruction    = READ_STATUS_REG_CMD;
  sCommand.DataMode       = QSPI_DATA_1_LINE;

  HAL_QSPI_AutoPolling(&QSPIHandle, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

/* This function read the SR of the memory and wait the EOP */
void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready */  
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = READ_STATUS_REG_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_1_LINE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode         = QSPI_SIOO_INST_EVERY_CMD;

  sConfig.Match           = 0x00;
  sConfig.Mask            = 0x01;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  HAL_QSPI_AutoPolling_IT(&QSPIHandle, &sCommand, &sConfig);
}

/* This function configure the dummy cycles on memory side */
void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef sCommand;
  uint8_t reg;

  /* Read Volatile Configuration register */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = READ_VOL_CFG_REG_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_1_LINE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode         = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.NbData            = 1;

  HAL_QSPI_Command(&QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

  HAL_QSPI_Receive(&QSPIHandle, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

  /* Enable write operations */
  QSPI_WriteEnable(&QSPIHandle);

  /* Write Volatile Configuration register (with new dummy cycles) */  
  sCommand.Instruction = WRITE_VOL_CFG_REG_CMD;
  MODIFY_REG(reg, 0xF0, (DUMMY_CLOCK_CYCLES_READ_QUAD << POSITION_VAL(0xF0)));
      
  HAL_QSPI_Command(&QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);

  HAL_QSPI_Transmit(&QSPIHandle, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}
