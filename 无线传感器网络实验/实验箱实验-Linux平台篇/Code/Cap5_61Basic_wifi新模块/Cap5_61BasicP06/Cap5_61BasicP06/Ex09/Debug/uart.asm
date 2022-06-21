// GCC for GeneralPlus u'nSP version 1.1.0.3
// Command: C:\GENERA~1\UNSPID~1.4\toolchain\cc1.exe C:\Users\XIANGX~1.LIU\AppData\Local\Temp\ccQ5sY9f.i -fkeep-inline-functions -quiet -dumpbase uart.c -mglobal-var-iram -gstabs -Wall -o .\Debug/uart.asm
	.external __sn_func_ptr_sec

// gcc2_compiled.:

.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex09/",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
.code
.debug
	.dw '.stabs "C:/Users/xiangxiang.liu/Desktop/Ex09/wifi/uart.c",0x64,0,3,',0,0,offset Ltext0,seg Ltext0,0x0d,0x0a
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
	.dw '.stabs "UART_INFO:G22=s1ProcessRxByte:23=*24=f19,0,16;;",32,0,0,',0,0,offset _UART_INFO,seg _UART_INFO,0x0d,0x0a
.CODE
.code
.debug
	.dw '.stabs "UART_Init:F19",36,0,0,',0,0,offset _UART_Init,seg _UART_Init,0x0d,0x0a
.CODE
.public _UART_Init
_UART_Init:	.proc
.debug
	.dw '.stabn 0x44,0,24,',0,0
	.dd LM1-_UART_Init
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
	.dw '.stabn 0x44,0,25,',0,0
	.dd LM2-_UART_Init
	.dw 0x0d,0x0a
.code
LM2:
	R3=R1	// QImode move
	R2=[R3]	// QImode move
	[_UART_INFO]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,26,',0,0
	.dd LM3-_UART_Init
	.dw 0x0d,0x0a
.code
LM3:
	R3=[28680]	// QImode move
	R2=R3&(-129)
	R3=R2|1024
	[28680]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,27,',0,0
	.dd LM4-_UART_Init
	.dw 0x0d,0x0a
.code
LM4:
	R2=[28678]	// QImode move
	R3=R2|1152
	[28678]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,28,',0,0
	.dd LM5-_UART_Init
	.dw 0x0d,0x0a
.code
LM5:
	R3=[28679]	// QImode move
	R2=R3&(-129)
	R3=R2|1024
	[28679]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,29,',0,0
	.dd LM6-_UART_Init
	.dw 0x0d,0x0a
.code
LM6:
	R2=0	// QImode move
	[28708]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,30,',0,0
	.dd LM7-_UART_Init
	.dw 0x0d,0x0a
.code
LM7:
	R2=5	// QImode move
	[28709]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,31,',0,0
	.dd LM8-_UART_Init
	.dw 0x0d,0x0a
.code
LM8:
	R2=128	// QImode move
	[28705]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,36,',0,0
	.dd LM9-_UART_Init
	.dw 0x0d,0x0a
.code
LM9:
	R2=192	// QImode move
	[28706]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,37,',0,0
	.dd LM10-_UART_Init
	.dw 0x0d,0x0a
.code
LM10:
.debug
	.dw '.stabn 0x44,0,37,',0,0
	.dd LM11-_UART_Init
	.dw 0x0d,0x0a
.code
LM11:
L2:

	POP BP from [SP]
	RETF
	.endp	// end of UART_Init

.debug
	.dw '.stabs "ProcessRxByte:p23",160,0,0,3',0x0d,0x0a
.CODE
.debug
	.dw '.stabf ',0,0
	.dd LME1-_UART_Init
	.dw 0x0d,0x0a
.code
LME1:
.text
_BaudRateTable:
	.dw -24576
	.dw 20480
	.dw 10240
	.dw 5120
	.dw 3000
	.dw 2560
	.dw 1280
	.dw 853
	.dw 640
	.dw 426
	.dw 320
	.dw 213
	.dw 107
.debug
	.dw '.stabs "BaudRateTable:S25=ar1;0;12;4",38,0,0,',0,0,offset _BaudRateTable,seg _BaudRateTable,0x0d,0x0a
.CODE
.code
.debug
	.dw '.stabs "UART_BaudSet:F19",36,0,0,',0,0,offset _UART_BaudSet,seg _UART_BaudSet,0x0d,0x0a
.CODE
.public _UART_BaudSet
_UART_BaudSet:	.proc
.debug
	.dw '.stabn 0x44,0,61,',0,0
	.dd LM12-_UART_BaudSet
	.dw 0x0d,0x0a
.code
LM12:
	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.code
	PUSH BP to [SP]
	BP=SP+1

	R1=BP+3
.debug
	.dw '.stabn 0x44,0,62,',0,0
	.dd LM13-_UART_BaudSet
	.dw 0x0d,0x0a
