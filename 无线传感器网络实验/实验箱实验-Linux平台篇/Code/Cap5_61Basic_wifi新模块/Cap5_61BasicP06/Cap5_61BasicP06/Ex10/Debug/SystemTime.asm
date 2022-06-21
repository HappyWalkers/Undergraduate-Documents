// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: C:\GENERA~1\UNSPID~1.4\toolchain\cc1.exe C:\Users\XIANGX~1.LIU\AppData\Local\Temp\ccaow68g.i -fkeep-inline-functions -quiet -dumpbase SystemTime.c -mglobal-var-iram -gstabs -Wall -o .\Debug/SystemTime.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex10/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex10/wifi/SystemTime.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
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
	.dw '.stabs "WaitInfo:T20=s4next:21=*20,0,16;tick:5,16,32;\\",128,0,0,0',0x0d,0x0a
	.DW '.stabs "flag:1,48,16;;",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "WaitInfo:t22=20",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "size_t:t23=4",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "ssize_t:t24=1",128,0,0,0',0x0d,0x0a
.CODE
.iram
__sysTick:
	.dw 0
	.dw 0
.debug
	.dw '.stabs "_sysTick:S5",38,0,0,',0,0,offset __sysTick,seg __sysTick,0x0d,0x0a
.CODE
.iram
_waitQueue:
	.dw 0
.debug
	.dw '.stabs "waitQueue:S25=*22",38,0,0,',0,0,offset _waitQueue,seg _waitQueue,0x0d,0x0a
.CODE
.code
.debug
	.dw '.stabs "SystemTimeInit:F19",36,0,0,',0,0,offset _SystemTimeInit,seg _SystemTimeInit,0x0d,0x0a
.CODE
.public _SystemTimeInit
_SystemTimeInit:	.proc
.debug
	.dw '.stabn 0x44,0,13,',0,0
	.dd LM1-_SystemTimeInit
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
	.dw '.stabn 0x44,0,14,',0,0
	.dd LM2-_SystemTimeInit
	.dw 0x0d,0x0a
.code
LM2:
	//split R3=0
	R3=0	// QImode move
	R4=0	// QImode move
	//split [__sysTick]=R3
	[__sysTick]=R3	// QImode move
	[__sysTick+1]=R4	// QImode move
.debug
	.dw '.stabn 0x44,0,15,',0,0
	.dd LM3-_SystemTimeInit
	.dw 0x0d,0x0a
.code
LM3:
.debug
	.dw '.stabn 0x44,0,15,',0,0
	.dd LM4-_SystemTimeInit
	.dw 0x0d,0x0a
.code
LM4:
L2:

	POP BP from [SP]
	RETF
	.endp	// end of SystemTimeInit

.debug
	.dw '.stabf ',0,0
	.dd LME1-_SystemTimeInit
	.dw 0x0d,0x0a
.code
LME1:
.code
.debug
	.dw '.stabs "SystemTickISR:F19",36,0,0,',0,0,offset _SystemTickISR,seg _SystemTickISR,0x0d,0x0a
.CODE
.public _SystemTickISR
_SystemTickISR:	.proc
.debug
	.dw '.stabn 0x44,0,19,',0,0
	.dd LM5-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM5:
	// total=9, vars=9
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,9',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=9
	BP=SP+1

	R1=BP+12
.debug
	.dw '.stabn 0x44,0,20,',0,0
	.dd LM6-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM6:
LBB2:
	R3=[28688]	// QImode move
	R2=R3&16
	CMP R2,0	// QImode test
	NSJZ L4	//QImode EQ
.debug
	.dw '.stabn 0x44,0,22,',0,0
	.dd LM7-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM7:
	//split R3=[__sysTick]
	R3=[__sysTick]	// QImode move
	R4=[__sysTick+1]	// QImode move
	//split [BP+6]=R3
	[BP+6]=R3	// QImode move
	[BP+7]=R4	// QImode move
	//split R3=[BP+6]
	R3=[BP+6]	// QImode move
	R4=[BP+7]	// QImode move
	R3=R3+1	// HImode RD=RS+#IMM16
	R4=R4+0, Carry
	//split [BP+2]=R3
	[BP+2]=R3	// QImode move
	[BP+3]=R4	// QImode move
	//split R3=[BP+2]
	R3=[BP+2]	// QImode move
	R4=[BP+3]	// QImode move
	//split [__sysTick]=R3
	[__sysTick]=R3	// QImode move
	[__sysTick+1]=R4	// QImode move
