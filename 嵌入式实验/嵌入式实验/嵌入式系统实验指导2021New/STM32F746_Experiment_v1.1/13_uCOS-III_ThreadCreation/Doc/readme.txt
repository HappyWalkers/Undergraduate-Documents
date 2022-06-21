/**
  ********************************************************************
  * @experiment  uCOS-III_ThreadCreation
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2016-05-27
  * @brief       Description of the uCOS-III_ThreadCreation example
  ********************************************************************
  *
  * 本实验例程包含源文件：app.c, app_serial.c, os_app_hooks.c, stm32f7xx_it.c
  *
  * 本实验演示uC/OS-III系统中任务的创建和运行过程。
  * 
  * 系统初始化结束后，上电后进行系统硬件初始化以及uC/OS-III初始化，再创建两个应用级
  *
  * 任务，LED1闪烁。
  *
  * 程序中创建两个优先级相同的线程：
  *
  * AppTaskObj0：产生信号量并向串口发送信息。
  *
  * AppTaskObj1：获取信号量，若获取到信号量则发送串口信息。
  *
  */