/**
  ********************************************************************
  * @experiment  FreeRTOS_Message_Queue
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-12-20
  * @brief       Description of the FreeRTOS_Message_Queue example
  ********************************************************************
  *
  * 本实验例程包含源文件：main.c, stm32f7xx_it.c
  *
  * 本实验演示FreeRTOS系统中使用消息队列进行线程间通信的过程。
  * 
  * 系统初始化结束后，超级终端显示System initialize success
  *
  * 程序中创建两个优先级相同的线程，发送线程和接收线程：
  *
  * 发送线程：每隔1s生成一个递增的数据并发送至消息队列，超级终端显示“Message produced”
  *
  * 接收线程：获取消息队列中的数据并验证，数据无误则使LED1状态变化
  *
  */