/**
  ********************************************************
  * @experiment  EXTI
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-21
  * @brief       Description of the EXTI example
  ********************************************************
  *
  * 本实验例程包含源文件：main.c, config.c, stm32f7xx_it.c
  *
  * 本实验将按键开关S3配置为外部中断(EXTI13)的中断源，通过
  * 
  * 按下按键触发中断，使LED1跳变
  *
  * 硬件原理图如下：
  *
  *  ________________
  * |   STM32F746    |        +3.3V
  * |                |         ___
  * |                |          |
  * |                |         _|_
  * |                |         | |
  * |                |         |_| 100K
  * |                |          |         S3
  * |           PC13 |__________|_______.----.___
  * |                |                           |
  * |                |                          _|_
  * |________________|                           -  GND
  *
  *
  * 程序运行成功后超级终端显示如下信息：
  *
  * System initialize success
  *
  * 按下按键S3使LED1跳变，超级终端显示如下信息：
  *
  * LED1 switched
  *
  */