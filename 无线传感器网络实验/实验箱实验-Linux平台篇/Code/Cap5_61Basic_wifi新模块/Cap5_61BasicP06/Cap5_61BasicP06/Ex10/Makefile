#####################################################################
#																	 
#	Created by u'nSP IDE		17:16:37	02/08/17
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

INCLUDES	= -I"C:/Users/xiangxiang.liu/Desktop/Ex10" -I"C:/Generalplus/unSPIDE 3.0.4/library/include" -I"C:/Generalplus/unSPIDE 3.0.4/library/include/sys"

BODY	= -body SPCE060A_061A -nobdy -bfile "C:\Users\xiangxiang.liu\Desktop\Ex10\WifiTempHumi.bdy"

BODYFILE	= "C:\Users\xiangxiang.liu\Desktop\Ex10\WifiTempHumi.bdy" 

BINFILE	= "$(OUTDIR)\WifiTempHumi.S37"

ARYFILE	= "$(OUTDIR)\WifiTempHumi.ary"

SBMFILE	= "$(OUTDIR)\WifiTempHumi.sbm"

OPT	= -S -gstabs -Wall -mglobal-var-iram

ASFLAGS	= -t2 -d

CASFLAGS	= -t2 -wpop

CFLAGS	= $(OPT) -B$(APPDIR)\toolchain\ $(INCLUDES) 

BINTYPE	= -as

LDFLAGS	= -listfile

EXTRAFLAGS	= 


OBJFILES	= \
	"$(OUTDIR)\Resource.obj" \
	"$(OUTDIR)\main.obj" \
	"$(OUTDIR)\isr.obj" \
	"$(OUTDIR)\uart.obj" \
	"$(OUTDIR)\wifi.obj" \
	"$(OUTDIR)\SystemTime.obj" \
	"$(OUTDIR)\SHT10.obj" 

"$(OUTDIR)\Resource.obj": "C:\Users\xiangxiang.liu\Desktop\Ex10\Resource.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -l "$(OUTDIR)\Resource.lst" -o "$(OUTDIR)\Resource.obj" "C:\Users\xiangxiang.liu\Desktop\Ex10\Resource.asm" 

"$(OUTDIR)\main.asm": "C:\Users\xiangxiang.liu\Desktop\Ex10\main.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\SHT10.h" ".\wifi\UART.h" ".\SPCE061A.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdlib.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\sys\reent.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\machine/_types.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\assert.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\limits.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/main.asm" "C:/Users/xiangxiang.liu/Desktop/Ex10/main.c" 

"$(OUTDIR)\main.obj": "$(OUTDIR)\main.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\main.lst" -o "$(OUTDIR)\main.obj" "$(OUTDIR)\main.asm" 

"$(OUTDIR)\isr.asm": "C:\Users\xiangxiang.liu\Desktop\Ex10\isr.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\wifi\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/isr.asm" "C:/Users/xiangxiang.liu/Desktop/Ex10/isr.c" 

"$(OUTDIR)\isr.obj": "$(OUTDIR)\isr.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\isr.lst" -o "$(OUTDIR)\isr.obj" "$(OUTDIR)\isr.asm" 

"$(OUTDIR)\uart.asm": "C:\Users\xiangxiang.liu\Desktop\Ex10\wifi\uart.c" ".\wifi\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/uart.asm" "C:/Users/xiangxiang.liu/Desktop/Ex10/wifi/uart.c" 

"$(OUTDIR)\uart.obj": "$(OUTDIR)\uart.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\uart.lst" -o "$(OUTDIR)\uart.obj" "$(OUTDIR)\uart.asm" 

"$(OUTDIR)\wifi.asm": "C:\Users\xiangxiang.liu\Desktop\Ex10\wifi\wifi.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\wifi\UART.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/wifi.asm" "C:/Users/xiangxiang.liu/Desktop/Ex10/wifi/wifi.c" 

"$(OUTDIR)\wifi.obj": "$(OUTDIR)\wifi.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\wifi.lst" -o "$(OUTDIR)\wifi.obj" "$(OUTDIR)\wifi.asm" 

"$(OUTDIR)\SystemTime.asm": "C:\Users\xiangxiang.liu\Desktop\Ex10\wifi\SystemTime.c" ".\wifi\SystemTime.h" "SPCE061A.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/SystemTime.asm" "C:/Users/xiangxiang.liu/Desktop/Ex10/wifi/SystemTime.c" 

"$(OUTDIR)\SystemTime.obj": "$(OUTDIR)\SystemTime.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\SystemTime.lst" -o "$(OUTDIR)\SystemTime.obj" "$(OUTDIR)\SystemTime.asm" 

"$(OUTDIR)\SHT10.asm": "C:\Users\xiangxiang.liu\Desktop\Ex10\SHT10.c" ".\SHT10.h" ".\SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/SHT10.asm" "C:/Users/xiangxiang.liu/Desktop/Ex10/SHT10.c" 

"$(OUTDIR)\SHT10.obj": "$(OUTDIR)\SHT10.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\SHT10.lst" -o "$(OUTDIR)\SHT10.obj" "$(OUTDIR)\SHT10.asm" 


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
	$(RM) "$(OUTDIR)\SHT10.obj" 
	$(RM) "$(OUTDIR)\SHT10.lst" 
	$(RM) "$(OUTDIR)\SHT10.asm" 
	$(RM) $(BINFILE) $(SBMFILE) 

.c.asm:
	$(CC) $(CFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

.asm.obj:
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