.debug
	.dw '.stabn 0x44,0,24,',0,0
	.dd LM8-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM8:
	R2=[_waitQueue]	// QImode move
	CMP R2,0	// QImode test
	NSJZ L4	//QImode EQ
.debug
	.dw '.stabn 0x44,0,26,',0,0
	.dd LM9-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM9:
LBB3:
	R2=0	// QImode move
	[BP]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM10-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM10:
	R2=BP	// QImode move
	R3=BP+1
	R2=[_waitQueue]	// QImode move
	R4=R3	// QImode move
	[R4]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,28,',0,0
	.dd LM11-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM11:
L6:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	CMP R2,0	// QImode test
	NSJNZ L8	//QImode NE
	PC=L4	// jump
L8:
.debug
	.dw '.stabn 0x44,0,30,',0,0
	.dd LM12-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM12:
	R2=BP	// QImode move
	R3=BP+1
	R2=R3	// QImode move
	R4=[R2]	// QImode move
	R2=R4	// QImode move
	R3=R4+1
	[BP+6]=R3	// QImode move
	R4=[BP+6]	// QImode move
	//split R3=[R4]
	R3=[R4++]	// QImode move
	R4=[R4--]	// QImode move
	//split [BP+4]=R3
	[BP+4]=R3	// QImode move
	[BP+5]=R4	// QImode move
	//split R3=[__sysTick]
	R3=[__sysTick]	// QImode move
	R4=[__sysTick+1]	// QImode move
	//split [BP+6]=R3
	[BP+6]=R3	// QImode move
	[BP+7]=R4	// QImode move
	//split R3=[BP+4]
	R3=[BP+4]	// QImode move
	R4=[BP+5]	// QImode move
	CMP R4,[BP+7]	// CMP RD,[RS] HImode
	NSJNZ L9	// HImode NE
	CMP R3,[BP+6]
	NSJNZ  L9
.debug
	.dw '.stabn 0x44,0,32,',0,0
	.dd LM13-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM13:
	R2=BP	// QImode move
	R3=BP+1
	R2=R3	// QImode move
	R4=[R2]	// QImode move
	R2=R4	// QImode move
	R3=R4+3
	R2=1	// QImode move
	R4=R3	// QImode move
	[R4]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,34,',0,0
	.dd LM14-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM14:
	R2=[BP]	// QImode move
	CMP R2,0	// QImode test
	NSJNZ L10	//QImode NE
.debug
	.dw '.stabn 0x44,0,36,',0,0
	.dd LM15-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM15:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	R4=R2	// QImode move
	R3=[R4]	// QImode move
	[_waitQueue]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,37,',0,0
	.dd LM16-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM16:
	R3=BP	// QImode move
	R2=BP+1
	R3=BP	// QImode move
	R3=BP+1
	[BP+8]=R3	// QImode move
	R4=[BP+8]	// QImode move
	R3=[R4]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+8]=R4	// QImode move
	R3=[BP+8]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,38,',0,0
	.dd LM17-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM17:
	PC=L11	// jump
L10:
.debug
	.dw '.stabn 0x44,0,41,',0,0
	.dd LM18-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM18:
	R2=[BP]	// QImode move
	R3=BP	// QImode move
	R3=BP+1
	[BP+8]=R3	// QImode move
	R4=[BP+8]	// QImode move
	R3=[R4]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+8]=R4	// QImode move
	R3=[BP+8]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,42,',0,0
	.dd LM19-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM19:
	R3=BP	// QImode move
	R2=BP+1
	R3=BP	// QImode move
	R3=BP+1
	[BP+8]=R3	// QImode move
	R4=[BP+8]	// QImode move
	R3=[R4]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+8]=R4	// QImode move
	R3=[BP+8]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
L11:
.debug
	.dw '.stabn 0x44,0,44,',0,0
	.dd LM20-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM20:
	PC=L12	// jump
L9:
.debug
	.dw '.stabn 0x44,0,47,',0,0
	.dd LM21-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM21:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	[BP]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,48,',0,0
	.dd LM22-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM22:
	R3=BP	// QImode move
	R2=BP+1
	R3=BP	// QImode move
	R3=BP+1
	[BP+8]=R3	// QImode move
	R4=[BP+8]	// QImode move
	R3=[R4]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+8]=R4	// QImode move
	R3=[BP+8]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
L12:
.debug
	.dw '.stabn 0x44,0,50,',0,0
	.dd LM23-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM23:
	PC=L6	// jump
L7:
.debug
	.dw '.stabn 0x44,0,51,',0,0
	.dd LM24-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM24:
