/**
  ********************************************************************
  * @experiment  LwIP_HTTP_Server
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2016-1-20
  * @brief       Description of the LwIP_HTTP_Server example
  ********************************************************************
  *
  * ��ʵ�����̰���Դ�ļ���main.c, stm32f7xx_it.c, httpd_cgi_ssi.c, ethernetif.c,
  *           
  *                       httpd.c, fs.c, app_ethernet.c, stm32f7xx_hal_msp.c
  *
  * ��ʵ����ʾ���ͨ������STM32Cube HAL API����һ������LwIP TCP/IPЭ��ջ��http������
  *
  * 
  * ʵ��ǰ׼����
  * 
  * ʹ�ô���RJ-45��ͷ�����߽�PC��ʵ��������������޸�PC�˱����������ԣ���TCP/IPv4��
  *
  * ��IP����Ϊ�ֶ��������������ã�IP��ַ��Ϊ192.168.1.100������������Ϊ255.255.255.0��
  *
  * Ĭ��������Ϊ192.168.1.1�����ú��������ݺ���"ȷ��"��ť�������á�
  *
  *
  * ϵͳ�ϵ��ϵͳ���г�ʼ����LCD��ʾ"State: Ethernet Initialization ..."��
  *
  *
  * ��ʼ��������������û�����Ӻã�LCD��ʾ"The network cable is not connected"��
  *
  * ����������������ʾ"The network cable is now connected"����ʼ����DHCP��������
  *
  * LCD��ʾ"State: Looking for DHCP sever ..."����ʱʵ���ֱ����PC���������޷��ҵ�DHCP
  *
  * ����������ʱ���Զ���IP����Ϊ192.168.1.108��
  *
  * 
  * ��PC�������������192.168.1.108���ɽ���http�����������а���3��html��ҳ��
  *
  * 1.��һ��ҳ��(home page)Ϊ��̬ҳ�棬չʾSTM32F7ϵ��оƬ�Լ�LwIPЭ��ջ����Ϣ��
  *
  * 2.�ڶ���ҳ��(LED control)�п���ͨ������ҳ����Ϣ����LED��
  *
  * 3.������ҳ��(ADC conversion)��ʾģ��ת����ADC�����ֵ����ҳ��ÿ��һ���Զ�ˢ�¡�
  *
  */