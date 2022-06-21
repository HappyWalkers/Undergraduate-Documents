  /**
  ********************************************************
  * @experiment  TIMER
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-25
  * @brief       Description of the TIMER example
  ********************************************************
  *
  * 本实验例程包含源文件：main.c, config.c, stm32f7xx_it.c
  *
  * 本实验将通过配置定时器(Timer3)，以定时器中断的方式控制
  *
  * LED1闪烁。
  *
  * 程序运行成功后超级终端显示如下信息：
  *
  * ************************************
  * * Timer counter frequency is 10KHz *
  * * Upcounting mode                  *
  * * Initial value is 0               *
  * ************************************
  *
  * Select the value of ARR register:
  * 1. 10000(default)    2. 1000
  *
  * 使用PC键盘选择后，LED1闪烁，超级终端显示如下信息：
  *
  * Example finished
  *
  */
  
  注：
  
  根据例程中对定时器的配置，经过预分频后，定时器从0以固定频率自增到自动重载值（TIMx_ARR寄存器的内容），
  
  产生定时器中断，然后从0开始重新自增。
  
  定时器3频率计算方法如下：
  
  Timer3时钟频率（TIM3CLK）为APB1时钟频率（PCLK1）的2倍，
  
  APB1时钟频率为系统时钟的1/4，
  
  TIM3CLK = PCLK1*2
  PCLK1 = SystemCoreClock/4
  
  所以 TIM3CLK = SystemCoreClock/2
  
  本例程中，需将Timer3时钟频率配置为10KHz，预分频计算方式如下：
  
  Prescaler = (TIM3CLK / TIM3 counter clock) - 1
  Prescaler = ((SystemCoreClock/2) /10 KHz) - 1
  