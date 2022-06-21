#####################################################################
#																	 
#	Created by u'nSP IDE		14:41:13	02/08/17
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

INCLUDES	= -I"C:/Users/xiangxiang.liu/Desktop/Ex09" -I"C:/Generalplus/unSPIDE 3.0.4/library/include" -I"C:/Generalplus/unSPIDE 3.0.4/library/include/sys"

BODY	= -body SPCE060A_061A -nobdy -bfile "C:\Users\xiangxiang.liu\Desktop\Ex09\WifiAT.bdy"

BODYFILE	= "C:\Users\xiangxiang.liu\Desktop\Ex09\WifiAT.bdy" 

BINFILE	= "$(OUTDIR)\WifiAT.S37"

ARYFILE	= "$(OUTDIR)\WifiAT.ary"

SBMFILE	= "$(OUTDIR)\WifiAT.sbm"

OPT	= -S -gstabs -Wall -mglobal-var-iram

ASFLAGS	= -t2 -d

CASFLAGS	= -t2 -wpop

CFLAGS	= $(OPT) -B$(APPDIR)\toolchain\ $(INCLUDES) 

BINTYPE	= -as

LDFLAGS	= -listfile

EXTRAFLAGS	= 


OBJFILES	= \
	"$(OUTDIR)\at_finish_72k.res" \
	"$(OUTDIR)\fail_72k.res" \
	"$(OUTDIR)\lianjie_72k.res" \
	"$(OUTDIR)\success_72k.res" \
	"$(OUTDIR)\status_inq_72k.res" \
	"$(OUTDIR)\ass_72k.res" \
	"$(OUTDIR)\cur_net_72k.res" \
	"$(OUTDIR)\no_ass_72k.res" \
	"$(OUTDIR)\Resource.obj" \
	"$(OUTDIR)\main.obj" \
	"$(OUTDIR)\isr.obj" \
	"$(OUTDIR)\uart.obj" \
	"$(OUTDIR)\wifi.obj" \
	"$(OUTDIR)\SystemTime.obj" \
	"$(OUTDIR)\isr_yuyin.obj" \
	"$(OUTDIR)\Sound.obj" \
	"$(OUTDIR)\hardware.obj" 

"$(OUTDIR)\at_finish_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\at_finish.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\at_finish.72k" "$(OUTDIR)\at_finish_72k.res" RES_AT_FINISH_72K 

"$(OUTDIR)\fail_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\fail.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\fail.72k" "$(OUTDIR)\fail_72k.res" RES_FAIL_72K 

"$(OUTDIR)\lianjie_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\lianjie.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\lianjie.72k" "$(OUTDIR)\lianjie_72k.res" RES_LIANJIE_72K 

"$(OUTDIR)\success_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\success.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\success.72k" "$(OUTDIR)\success_72k.res" RES_SUCCESS_72K 

"$(OUTDIR)\status_inq_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\status_inq.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\status_inq.72k" "$(OUTDIR)\status_inq_72k.res" RES_STATUS_INQ_72K 

"$(OUTDIR)\ass_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\ass.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\ass.72k" "$(OUTDIR)\ass_72k.res" RES_ASS_72K 

"$(OUTDIR)\cur_net_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\cur_net.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\cur_net.72k" "$(OUTDIR)\cur_net_72k.res" RES_CUR_NET_72K 

"$(OUTDIR)\no_ass_72k.res": "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\no_ass.72k"
	$(RESC) "C:\Users\xiangxiang.liu\Desktop\Ex09\voice\no_ass.72k" "$(OUTDIR)\no_ass_72k.res" RES_NO_ASS_72K 

"$(OUTDIR)\Resource.obj": "C:\Users\xiangxiang.liu\Desktop\Ex09\Resource.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -l "$(OUTDIR)\Resource.lst" -o "$(OUTDIR)\Resource.obj" "C:\Users\xiangxiang.liu\Desktop\Ex09\Resource.asm" 

"$(OUTDIR)\main.asm": "C:\Users\xiangxiang.liu\Desktop\Ex09\main.c" ".\wifi\wifi.h" ".\sound\sound.h" ".\wifi\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/main.asm" "C:/Users/xiangxiang.liu/Desktop/Ex09/main.c" 

"$(OUTDIR)\main.obj": "$(OUTDIR)\main.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\main.lst" -o "$(OUTDIR)\main.obj" "$(OUTDIR)\main.asm" 

"$(OUTDIR)\isr.asm": "C:\Users\xiangxiang.liu\Desktop\Ex09\isr.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\wifi\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/isr.asm" "C:/Users/xiangxiang.liu/Desktop/Ex09/isr.c" 

