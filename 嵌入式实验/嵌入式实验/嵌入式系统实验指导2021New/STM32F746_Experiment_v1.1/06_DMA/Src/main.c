/**
  主程序：aSRC_Const_Buffer为Flash空间中的数据，系统上电后对DMA进行配置，
	使用DMA将aSRC_Const_Buffer中的内容以FIFO的方式传输至RAM，传输完成后点亮LED。
**/
#include "main.h"
#include "system_init.h"

extern DMA_HandleTypeDef  DmaHandle;

const uint32_t aSRC_Const_Buffer[BUFFER_SIZE] =
{
  0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
  0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
  0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
  0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
  0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
  0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
  0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
  0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};

static uint32_t aDST_Buffer[BUFFER_SIZE];

void System_Init(void);
void DMA_Config(void);

/* main */
int main(void)
{
  System_Init();
  
  /* Initialize LED1 mounted on board */
  BSP_LED_Init(LED1);
  
  /* Configure and enable the DMA stream for Memory to Memory transfer */
  DMA_Config();
  
  /* Start the DMA transfer using the interrupt mode */
  HAL_DMA_Start_IT(&DmaHandle, (uint32_t)&aSRC_Const_Buffer, (uint32_t)&aDST_Buffer, BUFFER_SIZE);
  
  printf("\n\rDMA transmition success\n\r\n\rExample finished\n\r");
  
  while (1)
  {
  }
}