.code
LM13:
	R2=_BaudRateTable	// QImode move
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	R2 = R2 + R3	//addqi3
	R4=R2	// QImode move
	R3=[R4]	// QImode move
	[28708]=R3	// QImode move
.debug
	.dw '.stabn 0x44,0,63,',0,0
	.dd LM14-_UART_BaudSet
	.dw 0x0d,0x0a
.code
LM14:
	R2=_BaudRateTable	// QImode move
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	R2 = R2 + R3	//addqi3
	R4=R2	// QImode move
	R3=[R4]	// QImode move
	R2=R3 lsr 4
	R2=R2 lsr 4
	[28709]=R2	// QImode move
.debug
	.dw '.stabn 0x44,0,64,',0,0
	.dd LM15-_UART_BaudSet
	.dw 0x0d,0x0a
.code
LM15:
.debug
	.dw '.stabn 0x44,0,64,',0,0
	.dd LM16-_UART_BaudSet
	.dw 0x0d,0x0a
.code
LM16:
L3:

	POP BP from [SP]
	RETF
	.endp	// end of UART_BaudSet

.debug
	.dw '.stabs "nBaudRate:p21",160,0,0,3',0x0d,0x0a
.CODE
.debug
	.dw '.stabf ',0,0
	.dd LME2-_UART_BaudSet
	.dw 0x0d,0x0a
.code
LME2:
.code
.debug
	.dw '.stabs "UART_Send:F1",36,0,0,',0,0,offset _UART_Send,seg _UART_Send,0x0d,0x0a
.CODE
.public _UART_Send
_UART_Send:	.proc
.debug
	.dw '.stabn 0x44,0,74,',0,0
	.dd LM17-_UART_Send
	.dw 0x0d,0x0a
.code
LM17:
	// total=2, vars=2
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,2',0x0d, 0x0a
.code
	PUSH BP to [SP]
	SP-=2
	BP=SP+1

	R2=BP+5
.debug
	.dw '.stabn 0x44,0,81,',0,0
	.dd LM18-_UART_Send
	.dw 0x0d,0x0a
.code
LM18:
LBB2:
	R3=R2	// QImode move
	R1=[R3]	// QImode move
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,82,',0,0
	.dd LM19-_UART_Send
	.dw 0x0d,0x0a
.code
LM19:
L5:
	R3=R2	// QImode move
	R1=R2+1
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	[BP+1]=R3	// QImode move
	R3=R3+(-1)
	R4=R1	// QImode move
	[R4]=R3	// QImode move
	R1=[BP+1]	// QImode move
	CMP R1,0	// QImode test
	NSJG L7	//QImode GT
	PC=L6	// jump
L7:
.debug
	.dw '.stabn 0x44,0,84,',0,0
	.dd LM20-_UART_Send
	.dw 0x0d,0x0a
.code
LM20:
L8:
	R3=[28706]	// QImode move
	R1=R3&64
	CMP R1,0	// QImode test
	NSJZ L10	//QImode EQ
	PC=L9	// jump
L10:
	PC=L8	// jump
L9:
.debug
	.dw '.stabn 0x44,0,85,',0,0
	.dd LM21-_UART_Send
	.dw 0x0d,0x0a
.code
LM21:
	R1=[BP]	// QImode move
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	[28707]=R3	// QImode move
	R1=R1+1
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,86,',0,0
	.dd LM22-_UART_Send
	.dw 0x0d,0x0a
.code
LM22:
	PC=L5	// jump
L6:
.debug
	.dw '.stabn 0x44,0,88,',0,0
	.dd LM23-_UART_Send
	.dw 0x0d,0x0a
.code
LM23:
	R1=0	// QImode move
	PC=L4	// jump
.debug
	.dw '.stabn 0x44,0,89,',0,0
	.dd LM24-_UART_Send
	.dw 0x0d,0x0a
.code
LM24:
LBE2:
.debug
	.dw '.stabn 0x44,0,89,',0,0
	.dd LM25-_UART_Send
	.dw 0x0d,0x0a
.code
LM25:
L4:

	SP+=2
	POP BP from [SP]
	RETF
	.endp	// end of UART_Send

.debug
	.dw '.stabs "buf:p26=*19",160,0,0,5',0x0d,0x0a
.CODE
.debug
	.dw '.stabs "size:p1",160,0,0,6',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xc0,0,0,',0,0
	.dd LBB2-_UART_Send
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabs "p:27=*11",128,0,0,0',0x0d,0x0a
.CODE
.debug
	.dw '.stabn 0xe0,0,0,',0,0
	.dd LBE2-_UART_Send
	.dw 0x0d,0x0a
.code
.debug
	.dw '.stabf ',0,0
	.dd LME3-_UART_Send
	.dw 0x0d,0x0a
