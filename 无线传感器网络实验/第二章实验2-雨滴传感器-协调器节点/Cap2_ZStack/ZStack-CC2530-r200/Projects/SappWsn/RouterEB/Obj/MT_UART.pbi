This is an internal working file generated by the Source Browser.
11:11 57s
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Components\mt\MT_UART.c
-f
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\zstack\Tools\CC2530DB\f8wRouter.cfg
-f
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\zstack\Tools\CC2530DB\f8wConfig.cfg
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Components\mt\MT_UART.c
-D
ZTOOL_P1
-D
MT_TASK
-D
MT_SYS_FUNC
-D
MT_ZDO_FUNC
-D
LCD_SUPPORTED=DEBUG
-D
SAPP_ZSTACK
-lC
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\RouterEB\List\
-lA
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\RouterEB\List\
--diag_suppress
Pe001,Pa010
-o
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\RouterEB\Obj\
-e
--no_code_motion
--debug
--core=plain
--dptr=16,1
--data_model=large
--code_model=banked
--calling_convention=xdata_reentrant
--place_constants=data_rom
--nr_virtual_regs
16
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\Source\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\zstack\ZMain\TI2530DB\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\hal\include\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\hal\target\CC2530EB\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\mac\include\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\mac\high_level\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\mac\low_level\srf04\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\mac\low_level\srf04\single_chip\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\mt\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\osal\include\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\services\saddr\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\services\sdata\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\stack\af\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\stack\nwk\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\stack\sapi\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\stack\sec\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\stack\sys\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\stack\zdo\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\zmac\
-I
E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap2_ZStack\ZStack-CC2530-r200\Projects\SappWsn\..\..\Components\zmac\f8w\
-Ohz
--require_prototypes
