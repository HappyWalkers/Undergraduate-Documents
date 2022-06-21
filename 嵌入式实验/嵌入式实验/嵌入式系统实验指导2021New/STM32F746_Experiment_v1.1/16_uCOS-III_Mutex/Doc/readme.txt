/**
  ********************************************************************
  * @experiment  uCOS-III_Mutex
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2016-05-27
  * @brief       Description of the uCOS-III_Mutex example
  ********************************************************************
  *
  * 本实验例程包含源文件：app.c, app_serial.c, os_app_hooks.c, stm32f7xx_it.c
  *
  * 本实验演示uC/OS-III系统中任务的创建和互斥信号量的使用。
  * 
  * 系统初始化结束后，上电后进行系统硬件初始化以及uC/OS-III初始化，再创建两个应用级
  *
  * 任务。程序中使用互斥信号量作为串口的使用权，实现外设的互斥访问。
  *
  * 程序中创建两个优先级相同的线程：
  *
  * Task_A：阻塞地等待互斥信号量，在获得互斥信号量后向串口发送"Task A is runing\n\r"，然后释放互斥信号量。
  *
  * Task_B：阻塞地等待互斥信号量，在获得互斥信号量后向串口发送"Task B is runing\n\r"，然后释放互斥信号量。
  *
  */