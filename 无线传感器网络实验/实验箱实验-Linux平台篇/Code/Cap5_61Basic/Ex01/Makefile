#####################################################################
#																	 
#	Created by u'nSP IDE		13:59:16	09/07/18
#
#####################################################################




APPDIR	= D:\unSPIDE

OUTDIR	= .\Debug

CC	= $(APPDIR)\toolchain\gcc

AS	= $(APPDIR)\toolchain\xasm16

LD	= $(APPDIR)\toolchain\xlink16

AR	= $(APPDIR)\toolchain\xlib16

RESC	= $(APPDIR)\toolchain\resc

RM	= $(APPDIR)\toolchain\rm -f

INCLUDES	= -I"E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic/Ex01" -I"D:/unSPIDE/library/include" -I"D:/unSPIDE/library/include/sys"

BODY	= -body SPCE060A_061A -nobdy -bfile "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic\Ex01\Ex_C_Basic.bdy"

BODYFILE	= "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic\Ex01\Ex_C_Basic.bdy" 

BINFILE	= "$(OUTDIR)\Ex_C_Basic.S37"

ARYFILE	= "$(OUTDIR)\Ex_C_Basic.ary"

SBMFILE	= "$(OUTDIR)\Ex_C_Basic.sbm"

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

"$(OUTDIR)\main.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic\Ex01\main.c" ".\SPCE061A.h" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/main.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic/Ex01/main.c" 

"$(OUTDIR)\main.obj": "$(OUTDIR)\main.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\main.obj" "$(OUTDIR)\main.asm" 

"$(OUTDIR)\isr.asm": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic\Ex01\isr.c" 
	set PATH="$(APPDIR)\toolchain\";%PATH% & \
	$(CC) $(CFLAGS) -o "$(OUTDIR)/isr.asm" "E:/光盘资料V1.2.0（中南大学）/实验指导书/实验箱实验-Linux平台篇/Code/Cap5_61Basic/Ex01/isr.c" 

"$(OUTDIR)\isr.obj": "$(OUTDIR)\isr.asm"
	$(AS) $(CASFLAGS) $(INCLUDES) -o "$(OUTDIR)\isr.obj" "$(OUTDIR)\isr.asm" 

"$(OUTDIR)\Resource.obj": "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic\Ex01\Resource.asm" 
	$(AS) $(ASFLAGS) $(INCLUDES) -o "$(OUTDIR)\Resource.obj" "E:\光盘资料V1.2.0（中南大学）\实验指导书\实验箱实验-Linux平台篇\Code\Cap5_61Basic\Ex01\Resource.asm" 


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

