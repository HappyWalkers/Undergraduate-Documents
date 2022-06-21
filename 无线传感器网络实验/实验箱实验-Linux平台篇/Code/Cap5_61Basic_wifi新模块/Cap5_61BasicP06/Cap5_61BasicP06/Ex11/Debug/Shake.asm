// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: C:\GENERA~1\UNSPID~1.4\toolchain\cc1.exe C:\Users\XIANGX~1.LIU\AppData\Local\Temp\cc4Dlq1b.i -fkeep-inline-functions -quiet -dumpbase Shake.c -mglobal-var-iram -gstabs -Wall -o .\Debug/Shake.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex11/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex11/Shake/Shake.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
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
	.dw '.stabs "ShakeInit:F19",36,0,0,',0,0,offset _ShakeInit,seg _ShakeInit,0x0d,0x0a
.CODE
.public _ShakeInit
_ShakeInit:	.proc
.debug
	.dw '.stabn 0x44,0,17,',0,0
	.dd LM1-_ShakeInit
	.dw 0x0d,0x0a
.code
LM1:
	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.code
	PUSH BP to [SP]
	BP=SP+1

	R1=BP+3
.debug
	.dw '.stabn 0x44,0,18,',0,0
	.dd LM2-_ShakeInit
	.dw 0x0d,0x0a
.code
LM2:
	R2=[28674]	// QImode move
	R3=R2&(-2)
	[28674]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM3-_ShakeInit
	.dw 0x0d,0x0a
.code
LM3:
	R2=[28675]	// QImode move
	R3=R2&(-2)
	[28675]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,20,',0,0
	.dd LM4-_ShakeInit
	.dw 0x0d,0x0a
.code
LM4:
	R2=[28672]	// QImode move
	R3=R2|1
	[28672]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,21,',0,0
	.dd LM5-_ShakeInit
	.dw 0x0d,0x0a
.code
LM5:
.debug
	.dw '.stabn 0x44,0,21,',0,0
	.dd LM6-_ShakeInit
	.dw 0x0d,0x0a
.code
LM6:
L2:

	POP BP from [SP]
	RETF
	.endp	// end of ShakeInit

.debug
	.dw '.stabf ',0,0
	.dd LME1-_ShakeInit
	.dw 0x0d,0x0a
.code
LME1:
.code
.debug
	.dw '.stabs "ShakeRefresh:F11",36,0,0,',0,0,offset _ShakeRefresh,seg _ShakeRefresh,0x0d,0x0a
.CODE
.public _ShakeRefresh
_ShakeRefresh:	.proc
.debug
	.dw '.stabn 0x44,0,23,',0,0
	.dd LM7-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LM7:
	// total=1, vars=1
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,1',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=1
	BP=SP+1

	R2=BP+4
.debug
	.dw '.stabn 0x44,0,25,',0,0
	.dd LM8-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LM8:
LBB2:
	R1=0	// QImode move
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,26,',0,0
	.dd LM9-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LM9:
	R3=[28672]	// QImode move
	R1=R3&1
	CMP R1,0	// QImode test
	NSJZ L4	//QImode EQ
	R1=1	// QImode move
	PC=L5	// jump
L4:
	R1=0	// QImode move
L5:
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM10-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LM10:
	R3=[BP]	// QImode move
	R1=R3	// QImode move
	PC=L3	// jump
.debug
	.dw '.stabn 0x44,0,28,',0,0
	.dd LM11-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LM11:
LBE2:
.debug
	.dw '.stabn 0x44,0,28,',0,0
	.dd LM12-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LM12:
L3:

	SP+=1
	POP BP from [SP]
	RETF
	.endp	// end of ShakeRefresh

.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB2-_ShakeRefresh
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabs "SensorFlag:11",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE2-_ShakeRefresh
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabf ',0,0
	.dd LME2-_ShakeRefresh
	.dw 0x0d,0x0a
.code
LME2:
	.end