LBE3:
L5:
L4:
.debug
	.dw '.stabn 0x44,0,54,',0,0
	.dd LM25-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM25:
LBE2:
.debug
	.dw '.stabn 0x44,0,54,',0,0
	.dd LM26-_SystemTickISR
	.dw 0x0d,0x0a
.code
LM26:
L3:

	SP+=9
	POP BP from [SP]
	RETF
	.endp	// end of SystemTickISR

.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB2-_SystemTickISR
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB3-_SystemTickISR
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabs "prev:25",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "cur:25",128,0,0,1',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE3-_SystemTickISR
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE2-_SystemTickISR
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabf ',0,0
	.dd LME2-_SystemTickISR
	.dw 0x0d,0x0a
.code
LME2:
.code
.debug
	.dw '.stabs "SystemTick:F5",36,0,0,',0,0,offset _SystemTick,seg _SystemTick,0x0d,0x0a
.CODE
.public _SystemTick
_SystemTick:	.proc
.debug
	.dw '.stabn 0x44,0,57,',0,0
	.dd LM27-_SystemTick
	.dw 0x0d,0x0a
.code
LM27:
	// total=2, vars=2
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,2',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=2
	BP=SP+1

	R3=BP+5
.debug
	.dw '.stabn 0x44,0,58,',0,0
	.dd LM28-_SystemTick
	.dw 0x0d,0x0a
.code
LM28:
	//split R1=[__sysTick]
	R1=[__sysTick]	// QImode move
	R2=[__sysTick+1]	// QImode move
	//split [BP]=R1
	[BP]=R1	// QImode move
	[BP+1]=R2	// QImode move
	//split R1=[BP]
	R1=[BP]	// QImode move
	R2=[BP+1]	// QImode move
	PC=L19	// jump
.debug
	.dw '.stabn 0x44,0,59,',0,0
	.dd LM29-_SystemTick
	.dw 0x0d,0x0a
.code
LM29:
.debug
	.dw '.stabn 0x44,0,59,',0,0
	.dd LM30-_SystemTick
	.dw 0x0d,0x0a
.code
LM30:
L19:

	SP+=2
	POP BP from [SP]
	RETF
	.endp	// end of SystemTick

.debug
	.dw '.stabf ',0,0
	.dd LME3-_SystemTick
	.dw 0x0d,0x0a
.code
LME3:
.code
.debug
	.dw '.stabs "SystemTickReset:F19",36,0,0,',0,0,offset _SystemTickReset,seg _SystemTickReset,0x0d,0x0a
.CODE
.public _SystemTickReset
_SystemTickReset:	.proc
.debug
	.dw '.stabn 0x44,0,62,',0,0
	.dd LM31-_SystemTickReset
	.dw 0x0d,0x0a
.code
LM31:
	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.code
	PUSH BP to [SP]
	BP=SP+1

	R1=BP+3
.debug
	.dw '.stabn 0x44,0,63,',0,0
	.dd LM32-_SystemTickReset
	.dw 0x0d,0x0a
.code
LM32:
	//split R3=0
	R3=0	// QImode move
	R4=0	// QImode move
	//split [__sysTick]=R3
	[__sysTick]=R3	// QImode move
	[__sysTick+1]=R4	// QImode move
.debug
	.dw '.stabn 0x44,0,64,',0,0
	.dd LM33-_SystemTickReset
	.dw 0x0d,0x0a
.code
LM33:
.debug
	.dw '.stabn 0x44,0,64,',0,0
	.dd LM34-_SystemTickReset
	.dw 0x0d,0x0a
.code
LM34:
L20:

	POP BP from [SP]
	RETF
	.endp	// end of SystemTickReset

.debug
	.dw '.stabf ',0,0
	.dd LME4-_SystemTickReset
	.dw 0x0d,0x0a
.code
LME4:
.code
.debug
	.dw '.stabs "SystemTickWait:F19",36,0,0,',0,0,offset _SystemTickWait,seg _SystemTickWait,0x0d,0x0a
.CODE
.public _SystemTickWait
_SystemTickWait:	.proc
.debug
	.dw '.stabn 0x44,0,67,',0,0
	.dd LM35-_SystemTickWait
	.dw 0x0d,0x0a
.code
LM35:
	// total=15, vars=15
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,15',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=15
	BP=SP+1

	R1=BP+18
	[BP+11]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,68,',0,0
	.dd LM36-_SystemTickWait
	.dw 0x0d,0x0a
