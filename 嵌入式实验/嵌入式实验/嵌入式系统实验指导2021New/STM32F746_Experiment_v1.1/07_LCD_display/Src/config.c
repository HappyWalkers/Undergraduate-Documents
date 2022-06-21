#include "main.h"

LTDC_HandleTypeDef LtdcHandle;
RCC_PeriphCLKInitTypeDef  periph_clk_init_struct;

void LCD_Config(uint32_t Layer1_FrameBuffer_Addr, uint32_t Layer2_FrameBuffer_Addr)
{  
  LTDC_LayerCfgTypeDef      pLayerCfg;
  LTDC_LayerCfgTypeDef      pLayerCfg1;
  
  /* The AMPIRE LCD 480x272 */
  /* LCD clock configuration */
  /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
  /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz */
  /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz */
  /* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz */
  periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  periph_clk_init_struct.PLLSAI.PLLSAIN = 192;
  periph_clk_init_struct.PLLSAI.PLLSAIR = AMPIRE480272_FREQUENCY_DIVIDER;
  periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct); 
  
  /* LTDC Initialization -------------------------------------------------------*/
  /* Polarity configuration */
  /* Initialize the horizontal synchronization polarity as active low */
  LtdcHandle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  /* Initialize the vertical synchronization polarity as active low */ 
  LtdcHandle.Init.VSPolarity = LTDC_VSPOLARITY_AL; 
  /* Initialize the data enable polarity as active low */ 
  LtdcHandle.Init.DEPolarity = LTDC_DEPOLARITY_AL; 
  /* Initialize the pixel clock polarity as input pixel clock */  
  LtdcHandle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  
  /* Timing configuration */   
	/* Configure horizontal synchronization width */
	LtdcHandle.Init.HorizontalSync = (AMPIRE480272_HSYNC - 1);
	/* Configure vertical synchronization height */
	LtdcHandle.Init.VerticalSync = (AMPIRE480272_VSYNC - 1);
	/* Configure accumulated horizontal back porch */
	LtdcHandle.Init.AccumulatedHBP = (AMPIRE480272_HSYNC + AMPIRE480272_HBP - 1);
	/* Configure accumulated vertical back porch */
	LtdcHandle.Init.AccumulatedVBP = (AMPIRE480272_VSYNC + AMPIRE480272_VBP - 1); 
	/* Configure accumulated active height */	
	LtdcHandle.Init.AccumulatedActiveH = (AMPIRE480272_HEIGHT + AMPIRE480272_VSYNC + AMPIRE640480_VBP - 1);
	/* Configure accumulated active width */ 
	LtdcHandle.Init.AccumulatedActiveW = (AMPIRE480272_WIDTH + AMPIRE480272_HSYNC + AMPIRE640480_HBP - 1);
	/* Configure total height */
	LtdcHandle.Init.TotalHeigh = (AMPIRE480272_HEIGHT + AMPIRE480272_VSYNC + AMPIRE480272_VBP + AMPIRE480272_VFP - 1);
	/* Configure total width */
	LtdcHandle.Init.TotalWidth = (AMPIRE480272_WIDTH + AMPIRE480272_HSYNC + AMPIRE480272_HBP + AMPIRE480272_HFP - 1);
	 
	/* Initialize the LCD pixel width and pixel height */
	LtdcHandle.LayerCfg->ImageWidth  = AMPIRE480272_WIDTH;
	LtdcHandle.LayerCfg->ImageHeight = AMPIRE480272_HEIGHT;  
  
  /* Configure R,G,B component values for LCD background color */
  LtdcHandle.Init.Backcolor.Blue = 0;
  LtdcHandle.Init.Backcolor.Green = 0;
  LtdcHandle.Init.Backcolor.Red = 0;

  LtdcHandle.Instance = LTDC;
  
/* Layer1 Configuration ------------------------------------------------------*/
  
  /* Windowing configuration */ 
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 320;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 240;
  
  /* Pixel Format configuration*/ 
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_L8;
  
  /* Start Address configuration : frame buffer is located at FLASH memory */
  pLayerCfg.FBStartAdress = Layer1_FrameBuffer_Addr;
  
  /* Alpha constant (255 totally opaque) */
  pLayerCfg.Alpha = 255;
  
  /* Default Color configuration (configure A,R,G,B component values) */
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  
  /* Configure blending factors */
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  
  /* Configure the number of lines and number of pixels per line */
  pLayerCfg.ImageWidth = 320;
  pLayerCfg.ImageHeight = 240;

/* Layer2 Configuration ------------------------------------------------------*/
  
  /* Windowing configuration */ 
  pLayerCfg1.WindowX0 = 160;
  pLayerCfg1.WindowX1 = 480;
  pLayerCfg1.WindowY0 = 32;
  pLayerCfg1.WindowY1 = 272;
  
  /* Pixel Format configuration*/ 
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  
  /* Start Address configuration : frame buffer is located at FLASH memory */
  pLayerCfg1.FBStartAdress = Layer2_FrameBuffer_Addr;
  
  /* Alpha constant (255 totally opaque) */
  pLayerCfg1.Alpha = 200;
  
  /* Default Color configuration (configure A,R,G,B component values) */
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  
  /* Configure blending factors */
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  
  /* Configure the number of lines and number of pixels per line */
  pLayerCfg1.ImageWidth = 320;
  pLayerCfg1.ImageHeight = 240;  
   
  /* Configure the LTDC */  
  HAL_LTDC_Init(&LtdcHandle);

  /* Configure the Background Layer*/
  HAL_LTDC_ConfigLayer(&LtdcHandle, &pLayerCfg, 0);
  
  /* Configure the Foreground Layer*/
  HAL_LTDC_ConfigLayer(&LtdcHandle, &pLayerCfg1, 1);
}