"$(OUTDIR)\isr.obj": "$(OUTDIR)\isr.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\isr.lst" -o "$(OUTDIR)\isr.obj" "$(OUTDIR)\isr.asm" 

"$(OUTDIR)\uart.asm": "C:\Users\xiangxiang.liu\Desktop\Ex09\wifi\uart.c" ".\wifi\UART.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/uart.asm" "C:/Users/xiangxiang.liu/Desktop/Ex09/wifi/uart.c" 

"$(OUTDIR)\uart.obj": "$(OUTDIR)\uart.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\uart.lst" -o "$(OUTDIR)\uart.obj" "$(OUTDIR)\uart.asm" 

"$(OUTDIR)\wifi.asm": "C:\Users\xiangxiang.liu\Desktop\Ex09\wifi\wifi.c" ".\wifi\wifi.h" ".\wifi\SystemTime.h" ".\wifi\UART.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdio.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\_ansi.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stdarg.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" "SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/wifi.asm" "C:/Users/xiangxiang.liu/Desktop/Ex09/wifi/wifi.c" 

"$(OUTDIR)\wifi.obj": "$(OUTDIR)\wifi.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\wifi.lst" -o "$(OUTDIR)\wifi.obj" "$(OUTDIR)\wifi.asm" 

"$(OUTDIR)\SystemTime.asm": "C:\Users\xiangxiang.liu\Desktop\Ex09\wifi\SystemTime.c" ".\wifi\SystemTime.h" "SPCE061A.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\string.h" "C:\Generalplus\unSPIDE 3.0.4\library\include\stddef.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/SystemTime.asm" "C:/Users/xiangxiang.liu/Desktop/Ex09/wifi/SystemTime.c" 

"$(OUTDIR)\SystemTime.obj": "$(OUTDIR)\SystemTime.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\SystemTime.lst" -o "$(OUTDIR)\SystemTime.obj" "$(OUTDIR)\SystemTime.asm" 

"$(OUTDIR)\isr_yuyin.obj": "C:\Users\xiangxiang.liu\Desktop\Ex09\sound\isr_yuyin.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -l "$(OUTDIR)\isr_yuyin.lst" -o "$(OUTDIR)\isr_yuyin.obj" "C:\Users\xiangxiang.liu\Desktop\Ex09\sound\isr_yuyin.asm" 

"$(OUTDIR)\Sound.asm": "C:\Users\xiangxiang.liu\Desktop\Ex09\sound\Sound.c" "spce061a.h" "sound/s480.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/Sound.asm" "C:/Users/xiangxiang.liu/Desktop/Ex09/sound/Sound.c" 

"$(OUTDIR)\Sound.obj": "$(OUTDIR)\Sound.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -l "$(OUTDIR)\Sound.lst" -o "$(OUTDIR)\Sound.obj" "$(OUTDIR)\Sound.asm" 

"$(OUTDIR)\hardware.obj": "C:\Users\xiangxiang.liu\Desktop\Ex09\hardware.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -l "$(OUTDIR)\hardware.lst" -o "$(OUTDIR)\hardware.obj" "C:\Users\xiangxiang.liu\Desktop\Ex09\hardware.asm" 


.SUFFIXES : .c .asm .obj .s37 .tsk .res

all :	 BEFOREBUILD "$(OUTDIR)" $(BINFILE)

BEFOREBUILD :

"$(OUTDIR)" :
	if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(BINFILE) : $(OBJFILES) 
	$(LD) $(BINTYPE) $(ARYFILE) $(BINFILE) $(LDFLAGS) $(BODY) $(EXTRAFLAGS)

compile :	 $(OBJFILES)

clean :
	$(RM) "$(OUTDIR)\at_finish_72k.res" 
	$(RM) "$(OUTDIR)\fail_72k.res" 
	$(RM) "$(OUTDIR)\lianjie_72k.res" 
	$(RM) "$(OUTDIR)\success_72k.res" 
	$(RM) "$(OUTDIR)\status_inq_72k.res" 
	$(RM) "$(OUTDIR)\ass_72k.res" 
	$(RM) "$(OUTDIR)\cur_net_72k.res" 
	$(RM) "$(OUTDIR)\no_ass_72k.res" 
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
	$(RM) "$(OUTDIR)\isr_yuyin.obj" 
	$(RM) "$(OUTDIR)\isr_yuyin.lst" 
	$(RM) "$(OUTDIR)\Sound.obj" 
	$(RM) "$(OUTDIR)\Sound.lst" 
	$(RM) "$(OUTDIR)\Sound.asm" 
	$(RM) "$(OUTDIR)\hardware.obj" 
	$(RM) "$(OUTDIR)\hardware.lst" 
	$(RM) $(BINFILE) $(SBMFILE) 

.c.asm:
	$(CC) $(CFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

.asm.obj:
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