.code
LM36:
LBB4:
	R2=[BP+11]	// QImode move
	R1=[R2]
	R2=0
	//split [BP+2]=R1
	[BP+2]=R1	// QImode move
	[BP+3]=R2	// QImode move
	//split R1=[__sysTick]
	R1=[__sysTick]	// QImode move
	R2=[__sysTick+1]	// QImode move
	//split [BP+4]=R1
	[BP+4]=R1	// QImode move
	[BP+5]=R2	// QImode move
	R2=[BP+4]	// QImode move
	[BP+6]=R2	// QImode move
	R1=[BP+2]	// QImode move
	R1 = R1 + [BP+6]	//addqi3
	[BP+6]=R1	// QImode move
	R3=[BP+6]	// QImode move
	R2=1	// QImode move
	[BP+12]=R2	// QImode move
	R1=[BP+6]	// QImode move
	R2=[BP+4]	// QImode move
	CMP R1,R2	// QImode compare
	NSJB L22	//QImode LTU
	R1=0	// QImode move
	[BP+12]=R1	// QImode move
L22:
	R2=[BP+5]	// QImode move
	[BP+7]=R2	// QImode move
	R1=[BP+3]	// QImode move
	R1 = R1 + [BP+7]	//addqi3
	[BP+7]=R1	// QImode move
	R4=[BP+7]	// QImode move
	R2=[BP+7]	// QImode move
	[BP+8]=R2	// QImode move
	R1=[BP+8]	// QImode move
	R1 = R1 + [BP+12]	//addqi3
	[BP+8]=R1	// QImode move
	R4=[BP+8]	// QImode move
	//split [BP]=R3
	[BP]=R3	// QImode move
	[BP+1]=R4	// QImode move
.debug
	.dw '.stabn 0x44,0,70,',0,0
	.dd LM37-_SystemTickWait
	.dw 0x0d,0x0a
.code
LM37:
L23:
	//split R1=[__sysTick]
	R1=[__sysTick]	// QImode move
	R2=[__sysTick+1]	// QImode move
	//split [BP+13]=R1
	[BP+13]=R1	// QImode move
	[BP+14]=R2	// QImode move
	//split R1=[BP]
	R1=[BP]	// QImode move
	R2=[BP+1]	// QImode move
	//split [BP+9]=R1
	[BP+9]=R1	// QImode move
	[BP+10]=R2	// QImode move
	//split R1=[BP+13]
	R1=[BP+13]	// QImode move
	R2=[BP+14]	// QImode move
	CMP R2,[BP+10]	// CMP RD,[RS] HImode
	NSJNZ L25	// HImode NE
	CMP R1,[BP+9]
	NSJNZ  L25
	PC=L24	// jump
L25:
	PC=L23	// jump
L24:
.debug
	.dw '.stabn 0x44,0,71,',0,0
	.dd LM38-_SystemTickWait
	.dw 0x0d,0x0a
.code
LM38:
LBE4:
.debug
	.dw '.stabn 0x44,0,71,',0,0
	.dd LM39-_SystemTickWait
	.dw 0x0d,0x0a
.code
LM39:
L21:

	SP+=15
	POP BP from [SP]
	RETF
	.endp	// end of SystemTickWait

.debug
	.dw '.stabs "tick:p4",160,0,0,18',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB4-_SystemTickWait
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabs "_t:5",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE4-_SystemTickWait
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabf ',0,0
	.dd LME5-_SystemTickWait
	.dw 0x0d,0x0a
.code
LME5:
.code
.debug
	.dw '.stabs "SystemTickWaitAsync:F19",36,0,0,',0,0,offset _SystemTickWaitAsync,seg _SystemTickWaitAsync,0x0d,0x0a
.CODE
.public _SystemTickWaitAsync
_SystemTickWaitAsync:	.proc
.debug
	.dw '.stabn 0x44,0,75,',0,0
	.dd LM40-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM40:
	// total=12, vars=12
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,12',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=12
	BP=SP+1

	R1=BP+15
