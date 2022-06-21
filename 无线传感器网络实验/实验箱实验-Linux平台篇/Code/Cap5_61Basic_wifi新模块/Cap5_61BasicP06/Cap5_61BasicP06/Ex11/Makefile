#####################################################################
#																	 
#	Created by u'nSP IDE		17:14:31	02/08/17
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

INCLUDES	= -I"C:/Users/xiangxiang.liu/Desktop/Ex11" -I"C:/Generalplus/unSPIDE 3.0.4/library/include" -I"C:/Generalplus/unSPIDE 3.0.4/library/include/sys"

BODY	= -body SPCE060A_061A -nobdy -bfile "C:\Users\xiangxiang.liu\Desktop\Ex11\WifiShake.bdy"

BODYFILE	= "C:\Users\xiangxiang.liu\Desktop\Ex11\WifiShake.bdy" 

BINFILE	= "$(OUTDIR)\WifiShake.S37"

ARYFILE	= "$(OUTDIR)\WifiShake.ary"

SBMFILE	= "$(OUTDIR)\WifiShake.sbm"

OPT	= -S -gstabs -Wall -mglobal-var-iram

ASFLAGS	= -t2 -d -sr

CASFLAGS	= -t2 -sr -wpop

CFLAGS	= $(OPT) -B$(APPDIR)\toolchain\ $(INCLUDES) 

BINTYPE	= -as

LDFLAGS	= 

EXTRAFLAGS	= 


OBJFILES	= \
	"$(OUTDIR)\main.obj" \
	"$(OUTDIR)\isr.obj" \
	"$(OUTDIR)\Resource.obj" \
	"$(OUTDIR)\Shake.obj" \
	"$(OUTDIR)\SystemTime.obj" \
	"$(OUTDIR)\uart.obj" \
	"$(OUTDIR)\wifi.obj" 

"$(OUTDIR)\main.asm": "C:\Users\xiangxiang.liu\Desktop\Ex11\main.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\Shake\Shake.h" ".\wifi\UART.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdlib.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\sys\reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\machine/_types.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\assert.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\limits.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/main.asm" "C:/Users/xiangxiang.liu/Desktop/Ex11/main.c" 

"$(OUTDIR)\main.obj": "$(OUTDIR)\main.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\main.obj" "$(OUTDIR)\main.asm" 

"$(OUTDIR)\isr.asm": "C:\Users\xiangxiang.liu\Desktop\Ex11\isr.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\Shake\Shake.h" ".\wifi\UART.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/isr.asm" "C:/Users/xiangxiang.liu/Desktop/Ex11/isr.c" 

"$(OUTDIR)\isr.obj": "$(OUTDIR)\isr.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\isr.obj" "$(OUTDIR)\isr.asm" 

"$(OUTDIR)\Resource.obj": "C:\Users\xiangxiang.liu\Desktop\Ex11\Resource.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)\Resource.obj" "C:\Users\xiangxiang.liu\Desktop\Ex11\Resource.asm" 

"$(OUTDIR)\Shake.asm": "C:\Users\xiangxiang.liu\Desktop\Ex11\Shake\Shake.c" ".\Shake\Shake.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/Shake.asm" "C:/Users/xiangxiang.liu/Desktop/Ex11/Shake/Shake.c" 

"$(OUTDIR)\Shake.obj": "$(OUTDIR)\Shake.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\Shake.obj" "$(OUTDIR)\Shake.asm" 

"$(OUTDIR)\SystemTime.asm": "C:\Users\xiangxiang.liu\Desktop\Ex11\wifi\SystemTime.c" ".\wifi\SystemTime.h" "SPCE061A.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/SystemTime.asm" "C:/Users/xiangxiang.liu/Desktop/Ex11/wifi/SystemTime.c" 

"$(OUTDIR)\SystemTime.obj": "$(OUTDIR)\SystemTime.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\SystemTime.obj" "$(OUTDIR)\SystemTime.asm" 

"$(OUTDIR)\uart.asm": "C:\Users\xiangxiang.liu\Desktop\Ex11\wifi\uart.c" ".\wifi\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/uart.asm" "C:/Users/xiangxiang.liu/Desktop/Ex11/wifi/uart.c" 

"$(OUTDIR)\uart.obj": "$(OUTDIR)\uart.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\uart.obj" "$(OUTDIR)\uart.asm" 

"$(OUTDIR)\wifi.asm": "C:\Users\xiangxiang.liu\Desktop\Ex11\wifi\wifi.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\wifi\UART.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/wifi.asm" "C:/Users/xiangxiang.liu/Desktop/Ex11/wifi/wifi.c" 

"$(OUTDIR)\wifi.obj": "$(OUTDIR)\wifi.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\wifi.obj" "$(OUTDIR)\wifi.asm" 


.SUFFIXES : .c .asm .obj .s37 .tsk .res

all :	 BEFOREBUILD "$(OUTDIR)" $(BINFILE)

BEFOREBUILD :

"$(OUTDIR)" :
	if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(BINFILE) : $(OBJFILES) 
	$(LD) $(BINTYPE) $(ARYFILE) $(BINFILE) $(LDFLAGS) $(BODY) $(EXTRAFLAGS)

compile :	 $(OBJFILES)

clean :
	$(RM) "$(OUTDIR)\main.obj" 
	$(RM) "$(OUTDIR)\main.lst" 
	$(RM) "$(OUTDIR)\main.asm" 
	$(RM) "$(OUTDIR)\isr.obj" 
	$(RM) "$(OUTDIR)\isr.lst" 
	$(RM) "$(OUTDIR)\isr.asm" 
	$(RM) "$(OUTDIR)\Resource.obj" 
	$(RM) "$(OUTDIR)\Resource.lst" 
	$(RM) "$(OUTDIR)\Shake.obj" 
	$(RM) "$(OUTDIR)\Shake.lst" 
	$(RM) "$(OUTDIR)\Shake.asm" 
	$(RM) "$(OUTDIR)\SystemTime.obj" 
	$(RM) "$(OUTDIR)\SystemTime.lst" 
	$(RM) "$(OUTDIR)\SystemTime.asm" 
	$(RM) "$(OUTDIR)\uart.obj" 
	$(RM) "$(OUTDIR)\uart.lst" 
	$(RM) "$(OUTDIR)\uart.asm" 
	$(RM) "$(OUTDIR)\wifi.obj" 
	$(RM) "$(OUTDIR)\wifi.lst" 
	$(RM) "$(OUTDIR)\wifi.asm" 
	$(RM) $(BINFILE) $(SBMFILE) 

.c.asm:
	$(CC) $(CFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

.asm.obj:
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

