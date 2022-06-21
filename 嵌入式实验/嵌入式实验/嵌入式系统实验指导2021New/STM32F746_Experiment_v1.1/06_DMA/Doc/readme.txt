/**
  ********************************************************
  * @experiment  DMA
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-21
  * @brief       Description of the DMA example
  ********************************************************
  *
  * 本实验例程包含源文件：main.c, config.c, stm32f7xx_it.c
  *
  * 本实验演示FIFO方式的DMA传输，将数据以4字节长度为单位从
  *
  * Flash传送至SRAM，传输结束后点亮LED1。
  *
  * 程序运行成功后超级终端显示如下信息：
  *
  * System initialize success
  *
  * DMA传输结束后LED1点亮，超级终端显示如下信息：
  *
  * DMA transmition success
  *
  * Example finished
  *
  */