.debug
	.dw '.stabn 0x44,0,76,',0,0
	.dd LM41-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM41:
	R3=R1	// QImode move
	R2=[R3]	// QImode move
	R3=[_waitQueue]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,77,',0,0
	.dd LM42-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM42:
	R3=R1	// QImode move
	R2=[R3]	// QImode move
	[_waitQueue]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,78,',0,0
	.dd LM43-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM43:
	R4=R1	// QImode move
	R2=[R4]	// QImode move
	R3=R2	// QImode move
	R3=R2+1
	[BP+8]=R3	// QImode move
	R3=R1	// QImode move
	R4=R1+1
	[BP+9]=R4	// QImode move
	R4=[BP+9]	// QImode move
	R3=[R4]
	R4=0
	//split [BP]=R3
	[BP]=R3	// QImode move
	[BP+1]=R4	// QImode move
	//split R3=[__sysTick]
	R3=[__sysTick]	// QImode move
	R4=[__sysTick+1]	// QImode move
	//split [BP+2]=R3
	[BP+2]=R3	// QImode move
	[BP+3]=R4	// QImode move
	R4=[BP+2]	// QImode move
	[BP+4]=R4	// QImode move
	R2=[BP]	// QImode move
	R2 = R2 + [BP+4]	//addqi3
	[BP+4]=R2	// QImode move
	R3=[BP+4]	// QImode move
	[BP+10]=R3	// QImode move
	R4=1	// QImode move
	[BP+5]=R4	// QImode move
	R2=[BP+4]	// QImode move
	R3=[BP+2]	// QImode move
	CMP R2,R3	// QImode compare
	NSJB L30	//QImode LTU
	R4=0	// QImode move
	[BP+5]=R4	// QImode move
L30:
	R2=[BP+3]	// QImode move
	[BP+6]=R2	// QImode move
	R3=[BP+1]	// QImode move
	R3 = R3 + [BP+6]	//addqi3
	[BP+6]=R3	// QImode move
	R4=[BP+6]	// QImode move
	[BP+11]=R4	// QImode move
	R2=[BP+6]	// QImode move
	[BP+7]=R2	// QImode move
	R3=[BP+7]	// QImode move
	R3 = R3 + [BP+5]	//addqi3
	[BP+7]=R3	// QImode move
	R4=[BP+7]	// QImode move
	[BP+11]=R4	// QImode move
	//split R3=[BP+10]
	R3=[BP+10]	// QImode move
	R4=[BP+11]	// QImode move
	//split [BP+10]=R3
	[BP+10]=R3	// QImode move
	[BP+11]=R4	// QImode move
	//split R3=[BP+10]
	R3=[BP+10]	// QImode move
	R4=[BP+11]	// QImode move
	R2=[BP+8]	// QImode move
	//split [R2]=R3
	[R2++]=R3	// QImode move
	[R2--]=R4	// QImode move
.debug
	.dw '.stabn 0x44,0,79,',0,0
	.dd LM44-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM44:
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	R2=R3	// QImode move
	R3=R3+3
	R2=0	// QImode move
	R4=R3	// QImode move
	[R4]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,80,',0,0
	.dd LM45-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM45:
.debug
	.dw '.stabn 0x44,0,80,',0,0
	.dd LM46-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LM46:
L29:

	SP+=12
	POP BP from [SP]
	RETF
	.endp	// end of SystemTickWaitAsync

.debug
	.dw '.stabs "info:p25",160,0,0,15',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "tick:p4",160,0,0,16',0x0d,0x0a
.CODE
.debug
	.dw '.stabf ',0,0
	.dd LME6-_SystemTickWaitAsync
	.dw 0x0d,0x0a
.code
LME6:
.code
.debug
	.dw '.stabs "SystemTickWaitFinished:F1",36,0,0,',0,0,offset _SystemTickWaitFinished,seg _SystemTickWaitFinished,0x0d,0x0a
.CODE
.public _SystemTickWaitFinished
_SystemTickWaitFinished:	.proc
.debug
	.dw '.stabn 0x44,0,83,',0,0
	.dd LM47-_SystemTickWaitFinished
	.dw 0x0d,0x0a
.code
LM47:
	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.code
	PUSH BP to [SP]
	BP=SP+1

	R2=BP+3
.debug
	.dw '.stabn 0x44,0,84,',0,0
	.dd LM48-_SystemTickWaitFinished
	.dw 0x0d,0x0a
.code
LM48:
	R1=R2	// QImode move
	R3=[R1]	// QImode move
	R1=R3	// QImode move
	R3=R3+3
	R1=R3	// QImode move
	R4=[R1]	// QImode move
	R1=R4	// QImode move
	PC=L32	// jump
.debug
	.dw '.stabn 0x44,0,85,',0,0
	.dd LM49-_SystemTickWaitFinished
	.dw 0x0d,0x0a
.code
LM49:
.debug
	.dw '.stabn 0x44,0,85,',0,0
	.dd LM50-_SystemTickWaitFinished
	.dw 0x0d,0x0a
