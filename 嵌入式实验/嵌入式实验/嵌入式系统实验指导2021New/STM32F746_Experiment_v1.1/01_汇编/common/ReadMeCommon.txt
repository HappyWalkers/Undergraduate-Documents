EdukitIII实验箱例程 MDK工程的基本文件组织结构：

   工程名
      	|----Startup 	启动代码 （S3C2410A.S）,请注意最好使用例程所带的启动代码，
      	|                          MDK自动生成的启动代码需要修改才可使用于实验箱上。
      	|----Common		公用代码（2410lib.c,sys_init.c）
      	|
		|----Source     用户源代码
      	|
		|----Script     脚本文件（调试文件ini，分散加载文件sct等）
        |
	 	----ReadMe     工程说明文档

===========================================================================================
实验箱例程文件目录结构:
	4.1.1_memory_test
	4.2_led_test
	4.3_int_test
	4.4_uart_test
	4.5_rtc_test
	4.6_8led_test
	4.7_timer_test
	5.1_color_lcd_test
	5.2_keyboard_test
	5.3_tsp_test
	6.1_iic_test
	6.2_tftp_test
	6.3_iis_test
	6.4_usb_test
	6.5_spi_test
	6.6_irda_test
	7.1_adc_test
	7.2_pwm_test
	7.3.1_sdi_test
	8.1_gprs_test
        以上目录分别对应实验教程各章节的例程.
	common  提供所有例程的公共文件;
	tools	提供一些例程运行所需要的工具软件;
============================================================================================
工程的Option设置: 
    Device下选择Samsung-S3C2410;
	Target下设置 	off-chip  ROM1: 0x0,0x200000  Startup
                 	off-chip  RAM1: 0x30000000,0x4000000
		     		on-chip   IRAM1:0x40000000,0x1000
	Output下设置文件夹为当前目录下的/obj;
	Listing下设置文件夹为当前目录下的/lst;
	C/C++和ASM下在includ path 文本框中将common目录所在路径加入;
	Linker下设置Scatter File,如果在RAM中运行则选择"RuninRAM.SCT",  
                             如果在FLash中运行则选择"RuninFLash.SCT"(这两个文件均在common目录下);
							 请注意在Script文件组下添加这两个文件时必须指定其为文本文件,而不是汇编语言文件.
	Debug下选择 use Simulator则可在PC上进行软件仿真;
	       选择 use ULINK ARM Debugger则进行目标板联机调试;
		   选择 Run to main 则程序自动运行到main()函数后暂停，须点击Run按钮或按F5键程序才继续运行。
               在Initialization文本框中可加入调试命令脚本文件,以帮助调试.
	Utilities下选择 ULINK ARM Debugger,点击setting按钮设置烧写参数
			RAM for Algorithm 设置Start: 0x40000000,Size 0x800
	        Programming Algorithm选择 AM29F160DB Flash Ext Flash 16-bit  2M

=============================================================================================
调试命令文件(INI)用于使用软件仿真和联机测试时,以下是几个常用的命令,用户可以根据调试需要来写自己的调试命令文件. 
	pc=0x30000000    		
		令PC指向0x30000000处;(例程在RAM中运行时可指向0x30000000,如果在Flash中运行则指向0x000)
	map    0x4c000000, 0x53000020 READ WRITE exec
		指定某段存储区域的属性为可读,可写,可执行;
	Go startaddr, stopaddr
		程序从startaddr开始执行,到stopaddr处停止;起始地址都可以缺省. 也可用函数名表示地址例如 G , main

==============================================================================================
分散加载文件(sct)用于加载映像文件到存储空间中,MDK可根据存储设置自动生成,复杂应用程序则需要自行编写. 
以下是在RAM中运行程序的SCT文:
LR_ROM1 0x30000000         {    ; load region
  ER_ROM1 0x30000000 0x00300000  {  ; load address = execution address
   *.o (RESET, +First)
;   *(InRoot$$Sections)
   .ANY (+RO)
  }
  RW_RAM1 0x30300000 0x03D00000  {  ; RW data
   .ANY (+RW +ZI)
  }
}

以下是在Flash中运行程序的SCT文件: 

LR_ROM1 0x00000000         {    ; load region
  ER_ROM1 0x00000000 0x00200000  {  ; load address = execution address
   *.o (RESET, +First)
   *(InRoot$$Sections)
   .ANY (+RO)
  }
  RW_RAM1 0x30000000 0x04000000  {  ; RW data
   .ANY (+RW +ZI)
  }
  RW_IRAM1 0x40000000 0x00001000  {
   .ANY (+RW +ZI)
  }
  
============================================================================================







       