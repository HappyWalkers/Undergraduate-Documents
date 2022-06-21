#####################################################################
#																	 
#	Created by u'nSP IDE		10:14:35	09/12/18
#
#####################################################################




APPDIR	= C:\GENERA~1\UNSPID~1.4

OUTDIR	= .\Debug

CC	= $(APPDIR)\toolchain\gcc

AS	= $(APPDIR)\toolchain\xasm16

LD	= $(APPDIR)\toolchain\xlink16

AR	= $(APPDIR)\toolchain\xlib16

RESC	= $(APPDIR)\toolchain\resc

RM	= $(APPDIR)\toolchain\rm -f

INCLUDES	= -I"E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake" -I"C:/Generalplus/unSPIDE 3.0.4/library/include" -I"C:/Generalplus/unSPIDE 3.0.4/library/include/sys"

BODY	= -body SPCE060A_061A -nobdy -bfile "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\wifi_hflpb_shake.bdy"

BODYFILE	= "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\wifi_hflpb_shake.bdy" 

BINFILE	= "$(OUTDIR)\wifi_hflpb_shake.S37"

ARYFILE	= "$(OUTDIR)\wifi_hflpb_shake.ary"

SBMFILE	= "$(OUTDIR)\wifi_hflpb_shake.sbm"

OPT	= -S -gstabs -Wall -mglobal-var-iram

ASFLAGS	= -t2 -d -sr

CASFLAGS	= -t2 -sr -wpop

CFLAGS	= $(OPT) -B$(APPDIR)\toolchain\ $(INCLUDES) 

BINTYPE	= -as

LDFLAGS	= 

EXTRAFLAGS	= 


OBJFILES	= \
	"$(OUTDIR)\Resource.obj" \
	"$(OUTDIR)\main.obj" \
	"$(OUTDIR)\isr.obj" \
	"$(OUTDIR)\uart.obj" \
	"$(OUTDIR)\wifi.obj" \
	"$(OUTDIR)\SystemTime.obj" \
	"$(OUTDIR)\wifi_pkgman.obj" \
	"$(OUTDIR)\shake.obj" 

"$(OUTDIR)\Resource.obj": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\Resource.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)\Resource.obj" "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\Resource.asm" 

"$(OUTDIR)\main.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\main.c" ".\wifi_drv\wifi.h" ".\SystemTime.h" ".\Shake.h" ".\wifi_pkgman.h" ".\wifi_drv\UART.h" ".\SPCE061A.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/main.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/main.c" 

"$(OUTDIR)\main.obj": "$(OUTDIR)\main.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\main.obj" "$(OUTDIR)\main.asm" 

"$(OUTDIR)\isr.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\isr.c" ".\SPCE061A.h" ".\SystemTime.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/isr.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/isr.c" 

"$(OUTDIR)\isr.obj": "$(OUTDIR)\isr.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\isr.obj" "$(OUTDIR)\isr.asm" 

"$(OUTDIR)\uart.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\wifi_drv\uart.c" ".\wifi_drv\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/uart.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/wifi_drv/uart.c" 

"$(OUTDIR)\uart.obj": "$(OUTDIR)\uart.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\uart.obj" "$(OUTDIR)\uart.asm" 

"$(OUTDIR)\wifi.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\wifi_drv\wifi.c" ".\wifi_drv\wifi.h" ".\wifi_drv\UART.h" "SystemTime.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/wifi.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/wifi_drv/wifi.c" 

"$(OUTDIR)\wifi.obj": "$(OUTDIR)\wifi.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\wifi.obj" "$(OUTDIR)\wifi.asm" 

"$(OUTDIR)\SystemTime.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\SystemTime.c" ".\SystemTime.h" ".\SPCE061A.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/SystemTime.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/SystemTime.c" 

"$(OUTDIR)\SystemTime.obj": "$(OUTDIR)\SystemTime.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\SystemTime.obj" "$(OUTDIR)\SystemTime.asm" 

"$(OUTDIR)\wifi_pkgman.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\wifi_pkgman.c" ".\wifi_pkgman.h" ".\wifi_drv\wifi.h" ".\wifi_drv\UART.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdlib.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\sys\reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\machine/_types.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\assert.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\limits.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\errno.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\sys\errno.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\sys/reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\machine\_types.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/wifi_pkgman.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/wifi_pkgman.c" 

"$(OUTDIR)\wifi_pkgman.obj": "$(OUTDIR)\wifi_pkgman.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\wifi_pkgman.obj" "$(OUTDIR)\wifi_pkgman.asm" 

"$(OUTDIR)\shake.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic_wifi新模块\Cap5_61BasicP06\Cap5_61BasicP06\wifi_hflpb_shake\shake.c" ".\Shake.h" ".\SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/shake.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic_wifi新模块/Cap5_61BasicP06/Cap5_61BasicP06/wifi_hflpb_shake/shake.c" 

"$(OUTDIR)\shake.obj": "$(OUTDIR)\shake.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\shake.obj" "$(OUTDIR)\shake.asm" 


.SUFFIXES : .c .asm .obj .s37 .tsk .res

all :	 BEFOREBUILD "$(OUTDIR)" $(BINFILE)

BEFOREBUILD :

"$(OUTDIR)" :
	if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(BINFILE) : $(OBJFILES) 
	$(LD) $(BINTYPE) $(ARYFILE) $(BINFILE) $(LDFLAGS) $(BODY) $(EXTRAFLAGS)

compile :	 $(OBJFILES)

clean :
	$(RM) "$(OUTDIR)\Resource.obj" 
	$(RM) "$(OUTDIR)\Resource.lst" 
	$(RM) "$(OUTDIR)\main.obj" 
	$(RM) "$(OUTDIR)\main.lst" 
	$(RM) "$(OUTDIR)\main.asm" 
	$(RM) "$(OUTDIR)\isr.obj" 
	$(RM) "$(OUTDIR)\isr.lst" 
	$(RM) "$(OUTDIR)\isr.asm" 
	$(RM) "$(OUTDIR)\uart.obj" 
	$(RM) "$(OUTDIR)\uart.lst" 
	$(RM) "$(OUTDIR)\uart.asm" 
	$(RM) "$(OUTDIR)\wifi.obj" 
	$(RM) "$(OUTDIR)\wifi.lst" 
	$(RM) "$(OUTDIR)\wifi.asm" 
	$(RM) "$(OUTDIR)\SystemTime.obj" 
	$(RM) "$(OUTDIR)\SystemTime.lst" 
	$(RM) "$(OUTDIR)\SystemTime.asm" 
	$(RM) "$(OUTDIR)\wifi_pkgman.obj" 
	$(RM) "$(OUTDIR)\wifi_pkgman.lst" 
	$(RM) "$(OUTDIR)\wifi_pkgman.asm" 
	$(RM) "$(OUTDIR)\shake.obj" 
	$(RM) "$(OUTDIR)\shake.lst" 
	$(RM) "$(OUTDIR)\shake.asm" 
	$(RM) $(BINFILE) $(SBMFILE) 

.c.asm:
	$(CC) $(CFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

.asm.obj:
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

