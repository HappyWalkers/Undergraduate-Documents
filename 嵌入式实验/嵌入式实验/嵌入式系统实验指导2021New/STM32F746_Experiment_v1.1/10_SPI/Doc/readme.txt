/**
  ********************************************************
  * @experiment  SPI
  * @author      Li ZuGeng
  * @version     V1.0.0
  * @date        2015-12-05
  * @brief       Description of the SPI example
  ********************************************************
  *
  * 本实验例程包含源文件：main.c, config.c, stm32f7xx_it.c, stm32f7xx_hal_msp.c
  *
  * 本实验使用QSPI接口通过中断模式对SPI接口的Nor Flash进行擦除、写和读等操作。
  *
  * 主程序中，在系统初始化及SPI配置成功后，对Nor Flash依次进行擦除、写、读，
  *
  * 程序成功运行后LED1亮起。
  *
  * 注意：由于涉及到的擦除操作是在某一固定区域，考虑到Flash的擦除次数
  *
  *       有限（通常是10万次左右），测试的次数不要过多！！！
  *
  */