.code
LM50:
L32:

	POP BP from [SP]
	RETF
	.endp	// end of SystemTickWaitFinished

.debug
	.dw '.stabs "info:p25",160,0,0,3',0x0d,0x0a
.CODE
.debug
	.dw '.stabf ',0,0
	.dd LME7-_SystemTickWaitFinished
	.dw 0x0d,0x0a
.code
LME7:
.code
.debug
	.dw '.stabs "SystemTickClearWait:F19",36,0,0,',0,0,offset _SystemTickClearWait,seg _SystemTickClearWait,0x0d,0x0a
.CODE
.public _SystemTickClearWait
_SystemTickClearWait:	.proc
.debug
	.dw '.stabn 0x44,0,88,',0,0
	.dd LM51-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM51:
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
	.dw '.stabn 0x44,0,89,',0,0
	.dd LM52-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM52:
LBB5:
	R2=[_waitQueue]	// QImode move
	CMP R2,0	// QImode test
	NSJNZ L34	//QImode NE
.debug
	.dw '.stabn 0x44,0,90,',0,0
	.dd LM53-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM53:
	PC=L33	// jump
L34:
.debug
	.dw '.stabn 0x44,0,91,',0,0
	.dd LM54-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM54:
	R2=[_waitQueue]	// QImode move
	R3=R1	// QImode move
	CMP R2,[R3]	// QImode compare
	NSJNZ L35	//QImode NE
.debug
	.dw '.stabn 0x44,0,93,',0,0
	.dd LM55-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM55:
	R4=R1	// QImode move
	R2=[R4]	// QImode move
	R4=R2	// QImode move
	R3=[R4]	// QImode move
	[_waitQueue]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,94,',0,0
	.dd LM56-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM56:
	PC=L36	// jump
L35:
.debug
	.dw '.stabn 0x44,0,97,',0,0
	.dd LM57-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM57:
LBB6:
	R2=[_waitQueue]	// QImode move
	[BP]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,98,',0,0
	.dd LM58-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM58:
	R3=BP	// QImode move
	R2=BP+1
	R3=[_waitQueue]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+2]=R4	// QImode move
	R3=[BP+2]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,99,',0,0
	.dd LM59-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM59:
L37:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	CMP R2,0	// QImode test
	NSJNZ L39	//QImode NE
	PC=L36	// jump
L39:
.debug
	.dw '.stabn 0x44,0,101,',0,0
	.dd LM60-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM60:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	R3=R1	// QImode move
	CMP R2,[R3]	// QImode compare
	NSJNZ L40	//QImode NE
.debug
	.dw '.stabn 0x44,0,103,',0,0
	.dd LM61-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM61:
	R2=[BP]	// QImode move
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+2]=R4	// QImode move
	R3=[BP+2]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,104,',0,0
	.dd LM62-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM62:
	PC=L41	// jump
L40:
.debug
	.dw '.stabn 0x44,0,107,',0,0
	.dd LM63-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM63:
	R2=BP	// QImode move
	R3=BP+1
	R4=R3	// QImode move
	R2=[R4]	// QImode move
	[BP]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,108,',0,0
	.dd LM64-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM64:
	R3=BP	// QImode move
	R2=BP+1
	R3=BP	// QImode move
	R3=BP+1
	[BP+2]=R3	// QImode move
	R4=[BP+2]	// QImode move
	R3=[R4]	// QImode move
	R4=R3	// QImode move
	R4=[R4]	// QImode move
	[BP+2]=R4	// QImode move
	R3=[BP+2]	// QImode move
	R4=R2	// QImode move
	[R4]=R3	// QImode move
L41:
.debug
	.dw '.stabn 0x44,0,110,',0,0
	.dd LM65-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM65:
	PC=L37	// jump
L38:
.debug
	.dw '.stabn 0x44,0,111,',0,0
	.dd LM66-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM66:
LBE6:
L36:
.debug
	.dw '.stabn 0x44,0,112,',0,0
	.dd LM67-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM67:
LBE5:
.debug
	.dw '.stabn 0x44,0,112,',0,0
	.dd LM68-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LM68:
L33:

	SP+=3
	POP BP from [SP]
	RETF
	.endp	// end of SystemTickClearWait

.debug
	.dw '.stabs "info:p25",160,0,0,6',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB5-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB6-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabs "prev:25",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "cur:25",128,0,0,1',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE6-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE5-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabf ',0,0
	.dd LME8-_SystemTickClearWait
	.dw 0x0d,0x0a
.code
LME8:
	.end
