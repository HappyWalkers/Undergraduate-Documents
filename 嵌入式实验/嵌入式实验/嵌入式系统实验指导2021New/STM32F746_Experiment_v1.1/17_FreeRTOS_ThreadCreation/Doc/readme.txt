/**
  ********************************************************************
  * @experiment  FreeRTOS_ThreadCreation
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-12-20
  * @brief       Description of the FreeRTOS_ThreadCreation example
  ********************************************************************
  *
  * 本实验例程包含源文件：main.c, stm32f7xx_it.c
  *
  * 本实验演示FreeRTOS系统中线程的创建和运行过程。
  * 
  * 系统初始化结束后，超级终端显示System initialize success
  *
  * 程序中创建两个优先级相同的线程，这两个线程的运行周期为15秒，分为三个阶段：
  *
  * 阶段1(第一个5s)：线程1每100ms切换一次LED1的状态，线程2每500ms向串口发送一次数据“Thread2 is running!”
  *
  * 阶段2(第二个5s)：线程1关闭LED1后挂起自己，线程2继续向串口发送数据
  *
  * 阶段3(第三个5s)：线程2唤醒线程1后挂起自己，线程1被唤醒后每400ms切换一次LED1的状态，
  *
  *                  线程1在阶段3的最后唤醒线程2
  *
  */