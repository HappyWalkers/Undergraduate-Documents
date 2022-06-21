/**
  ***********************************************************
  * @experiment  UART
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-11-22
  * @brief       Description of the UART example
  ***********************************************************
  *
  * ��ʵ�����̰���Դ�ļ���main.c, config.c, stm32f7xx_it.c
  *
  * ��ʵ�齫USART1����Ϊ�첽ģʽ(��UARTģʽ)��ͨ��9�봮��(J3)
  * 
  * ��PC���͡������ַ�����
  *
  * Ӳ��ԭ��ͼ���£�
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
  * �������гɹ��󳬼��ն���ʾ������Ϣ��
  *
  * System initialize success
  *
  * **** UART-HyperTerminal communication ****
  * Please enter 10 characters using keyboard...
  *
  * ��30��������10���ַ���LED1�����������ն���ʾ������Ϣ��
  *
  * The input is ...(������ַ���)
  *
  * Example finished
  *
  * 30����δ����10���ַ��������ն���ʾ������Ϣ��
  *
  * Timeout!
  *
  * Example finished
  *
  */