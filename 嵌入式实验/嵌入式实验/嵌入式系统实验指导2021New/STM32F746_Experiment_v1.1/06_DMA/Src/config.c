#include "main.h"

/* DMA Handle declaration */
DMA_HandleTypeDef     DmaHandle;

static void TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
  /* Turn LED1 on: Transfer correct */
  BSP_LED_On(LED1);
}

/* Configure the DMA controller */
void DMA_Config(void)
{
  /* Enable DMA2 clock */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Select the DMA functional Parameters */
  DmaHandle.Init.Channel = DMA_CHANNEL;                     /* DMA_CHANNEL_0                    */
  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M transfer mode                */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* Peripheral increment mode Enable */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* Peripheral data alignment : Word */
  DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;    /* memory data alignment : Word     */
  DmaHandle.Init.Mode = DMA_NORMAL;                         /* Normal DMA mode                  */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
  DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;            /* FIFO mode enabled                */        
  DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;  
  DmaHandle.Init.MemBurst = DMA_MBURST_INC4;                /* Memory burst                     */  
  DmaHandle.Init.PeriphBurst = DMA_PBURST_INC4;             /* Peripheral burst                 */

  /* Select the DMA instance to be used for the transfer : DMA2_Stream0 */
  DmaHandle.Instance = DMA_INSTANCE;

  /* Select Callbacks functions called after Transfer complete */
  DmaHandle.XferCpltCallback = TransferComplete;

  /* Initialize the DMA stream */
  HAL_DMA_Init(&DmaHandle);

  /* Configure NVIC for DMA transfer complete interrupts */
  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriority(DMA_INSTANCE_IRQ, 0, 0);

  /* Enable the DMA STREAM global Interrupt */
  HAL_NVIC_EnableIRQ(DMA_INSTANCE_IRQ);
}
