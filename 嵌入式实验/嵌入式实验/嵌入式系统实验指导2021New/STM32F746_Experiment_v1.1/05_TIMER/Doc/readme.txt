  /**
  ********************************************************
  * @experiment  TIMER
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-25
  * @brief       Description of the TIMER example
  ********************************************************
  *
  * ��ʵ�����̰���Դ�ļ���main.c, config.c, stm32f7xx_it.c
  *
  * ��ʵ�齫ͨ�����ö�ʱ��(Timer3)���Զ�ʱ���жϵķ�ʽ����
  *
  * LED1��˸��
  *
  * �������гɹ��󳬼��ն���ʾ������Ϣ��
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
  * ʹ��PC����ѡ���LED1��˸�������ն���ʾ������Ϣ��
  *
  * Example finished
  *
  */
  
  ע��
  
  ���������жԶ�ʱ�������ã�����Ԥ��Ƶ�󣬶�ʱ����0�Թ̶�Ƶ���������Զ�����ֵ��TIMx_ARR�Ĵ��������ݣ���
  
  ������ʱ���жϣ�Ȼ���0��ʼ����������
  
  ��ʱ��3Ƶ�ʼ��㷽�����£�
  
  Timer3ʱ��Ƶ�ʣ�TIM3CLK��ΪAPB1ʱ��Ƶ�ʣ�PCLK1����2����
  
  APB1ʱ��Ƶ��Ϊϵͳʱ�ӵ�1/4��
  
  TIM3CLK = PCLK1*2
  PCLK1 = SystemCoreClock/4
  
  ���� TIM3CLK = SystemCoreClock/2
  
  �������У��轫Timer3ʱ��Ƶ������Ϊ10KHz��Ԥ��Ƶ���㷽ʽ���£�
  
  Prescaler = (TIM3CLK / TIM3 counter clock) - 1
  Prescaler = ((SystemCoreClock/2) /10 KHz) - 1
  