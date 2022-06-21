// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: C:\GENERA~1\UNSPID~1.4\toolchain\cc1.exe C:\Users\XIANGX~1.LIU\AppData\Local\Temp\cc9wSn4J.i -fkeep-inline-functions -quiet -dumpbase Sound.c -mglobal-var-iram -gstabs -Wall -o .\Debug/Sound.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex09/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex09/sound/Sound.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
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
	.dw '.stabs "PlaySnd:F19",36,0,0,',0,0,offset _PlaySnd,seg _PlaySnd,0x0d,0x0a
.CODE
.public _PlaySnd
_PlaySnd:	.proc
.debug
	.dw '.stabn 0x44,0,18,',0,0
	.dd LM1-_PlaySnd
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
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM2-_PlaySnd
	.dw 0x0d,0x0a
.code
LM2:
	R1=1	// QImode move
	[SP--]=R1	// QImode move
	CALL _SACM_S480_Initial	// call with return value
	SP = SP + 1	//SP
.debug
	.dw '.stabn 0x44,0,20,',0,0
	.dd LM3-_PlaySnd
	.dw 0x0d,0x0a
.code
LM3:
	R1=3	// QImode move
	[SP--]=R1	// QImode move
	R1=3	// QImode move
	[SP--]=R1	// QImode move
	R2=[BP]	// QImode move
	R1=[R2]	// QImode move
	[SP--]=R1	// QImode move
	CALL _SACM_S480_Play	// call without return value
	SP = SP + 3	//SP
.debug
	.dw '.stabn 0x44,0,21,',0,0
	.dd LM4-_PlaySnd
	.dw 0x0d,0x0a
.code
LM4:
L3:
	CALL _SACM_S480_Status	// call with return value
	R2=R1&1
	CMP R2,0	// QImode test
	NSJNZ L5	//QImode NE
	PC=L4	// jump
L5:
.debug
	.dw '.stabn 0x44,0,23,',0,0
	.dd LM5-_PlaySnd
	.dw 0x0d,0x0a
.code
LM5:
	CALL _SACM_S480_ServiceLoop	// call without return value
.debug
	.dw '.stabn 0x44,0,24,',0,0
	.dd LM6-_PlaySnd
	.dw 0x0d,0x0a
.code
LM6:
	R1=1	// QImode move
	[28690]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,25,',0,0
	.dd LM7-_PlaySnd
	.dw 0x0d,0x0a
.code
LM7:
	PC=L3	// jump
L4:
.debug
	.dw '.stabn 0x44,0,26,',0,0
	.dd LM8-_PlaySnd
	.dw 0x0d,0x0a
.code
LM8:
	CALL _SACM_S480_Stop	// call without return value
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM9-_PlaySnd
	.dw 0x0d,0x0a
.code
LM9:
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM10-_PlaySnd
	.dw 0x0d,0x0a
.code
LM10:
L2:

	SP+=1
	POP BP from [SP]
	RETF
	.endp	// end of PlaySnd

.debug
	.dw '.stabs "SndIndex:p1",160,0,0,4',0x0d,0x0a
.CODE
.debug
	.dw '.stabf ',0,0
	.dd LME1-_PlaySnd
	.dw 0x0d,0x0a
.code
LME1:
.external _SACM_S480_Stop
.external _SACM_S480_ServiceLoop
.external _SACM_S480_Status
.external _SACM_S480_Play
.external _SACM_S480_Initial
	.end
