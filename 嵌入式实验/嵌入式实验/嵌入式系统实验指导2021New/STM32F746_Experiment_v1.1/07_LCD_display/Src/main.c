/**
  ������ϵͳ�ϵ��ʼ��������Һ�����ֲ���ʾ������ͬһʱ����������ʾ���ϸ�����ʾͼ��
	ͼƬ��������ʽ�ֱ����RGB565_320��240.h��L8_320��240.h�У��������к�Һ�����ϵ�����ͼ��
	������ԽǷ����ƶ���
**/
#include "main.h"
#include "system_init.h"
#include "L8_320x240.h"
#include "RGB565_320x240.h"

extern LTDC_HandleTypeDef LtdcHandle;

void System_Init(void);
void LCD_Config(uint32_t Layer1_FrameBuffer_Addr,uint32_t Layer2_FrameBuffer_Addr);

/* main */
int main(void)
{
  /* Variables for moving */
  uint32_t toBottom = 0;
  uint32_t toTop = 0;
  
  System_Init();
  
  /* LCD Configuration */ 
  /* Configure 2 layers */ 
  /* Blending and CLUT loading for layer 1 */
  LCD_Config((uint32_t)&L8_320x240, (uint32_t)&RGB565_320x240); 

  /* CLUT Configuration */
  HAL_LTDC_ConfigCLUT(&LtdcHandle, (uint32_t *)L8_320x240_CLUT, 256, 0); 
  
  /* Enable CLUT For Layer 1 */
  HAL_LTDC_EnableCLUT(&LtdcHandle, 0);  
  
  while (1)
  {
    for (toBottom = 0; toBottom < 32; toBottom++)
    {
      /* move the picture */
      /* reconfigure the layer1 position */
      HAL_LTDC_SetWindowPosition(&LtdcHandle, (toBottom*5), (toBottom), 0);
      /* reconfigure the layer2 position */
      HAL_LTDC_SetWindowPosition(&LtdcHandle, (160 - (toBottom*5)), (32 - toBottom), 1);
      HAL_Delay(50);
    }
    HAL_Delay(500);
    for (toTop = 0; toTop < 32; toTop++)
    {
      /* move the picture */
      /* reconfigure the layer1 position */
      HAL_LTDC_SetWindowPosition(&LtdcHandle, (160 - (toTop*5)), (32 - (toTop)), 0);
      /* reconfigure the layer2 position */
      HAL_LTDC_SetWindowPosition(&LtdcHandle, (toTop*5), toTop, 1);
      HAL_Delay(50);
    }
    HAL_Delay(500);
  }
}
