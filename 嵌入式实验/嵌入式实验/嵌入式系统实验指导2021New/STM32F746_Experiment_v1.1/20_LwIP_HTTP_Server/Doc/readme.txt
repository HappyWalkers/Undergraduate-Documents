/**
  ********************************************************************
  * @experiment  LwIP_HTTP_Server
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2016-1-20
  * @brief       Description of the LwIP_HTTP_Server example
  ********************************************************************
  *
  * 本实验例程包含源文件：main.c, stm32f7xx_it.c, httpd_cgi_ssi.c, ethernetif.c,
  *           
  *                       httpd.c, fs.c, app_ethernet.c, stm32f7xx_hal_msp.c
  *
  * 本实验演示如何通过调用STM32Cube HAL API建立一个基于LwIP TCP/IP协议栈的http服务器
  *
  * 
  * 实验前准备：
  * 
  * 使用带有RJ-45接头的网线将PC与实验板连接起来，修改PC端本地连接属性，将TCP/IPv4中
  *
  * 的IP设置为手动，按照如下设置：IP地址设为192.168.1.100，子网掩码设为255.255.255.0，
  *
  * 默认网关设为192.168.1.1。设置好以上内容后点击"确认"按钮保存设置。
  *
  *
  * 系统上电后，系统进行初始化，LCD显示"State: Ethernet Initialization ..."。
  *
  *
  * 初始化结束后，若网线没有连接好，LCD显示"The network cable is not connected"，
  *
  * 网线连接正常则显示"The network cable is now connected"并开始搜索DHCP服务器，
  *
  * LCD显示"State: Looking for DHCP sever ..."，此时实验板直接与PC连接所以无法找到DHCP
  *
  * 服务器，超时后自动将IP设置为192.168.1.108。
  *
  * 
  * 在PC端浏览器中输入192.168.1.108即可进入http服务器，其中包含3个html网页：
  *
  * 1.第一个页面(home page)为静态页面，展示STM32F7系列芯片以及LwIP协议栈的信息。
  *
  * 2.第二个页面(LED control)中可以通过发送页面信息控制LED。
  *
  * 3.第三个页面(ADC conversion)显示模数转换器ADC的输出值，该页面每隔一秒自动刷新。
  *
  */