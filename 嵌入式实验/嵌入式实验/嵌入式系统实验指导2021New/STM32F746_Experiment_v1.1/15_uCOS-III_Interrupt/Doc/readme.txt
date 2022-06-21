/**
  ********************************************************
  * @experiment  uCOS-III_Interrupt
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2016-05-27
  * @brief       Description of the uCOS-III_Interrupt example
  ********************************************************
  *
  * 本实验例程包含源文件：app.c, app_serial.c, os_app_hooks.c, stm32f7xx_it.c
  *
  * 本实验演示uC/OS-III系统中任务的创建和中断的响应过程。
  * 
  * 系统初始化结束后，上电后进行系统硬件初始化以及uC/OS-III初始化，再创建两个应用级
  *
  * 任务。
  *
  * 程序中创建两个优先级相同的线程：
  *
  * Task_A：检测S3是否被按下并释放，当S3释放时向Task_B发送信号量。
  *
  * Task_B：获取信号量，若获取到信号量则点亮/熄灭LED1并发送串口信息。
  *
  * 将S2按键对应的引脚PA0设为下降沿产生一次中断，中断服务程序向Task_B发送信号量。
  *
  */