.code
LME3:
.code
.debug
	.dw '.stabs "UART_Send_String:F1",36,0,0,',0,0,offset _UART_Send_String,seg _UART_Send_String,0x0d,0x0a
.CODE
.public _UART_Send_String
_UART_Send_String:	.proc
.debug
	.dw '.stabn 0x44,0,98,',0,0
	.dd LM26-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM26:
	// total=0, vars=0
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,0',0x0d, 0x0a
.code
	PUSH BP to [SP]
	BP=SP+1

	R2=BP+3
.debug
	.dw '.stabn 0x44,0,105,',0,0
	.dd LM27-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM27:
L14:
	R3=R2	// QImode move
	R1=[R3]	// QImode move
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	CMP R3,0	// QImode test
	NSJNZ L16	//QImode NE
	PC=L15	// jump
L16:
.debug
	.dw '.stabn 0x44,0,107,',0,0
	.dd LM28-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM28:
L17:
	R3=[28706]	// QImode move
	R1=R3&64
	CMP R1,0	// QImode test
	NSJZ L19	//QImode EQ
	PC=L18	// jump
L19:
	PC=L17	// jump
L18:
.debug
	.dw '.stabn 0x44,0,108,',0,0
	.dd LM29-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM29:
	R3=R2	// QImode move
	R1=[R3]	// QImode move
	R4=R1	// QImode move
	R3=[R4]	// QImode move
	[28707]=R3	// QImode move
	R1=R1+1
	R3=R2	// QImode move
	[R3]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,109,',0,0
	.dd LM30-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM30:
	PC=L14	// jump
L15:
.debug
	.dw '.stabn 0x44,0,111,',0,0
	.dd LM31-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM31:
	R1=0	// QImode move
	PC=L13	// jump
.debug
	.dw '.stabn 0x44,0,112,',0,0
	.dd LM32-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM32:
.debug
	.dw '.stabn 0x44,0,112,',0,0
	.dd LM33-_UART_Send_String
	.dw 0x0d,0x0a
.code
LM33:
L13:

	POP BP from [SP]
	RETF
	.endp	// end of UART_Send_String

.debug
	.dw '.stabs "str:p28=*2",160,0,0,3',0x0d,0x0a
.CODE
.debug
	.dw '.stabf ',0,0
	.dd LME4-_UART_Send_String
	.dw 0x0d,0x0a
.code
LME4:
// ISR ATTRIBUTE FUNCTION, LOCATE in .text SECTION
.text
.debug
	.dw '.stabs "IRQ7:F19",36,0,0,',0,0,offset _IRQ7,seg _IRQ7,0x0d,0x0a
.TEXT
.public _IRQ7
_IRQ7:	.proc
.debug
	.dw '.stabn 0x44,0,122,',0,0
	.dd LM34-_IRQ7
	.dw 0x0d,0x0a
.text
LM34:
	// ISR ATTRIBUTE FUNCTION, PUSH R1,BP
	PUSH R1,BP to [SP]

	// total=2, vars=2
	// frame_pointer_needed: 1
.debug
	.dw '.stabn 0xa6,0,0,2',0x0d, 0x0a
.text
	SP-=2
	BP=SP+1

	R1=BP+5
	[BP]=R1	// QImode move
.debug
	.dw '.stabn 0x44,0,123,',0,0
	.dd LM35-_IRQ7
	.dw 0x0d,0x0a
.text
LM35:
	R2=[28706]	// QImode move
	R1=R2&128
	CMP R1,0	// QImode test
	NSJZ L23	//QImode EQ
.debug
	.dw '.stabn 0x44,0,126,',0,0
	.dd LM36-_IRQ7
	.dw 0x0d,0x0a
.text
LM36:
	R1=[28707]	// QImode move
	[SP--]=R1	// QImode move
	R1=[_UART_INFO]	// QImode move
	[BP+1]=R1	// QImode move
	R1=[BP+1]	// QImode move
	//call function by pointer without return value
	R1-=1
	R2=L25
	PUSH R2 to [SP]
	PUSH SR to [SP]
	POP SR, PC from [R1]
	//end of expand
L25:
	SP = SP + 1	//SP
L23:
.debug
	.dw '.stabn 0x44,0,138,',0,0
	.dd LM37-_IRQ7
	.dw 0x0d,0x0a
.text
LM37:
.debug
	.dw '.stabn 0x44,0,138,',0,0
	.dd LM38-_IRQ7
	.dw 0x0d,0x0a
.text
LM38:
L22:

	SP+=2
	// ISR ATTRIBUTE FUNCTION, POP R1,BP
	POP R1,BP from [SP]
	RETI
	.endp	// end of IRQ7

.debug
	.dw '.stabf ',0,0
	.dd LME5-_IRQ7
	.dw 0x0d,0x0a
.text
LME5:
.iram
.public _UART_INFO
_UART_INFO:
	.dw 0
	.end
