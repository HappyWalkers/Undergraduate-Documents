// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: D:\unSPIDE\toolchain\cc1.exe C:\Users\dongchen\AppData\Local\Temp\ccW11ZbB.i -fkeep-inline-functions -quiet -dumpbase main.c -mglobal-var-iram -gstabs -Wall -o .\Debug/main.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "E:/π‚≈Ã◊ ¡œV1.2.0£®÷–ƒœ¥Û—ß£©/ µ—È÷∏µº È/ µ—Èœ‰ µ—È-Linux∆ΩÃ®∆™/Code/Cap5_61Basic/Ex01/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "E:/π/342≈/314◊/312¡/317V1.2.0£/250÷/320ƒ/317¥/363—/247£/251/ /265—/351÷/270µ/274 /351/ /265—/351œ/344 /265—/351-Linux∆/275Ã/250∆/252/Code/Cap5_61Basic/Ex01/main.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
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
	.dw '.stabn 0x44,0,9,',0,0
	.dd LM1-_main
	.dw 0x0d,0x0a
.code
LM1:
	// total=3, vars=3
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,3',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=3
	BP=SP+1

	R1=BP+6
.debug
	.dw '.stabn 0x44,0,10,',0,0
	.dd LM2-_main
	.dw 0x0d,0x0a
.code
LM2:
LBB2:
	R2=0	// QImode move
	[BP]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,13,',0,0
	.dd LM3-_main
	.dw 0x0d,0x0a
.code
LM3:
	R2=BP	// QImode move
	R3=BP+1
	R2=0	// QImode move
	R4=R3	// QImode move
	[R4]=R2	// QImode move
L3:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	CMP R2,100	// QImode compare
	NSJNA L6	//QImode LEU
	PC=L4	// jump
L6:
.debug
	.dw '.stabn 0x44,0,14,',0,0
	.dd LM4-_main
	.dw 0x0d,0x0a
.code
LM4:
	R3=BP	// QImode move
	R2=BP+1
	R4=[BP]	// QImode move
	R3=R4	// QImode move
	R4=R2	// QImode move
	R3 = R3 + [R4]	//addqi3
	[BP]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,13,',0,0
	.dd LM5-_main
	.dw 0x0d,0x0a
.code
LM5:
L5:
	R2=BP	// QImode move
	R3=BP+1
	R4=BP	// QImode move
	R2=BP+1
	R3=BP	// QImode move
	R3=BP+1
	[BP+2]=R3	// QImode move
	R4=[BP+2]	// QImode move
	R3=[R4]	// QImode move
	R4=R3+1
	R3=R2	// QImode move
	[R3]=R4	// QImode move
	PC=L3	// jump
L4:
.debug
	.dw '.stabn 0x44,0,15,',0,0
	.dd LM6-_main
	.dw 0x0d,0x0a
.code
LM6:
L7:
	PC=L9	// jump
	PC=L8	// jump
L9:
.debug
	.dw '.stabn 0x44,0,17,',0,0
	.dd LM7-_main
	.dw 0x0d,0x0a
.code
LM7:
	R2=1	// QImode move
	[28690]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,18,',0,0
	.dd LM8-_main
	.dw 0x0d,0x0a
.code
LM8:
	PC=L7	// jump
L8:
.debug
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM9-_main
	.dw 0x0d,0x0a
.code
LM9:
LBE2:
.debug
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM10-_main
	.dw 0x0d,0x0a
.code
LM10:
L2:

	SP+=3
	POP BP from [SP]
	RETF
	.endp	// end of main

.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB2-_main
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabs "Sum:1",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "i:11",128,0,0,1',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE2-_main
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabf ',0,0
	.dd LME1-_main
	.dw 0x0d,0x0a
.code
LME1:
	.end
