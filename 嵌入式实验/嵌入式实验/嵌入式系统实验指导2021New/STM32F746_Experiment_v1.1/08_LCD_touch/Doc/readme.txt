/**
  ********************************************************
  * @experiment  LCD_touch
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2016-05-21
  * @brief       Description of the LCD_touch example
  ********************************************************
  *
  * 本实验例程包含源文件：main.c, calibration.c, rtc.c, stm32f7xx_it.c, BASIC_Touch.c
  *
  * 本实验演示触摸屏功能，程序运行后液晶屏中提示触摸一下液晶屏，并开始校正触摸屏，
  *
  * 再根据提示触摸屏幕左上角和右下角的圆点，完成触摸屏的校正工作。校正后触摸屏幕即可以
  *
  * 在触摸的位置留下黑点并将该点的x轴和y轴坐标发送至串口。
  *
  */