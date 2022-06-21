#####################################################################
#																	 
#	Created by u'nSP IDE		11:07:30	09/06/16
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

INCLUDES	= -I"E:/光盘资料/矩阵试验箱光盘资料V1.1/实验指导书/Code/Cap5_61Basic/Ex05" -I"C:/Generalplus/unSPIDE 3.0.4/library/include" -I"C:/Generalplus/unSPIDE 3.0.4/library/include/sys"

BODY	= -body SPCE060A_061A -nobdy -bfile "E:\光盘资料\矩阵试验箱光盘资料V1.1\实验指导书\Code\Cap5_61Basic\Ex05\UART.bdy"

BODYFILE	= "E:\光盘资料\矩阵试验箱光盘资料V1.1\实验指导书\Code\Cap5_61Basic\Ex05\UART.bdy" 

BINFILE	= "$(OUTDIR)\UART.S37"

ARYFILE	= "$(OUTDIR)\UART.ary"

SBMFILE	= "$(OUTDIR)\UART.sbm"

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
	"$(OUTDIR)\Resource.obj" 

"$(OUTDIR)\main.asm": "E:\光盘资料\矩阵试验箱光盘资料V1.1\实验指导书\Code\Cap5_61Basic\Ex05\main.c" ".\SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/main.asm" "E:/光盘资料/矩阵试验箱光盘资料V1.1/实验指导书/Code/Cap5_61Basic/Ex05/main.c" 

"$(OUTDIR)\main.obj": "$(OUTDIR)\main.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\main.obj" "$(OUTDIR)\main.asm" 

"$(OUTDIR)\isr.asm": "E:\光盘资料\矩阵试验箱光盘资料V1.1\实验指导书\Code\Cap5_61Basic\Ex05\isr.c" ".\SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/isr.asm" "E:/光盘资料/矩阵试验箱光盘资料V1.1/实验指导书/Code/Cap5_61Basic/Ex05/isr.c" 

"$(OUTDIR)\isr.obj": "$(OUTDIR)\isr.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\isr.obj" "$(OUTDIR)\isr.asm" 

"$(OUTDIR)\Resource.obj": "E:\光盘资料\矩阵试验箱光盘资料V1.1\实验指导书\Code\Cap5_61Basic\Ex05\Resource.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)\Resource.obj" "E:\光盘资料\矩阵试验箱光盘资料V1.1\实验指导书\Code\Cap5_61Basic\Ex05\Resource.asm" 


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
	$(RM) $(BINFILE) $(SBMFILE) 

.c.asm:
	$(CC) $(CFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

.asm.obj:
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)/$@" $<

