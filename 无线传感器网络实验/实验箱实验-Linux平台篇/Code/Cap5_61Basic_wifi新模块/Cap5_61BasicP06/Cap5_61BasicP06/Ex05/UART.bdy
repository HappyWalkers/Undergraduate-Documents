[EMULATOR]
EMUS=Default,nDefault.dll,FALSE;
EMUS=PortIO,PortIO.dll,TRUE;
EMUS=Input_Output,Input_Output.dll,TRUE;
EMUS=AD,AdSim.dll,TRUE;
EMUS=PWM,PwmSIm.dll,TRUE;

[Debug Menu]
Count=4
Menu1=Memory
Menu2=Register
Menu3=Command
Menu4=BreakPoints


[Memory]
Name=Memory
Type=2
Start=0
End=65535
ReadOnly=0
Bits=16
EnableFlag=3

[Register]
Name=RegisterWindow
Type=1
EnableFlag=3

[Command]
Name=CommandWindow
Type=1
EnableFlag=3

[BreakPoints]
Name = BreakPointsWindow
Type=1
EnableFlag=3

[ARCH]
BODY=SPCE060A_061A;
SEC=RAM,0,7FF,W;
SEC=FLASH,8000,FBFF,F;
SEC=SysROM,FC00,FFF4,F;
SEC=Interrupt,FFF5,FFFF,F;
SEC=I/O,7000,7FFF,W;
BANK=1,FFFF;
CPUTYPE=unsp002;
DMAENABLE=1;
DEFAULTISAVER=ISA11;
PESUDOINST=7fff;
TSMCPSUDOINST=7555;
MEMORYTYPE=TsmcFlash;
LOCATE=IRQVec,FFF5;
DISABLEOUTPUTONLY=1;
HASEZPROBE=1;
DISABLECOMPILEROPTIMIZE=1;

