编译环境安装说明：
1.安装Keil：打开mdk515.exe程序并按照提示进行安装。
2.安装Cortex-M支持包：打开MDKCM515.EXE程序并进行安装。
3.破解：根据破解说明完成MDK的破解。
4.安装Cortex-M7系列芯片包：解压Keil.STM32F7xx_DFP.zip,将解压出的文件拖入MDK界面，完成M7芯片包的安装。
5.确保实验工程路径中不存在中文，否则只能进行汇编级调试，无法进行代码级调试。


更新说明：
v1.1
1.将每个工程目录下的RAM.ini移植Common文件夹中，所有工程共用同一个RAM.ini。
2.更新Common文件夹中的相关库文件，包括BSP、CMSIS、Component、Driver文件夹中的源文件和头文件，在Middlewares文件夹中添加uCOS-III相关组件。
3.增加uCOS-III相关实验程序。
4.增加I2C_EEPROM实验。
5.增加触摸屏实验。
6.添加Keil环境安装说明文档。
7.优化代码，大幅度降低编译耗时，压缩目标程序。
8.添加make clean批处理文件，双击make_clean.bat可以自动清除目标文件。


注意事项：
1.将中断向量表定向到SRAM的宏定义为VECT_TAB_SRAM，可以在工程->配置->C/C++选项中进行修改（需要同时修改对应的ROM和RAM配置）。