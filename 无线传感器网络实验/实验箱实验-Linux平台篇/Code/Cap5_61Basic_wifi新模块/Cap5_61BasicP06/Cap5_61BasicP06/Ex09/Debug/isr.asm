// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: C:\GENERA~1\UNSPID~1.4\toolchain\cc1.exe C:\Users\XIANGX~1.LIU\AppData\Local\Temp\ccbqU4Oj.i -fkeep-inline-functions -quiet -dumpbase isr.c -mglobal-var-iram -gstabs -Wall -o .\Debug/isr.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex09/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex09/isr.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.code
Ltext0:
.debug
	.dw '.stabs "int:t1=r1;-32768;32767;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "char:t2=r2;0;127;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "long int:t3=r3;-2147483648;2147483647;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "unsigned int:t4=r4;0;65535;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "long unsigned int:t5=r5;0;4294967295;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "long long int:t6=r6;-2147483648;2147483647;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "long long unsigned int:t7=r7;0;4294967295;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "short int:t8=r8;-32768;32767;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "short unsigned int:t9=r9;0;65535;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "signed char:t10=r10;-32768;32767;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "unsigned char:t11=r11;0;65535;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "float:t12=r1;2;0;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "double:t13=r1;2;0;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "long double:t14=r1;2;0;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "complex int:t15=s2real:1,0,16;imag:1,16,16;;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "complex float:t16=r16;2;0;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "complex double:t17=r17;2;0;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "complex long double:t18=r18;2;0;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "void:t19=19",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs " :T20=eBaudRate300:0,BaudRate600:1,BaudRate1200:2,\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "BaudRate2400:3,BaudRate4096:4,BaudRate4800:5,\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "BaudRate9600:6,BaudRate14400:7,BaudRate19200:8,\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "BaudRate28800:9,BaudRate38400:10,BaudRate57600:11,\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "BaudRate115200:12,MaxBaudRate:13,;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "BAUDRATE:t21=20",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs " :T22=eSTAMODE:0,APMODE:1,APSTAMODE:2,;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs " :T23=eNONKEY:0,WEPKEY:1,WPAKEY:2,\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "WPA2KEY:3,;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "WaitInfo:T24=s4next:25=*24,0,16;tick:5,16,32;\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "flag:1,48,16;;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "WaitInfo:t26=24",128,0,0,0',0x0d,0x0a
.CODE
// ISR ATTRIBUTE FUNCTION, LOCATE in .text SECTION
.text
.debug
	.dw '.stabs "IRQ4:F19",36,0,0,',0,0,offset _IRQ4,seg _IRQ4,0x0d,0x0a
.TEXT
.public _IRQ4
_IRQ4:	.proc
.debug
	.dw '.stabn 0x44,0,13,',0,0
	.dd LM1-_IRQ4
	.dw 0x0d,0x0a
.text
LM1:
	// ISR ATTRIBUTE FUNCTION, PUSH R1,BP
	PUSH R1,BP to [SP]

	// total=1, vars=1
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,1',0x0d, 0x0a
.text
	SP-=1
	BP=SP+1

	R1=BP+4
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,14,',0,0
	.dd LM2-_IRQ4
	.dw 0x0d,0x0a
.text
LM2:
	R2=[28688]	// QImode move
	R1=R2&16
	CMP R1,0	// QImode test
	NSJZ L3	//QImode EQ
.debug
	.dw '.stabn 0x44,0,16,',0,0
	.dd LM3-_IRQ4
	.dw 0x0d,0x0a
.text
LM3:
	CALL _SystemTickISR	// call without return value
.debug
	.dw '.stabn 0x44,0,17,',0,0
	.dd LM4-_IRQ4
	.dw 0x0d,0x0a
.text
LM4:
	R1=16	// QImode move
	[28689]=R1	// QImode move
L3:
.debug
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM5-_IRQ4
	.dw 0x0d,0x0a
.text
LM5:
.debug
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM6-_IRQ4
	.dw 0x0d,0x0a
.text
LM6:
L2:

	SP+=1
	// ISR ATTRIBUTE FUNCTION, POP R1,BP
	POP R1,BP from [SP]
	RETI
	.endp	// end of IRQ4

.debug
	.dw '.stabf ',0,0
	.dd LME1-_IRQ4
	.dw 0x0d,0x0a
.text
LME1:
// ISR ATTRIBUTE FUNCTION, LOCATE in .text SECTION
.text
.debug
	.dw '.stabs "IRQ5:F19",36,0,0,',0,0,offset _IRQ5,seg _IRQ5,0x0d,0x0a
.TEXT
.public _IRQ5
_IRQ5:	.proc
.debug
	.dw '.stabn 0x44,0,28,',0,0
	.dd LM7-_IRQ5
	.dw 0x0d,0x0a
.text
LM7:
	// ISR ATTRIBUTE FUNCTION, PUSH R1,BP
	PUSH R1,BP to [SP]

	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.text
	BP=SP+1

	R1=BP+3
.debug
	.dw '.stabn 0x44,0,29,',0,0
	.dd LM8-_IRQ5
	.dw 0x0d,0x0a
.text
LM8:
	R2=1	// QImode move
	[28690]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,30,',0,0
	.dd LM9-_IRQ5
	.dw 0x0d,0x0a
.text
LM9:
	R2=4	// QImode move
	[28689]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,31,',0,0
	.dd LM10-_IRQ5
	.dw 0x0d,0x0a
.text
LM10:
.debug
	.dw '.stabn 0x44,0,31,',0,0
	.dd LM11-_IRQ5
	.dw 0x0d,0x0a
.text
LM11:
L5:

	// ISR ATTRIBUTE FUNCTION, POP R1,BP
	POP R1,BP from [SP]
	RETI
	.endp	// end of IRQ5

.debug
	.dw '.stabf ',0,0
	.dd LME2-_IRQ5
	.dw 0x0d,0x0a
.text
LME2:
.external _SystemTickISR
	.end
