/**
  ********************************************************
  * @experiment  LCD_display
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-29
  * @brief       Description of the LCD_display example
  ********************************************************
  *
  * 本实验例程包含源文件：main.c, config.c, stm32f7xx_it.c, stm32f7xx_hal_msp.c
  *
  * 本实验通过配置LTDC驱动液晶屏分层显示，即在同一时间在两个显示层上各自
  * 
  * 显示图像。图片以数组形式分别存在RGB565_320×240.h和L8_320×240.h中，
  *
  * 程序运行后液晶屏上的两幅图像各自向对角方向移动。
  *
  * LCD时间同步原理图如下：
  *
  *                                             Total Width
  *                          <--------------------------------------------------->
  *                    Hsync width HBP             Active Width                HFP
  *                          <---><--><--------------------------------------><-->
  *                      ____    ____|_______________________________________|____ 
  *                          |___|   |                                       |    |
  *                                  |                                       |    |
  *                      __|         |                                       |    |
  *         /|\    /|\  |            |                                       |    |
  *          | VSYNC|   |            |                                       |    |
  *          |Width\|/  |__          |                                       |    |
  *          |     /|\     |         |                                       |    |
  *          |  VBP |      |         |                                       |    |
  *          |     \|/_____|_________|_______________________________________|    |
  *          |     /|\     |         | / / / / / / / / / / / / / / / / / / / |    |
  *          |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  * Total    |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  * Heigh    |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |Active|      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |Heigh |      |         |/ / / / / / Active Display Area / / / /|    |
  *          |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |      |      |         |/ / / / / / / / / / / / / / / / / / / /|    |
  *          |     \|/_____|_________|_______________________________________|    |
  *          |     /|\     |                                                      |
  *          |  VFP |      |                                                      |
  *         \|/    \|/_____|______________________________________________________|
  *
  *
  */