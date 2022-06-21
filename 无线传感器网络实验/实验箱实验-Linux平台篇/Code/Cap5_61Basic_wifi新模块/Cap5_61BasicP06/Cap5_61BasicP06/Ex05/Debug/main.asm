// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: C:\GENERA~1\UNSPID~1.4\toolchain\cc1.exe C:\Users\XIANGX~1.LIU\AppData\Local\Temp\ccrpDwmK.i -fkeep-inline-functions -quiet -dumpbase main.c -mglobal-var-iram -gstabs -Wall -o .\Debug/main.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "E:/π‚≈Ã◊ ¡œ/æÿ’Û ‘—Èœ‰π‚≈Ã◊ ¡œV1.1/ µ—È÷∏µº È/Code/Cap5_61Basic/Ex05/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "E:/π/342≈/314◊/312¡/317/æ/330’/363 /324—/351œ/344π/342≈/314◊/312¡/317V1.1/ /265—/351÷/270µ/274 /351/Code/Cap5_61Basic/Ex05/main.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
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
.code
.debug
	.dw '.stabs "main:F1",36,0,0,',0,0,offset _main,seg _main,0x0d,0x0a
.CODE
.public _main
_main:	.proc
.debug
	.dw '.stabn 0x44,0,13,',0,0
	.dd LM1-_main
	.dw 0x0d,0x0a
.code
LM1:
	// total=1, vars=1
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,1',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=1
	BP=SP+1

	R1=BP+4
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,14,',0,0
	.dd LM2-_main
	.dw 0x0d,0x0a
.code
LM2:
// GCC inline ASM start
	IRQ OFF
// GCC inline ASM end
.debug
	.dw '.stabn 0x44,0,15,',0,0
	.dd LM3-_main
	.dw 0x0d,0x0a
.code
LM3:
	CALL _Uart_Init	// call without return value
.debug
	.dw '.stabn 0x44,0,16,',0,0
	.dd LM4-_main
	.dw 0x0d,0x0a
.code
LM4:
L3:
	PC=L5	// jump
	PC=L4	// jump
L5:
.debug
	.dw '.stabn 0x44,0,18,',0,0
	.dd LM5-_main
	.dw 0x0d,0x0a
.code
LM5:
	R1=1	// QImode move
	[28690]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,20,',0,0
	.dd LM6-_main
	.dw 0x0d,0x0a
.code
LM6:
	R2=[28706]	// QImode move
	R1=R2&128
	CMP R1,0	// QImode test
	NSJZ L6	//QImode EQ
.debug
	.dw '.stabn 0x44,0,22,',0,0
	.dd LM7-_main
	.dw 0x0d,0x0a
.code
LM7:
L7:
	R2=[28706]	// QImode move
	R1=R2&64
	CMP R1,0	// QImode test
	NSJZ L9	//QImode EQ
	PC=L8	// jump
L9:
	PC=L7	// jump
L8:
.debug
	.dw '.stabn 0x44,0,23,',0,0
	.dd LM8-_main
	.dw 0x0d,0x0a
.code
LM8:
	R1=[28707]	// QImode move
	[28707]=R1	// QImode move
L6:
.debug
	.dw '.stabn 0x44,0,25,',0,0
	.dd LM9-_main
	.dw 0x0d,0x0a
.code
LM9:
	PC=L3	// jump
L4:
.debug
	.dw '.stabn 0x44,0,26,',0,0
	.dd LM10-_main
	.dw 0x0d,0x0a
.code
LM10:
	R1=0	// QImode move
	PC=L2	// jump
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM11-_main
	.dw 0x0d,0x0a
.code
LM11:
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM12-_main
	.dw 0x0d,0x0a
.code
LM12:
L2:

	SP+=1
	POP BP from [SP]
	RETF
	.endp	// end of main

.debug
	.dw '.stabf ',0,0
	.dd LME1-_main
	.dw 0x0d,0x0a
.code
LME1:
.code
.debug
	.dw '.stabs "Uart_Init:F19",36,0,0,',0,0,offset _Uart_Init,seg _Uart_Init,0x0d,0x0a
.CODE
.public _Uart_Init
_Uart_Init:	.proc
.debug
	.dw '.stabn 0x44,0,38,',0,0
	.dd LM13-_Uart_Init
	.dw 0x0d,0x0a
.code
LM13:
	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.code
	PUSH BP to [SP]
	BP=SP+1

	R1=BP+3
.debug
	.dw '.stabn 0x44,0,39,',0,0
	.dd LM14-_Uart_Init
	.dw 0x0d,0x0a
.code
LM14:
	R2=1152	// QImode move
	[28680]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,40,',0,0
	.dd LM15-_Uart_Init
	.dw 0x0d,0x0a
.code
LM15:
	R2=1024	// QImode move
	[28679]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,41,',0,0
	.dd LM16-_Uart_Init
	.dw 0x0d,0x0a
.code
LM16:
	R2=1024	// QImode move
	[28677]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,43,',0,0
	.dd LM17-_Uart_Init
	.dw 0x0d,0x0a
.code
LM17:
	R2=0	// QImode move
	[28709]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,44,',0,0
	.dd LM18-_Uart_Init
	.dw 0x0d,0x0a
.code
LM18:
	R2=106	// QImode move
	[28708]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,47,',0,0
	.dd LM19-_Uart_Init
	.dw 0x0d,0x0a
.code
LM19:
	R2=0	// QImode move
	[28705]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,48,',0,0
	.dd LM20-_Uart_Init
	.dw 0x0d,0x0a
.code
LM20:
	R2=192	// QImode move
	[28706]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,50,',0,0
	.dd LM21-_Uart_Init
	.dw 0x0d,0x0a
.code
LM21:
.debug
	.dw '.stabn 0x44,0,50,',0,0
	.dd LM22-_Uart_Init
	.dw 0x0d,0x0a
.code
LM22:
L12:

	POP BP from [SP]
	RETF
	.endp	// end of Uart_Init

.debug
	.dw '.stabf ',0,0
	.dd LME2-_Uart_Init
	.dw 0x0d,0x0a
.code
LME2:
	.end
