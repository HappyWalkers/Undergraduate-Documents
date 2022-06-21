/**
  ***********************************************************
  * @experiment  UART
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-22
  * @brief       Description of the UART example
  ***********************************************************
  *
  * 本实验例程包含源文件：main.c, config.c, stm32f7xx_it.c
  *
  * 本实验将USART1配置为异步模式(即UART模式)，通过9针串口(J3)
  * 
  * 向PC发送、接收字符串。
  *
  * 硬件原理图如下：
  *
  *  ________________
  * |   STM32F746    |                  _______________
  * |    ____________|                 |      PC       |
  * |   |UART1       |                 | HyperTerminal |
  * |   |            |                 |               |
  * |   |    TX(PA9) |_________________| RX            |
  * |   |            |                 |               |
  * |   |            |   RS232 Cable   |               |
  * |   |    RX(PA10)|_________________| TX            |
  * |   |____________|                 |               |
  * |                |                 |_______________|
  * |________________| 
  *
  *
  * 程序运行成功后超级终端显示如下信息：
  *
  * System initialize success
  *
  * **** UART-HyperTerminal communication ****
  * Please enter 10 characters using keyboard...
  *
  * 在30秒内输入10个字符后LED1点亮，超级终端显示如下信息：
  *
  * The input is ...(输入的字符串)
  *
  * Example finished
  *
  * 30秒内未输入10个字符，超级终端显示如下信息：
  *
  * Timeout!
  *
  * Example finished
  *
  */