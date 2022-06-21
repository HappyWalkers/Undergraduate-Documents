#=======================================================================================================================
# File Name : 2410init.s
# Author	: embest
# Descript	: S3C2410x system start up codes
#			  Configure memory, ISR ,stacks
#			  Initialize C-variables
# History	:
#			(1) R.X.Huang, Programming modify, March 12, 2005
#=======================================================================================================================
	.include "option.inc"
	.include "memcfg.inc"
	.include "2410addr.inc"

/*------------------------------------------------------------------------------------------*/
/*	 								constant define						 				    */
/*------------------------------------------------------------------------------------------*/
.equ 	USERMODE,	0x10
.equ 	FIQMODE,	0x11
.equ 	IRQMODE,	0x12
.equ 	SVCMODE,	0x13
.equ 	ABORTMODE,	0x17
.equ 	UNDEFMODE,	0x1b
.equ 	MODEMASK,	0x1f
.equ 	NOINT,		0xc0
.equ    CPSR_IRQ_EN,	0x80		/*  */
.equ    CPSR_IRQ_MASK,	0x40		/* disable Interrupt Mode (IRQ) */
.equ    CPSR_FIQ_MASK,	0x80		/* disable Fast Interrupt Mode (FIQ) */

.macro HANDLER HandleLabel
    sub	    sp,sp,#4				/* decrement sp(to store jump address) */							
    stmfd   sp!,{r0}				/* PUSH the work register to stack(lr does't push because it return to original address) */
    ldr	    r0,=\HandleLabel		/* load the address of HandleXXX to r0 */
    ldr	    r0,[r0]					/* load the contents(service routine start address) of HandleXXX */
    str	    r0,[sp,#4]				/* store the contents(ISR) of HandleXXX to stack */
    ldmfd   sp!,{r0,pc}				/* POP the work register and pc(jump to ISR) */
.endm
    
.macro LCD_DOFF OPT
	ldr	r1, =GPCCON
	ldr	r2, =0xaaaa55aa
	str	r2, [r1]
	ldr	r2, =0xffff
	str	r2, [r1, #8] @ rGPCUP
	ldr	r2, =\OPT
	str	r2, [r1, #4] @ rGPCDAT
.endm

	.extern			Image_RO_Base
	.extern			Image_RO_Limit	/* End of ROM code (=start of ROM data) */
	.extern			Image_RW_Base	/* Base of RAM to initialise */           
	.extern			Image_ZI_Base	/* Base and limit of area */              
	.extern			Image_ZI_Limit	/* to zero initialise */       
	.extern			Main			/* The main entry of mon program */

#=============================================================================================
# reset entry point  
#=============================================================================================
    .text
ENTRY:
# 1)The code, which converts to Big-endian, should be in little endian code.
# 2)The following little endian code will be compiled in Big-Endian mode. 
#   The code byte order should be changed as the memory bus width.
# 3)The pseudo instruction,.long can't be used here because the linker generates error.
.ifeq ENDIAN_CHANGE-1
.ifeq ENTRY_BUS_WIDTH-32
	b	ChangeBigEndian			@ .long 0xea000007 
.elseif ENTRY_BUS_WIDTH-16
	andeq	r14,r7,r0,lsl #20	@ .long 0x0007ea00
.elseif ENTRY_BUS_WIDTH-8
	streq	r0,[r0,-r10,ror #1]	@ .long 0x070000ea
.endif
.else
	b	ResetHandler 
.endif
	
	b	HandlerUndef		@ handler for Undefined mode
	b	HandlerSWI			@ handler for SWI interrupt
	b	HandlerPabort		@ handler for PAbort
	b	HandlerDabort		@ handler for DAbort
	b	.					@ reserved
	b	HandlerIRQ			@ handler for IRQ interrupt 
	b	HandlerFIQ			@ handler for FIQ interrupt
#- 0x20
	b	EnterPWDN

#=============================================================================================
# ChangeBigEndian 
# Should be stored in memory address at 0x24 
#=============================================================================================
ChangeBigEndian:
#- 0x24
.ifeq ENTRY_BUS_WIDTH-32
	.long	0xee110f10	@ 0xee110f10 => mrc p15,0,r0,c1,c0,0
	.long	0xe3800080	@ 0xe3800080 => orr r0,r0,#0x80#  //Big-endian
	.long	0xee010f10	@ 0xee010f10 => mcr p15,0,r0,c1,c0,0
.endif
.ifeq ENTRY_BUS_WIDTH-16
	.long 0x0f10ee11
	.long 0x0080e380	
	.long 0x0f10ee01	
.endif
.ifeq ENTRY_BUS_WIDTH-8
	.long 0x100f11ee	
	.long 0x800080e3	
	.long 0x100f01ee	
.endif
	.long 0xffffffff		@ swinv 0xffffff is similar with NOP and run well in both endian mode. 
	.long 0xffffffff
	.long 0xffffffff
	.long 0xffffffff
	.long 0xffffffff
	b ResetHandler
	
#=============================================================================================
# EnterPWDN  
# Function for entering power down mode
# 1. SDRAM should be in self-refresh mode.
# 2. All interrupt should be maksked for SDRAM/DRAM self-refresh.
# 3. LCD controller should be disabled for SDRAM/DRAM self-refresh.
# 4. The I-cache may have to be turned on. 
# 5. The location of the following code may have not to be changed.
#=============================================================================================
# void EnterPWDN(int CLKCON); 
EnterPWDN:			
	mov r2,r0			@ r2=rCLKCON
	tst r0,#0x8			@ POWER_OFF mode?
	bne ENTER_POWER_OFF

ENTER_STOP:	
	ldr r0,=REFRESH		
	ldr r3,[r0]			@ r3=rREFRESH	
	mov r1, r3
	orr r1, r1, #BIT_SELFREFRESH
	str r1, [r0]		@ Enable SDRAM self-refresh
	mov r1,#16			@ wait until self-refresh is issued. may not be needed.
B0:
	subs r1,r1,#1
	bne B0
	ldr r0,=CLKCON		@ enter STOP mode.
	str r2,[r0] 
	mov r1,#32
F0:	
	subs r1,r1,#1		@ 1) wait until the STOP mode is in effect.
	bne B0				@ 2) Or wait here until the CPU&Peripherals will be turned-off
	
# Entering POWER_OFF mode, only the reset by wake-up is available.
	ldr r0,=REFRESH		@ exit from SDRAM self refresh mode.
	str r3,[r0]	
	MOV_PC_LR

#=============================================================================================
# ENTER_POWER_OFF  
#=============================================================================================
ENTER_POWER_OFF:	
# NOTE.
# 1) rGSTATUS3 should have the return address after wake-up from POWER_OFF mode.	
	ldr r0,=REFRESH		
	ldr r1,[r0]			@ r1=rREFRESH	
	orr r1, r1, #BIT_SELFREFRESH
	str r1, [r0]		@ Enable SDRAM self-refresh
	
	mov r1,#16	   		@ Wait until self-refresh is issued,which may not be needed.
B1:	subs r1,r1,#1
	bne B1
	ldr r1,=MISCCR
	ldr	r0,[r1]
	orr	r0,r0,#(7<<17)  @ Make sure that SCLK0:SCLK->0, SCLK1:SCLK->0, SCKE=L during boot-up 
	str	r0,[r1]
	ldr r0,=CLKCON
	str r2,[r0]
	b .					@ CPU will die here.
	
#=============================================================================================
# WAKEUP_POWER_OFF  
#=============================================================================================
WAKEUP_POWER_OFF:
# Release SCLKn after wake-up from the POWER_OFF mode.
	ldr r1,=MISCCR
	ldr	r0,[r1]
	bic	r0,r0,#(7<<17)  @ SCLK0:0->SCLK, SCLK1:0->SCLK, SCKE:L->H
	str	r0,[r1]
	
# Set memory control registers
    ldr	r0,=SMRDATA
	ldr	r1,=BWSCON		@ BWSCON Address
	add	r2, r0, #52		@ End address of SMRDATA
B2:       
	ldr	r3, [r0], #4    
	str	r3, [r1], #4    
	cmp	r2, r0		
	bne	B2
	mov r1,#256
B3:	
	subs r1,r1,#1		@ 1) wait until the SelfRefresh is released.
	bne B3	

	ldr r1,=GSTATUS3 	@ GSTATUS3 has the start address just after POWER_OFF wake-up
	ldr r0,[r1]
	mov pc,r0

#=============================================================================================
# ARM core's exception entry  
#=============================================================================================
	.align   
HandlerFIQ:      HANDLER HandleFIQ
HandlerIRQ:      HANDLER HandleIRQ
HandlerUndef:    HANDLER HandleUndef
HandlerSWI:      HANDLER HandleSWI
HandlerDabort:   HANDLER HandleDabort
HandlerPabort:   HANDLER HandlePabort
	
	.global IsrIRQ
IsrIRQ:  
	sub	sp,sp,#4       @ reserved for PC
	stmfd	sp!,{r8-r9}   
	
	ldr	r9,=INTOFFSET
	ldr	r9,[r9]
	ldr	r8,=HandleEINT0
	add	r8,r8,r9,lsl #2
	ldr	r8,[r8]
	str	r8,[sp,#8]
	ldmfd	sp!,{r8-r9,pc}

#=============================================================================================
# ResetHandler  
#=============================================================================================
ResetHandler:
	LCD_DOFF 0
	ldr	r1, =GPFCON
	ldr	r2,=0x55aa
	str	r2, [r1]
	mov	r2, #0xff
	str	r2, [r1, #8]

	ldr	r1, =GPFDAT
	mov	r2, #0xf		@ All LED on
	str	r2, [r1]

	ldr	r0,=WTCON       @ watch dog disable 
	ldr	r1,=0x0         
	str	r1,[r0]
	
	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff  @ all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7ff		@ all sub interrupt disable, 2002/04/10
	str	r1,[r0]

# To reduce PLL lock time, adjust the LOCKTIME register. 
	ldr	r0,=LOCKTIME
	ldr	r1,=0xffffff
	str	r1,[r0]
    
.ifdef PLL_ON_START
# Configure MPLL
	ldr	r0,=MPLLCON          
	ldr	r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV)  @ Fin=12MHz,Fout=50MHz
	str	r1,[r0]
.endif
# Check if the boot is caused by the wake-up from POWER_OFF mode.
	ldr	r1,=GSTATUS2
	ldr	r0,[r1]
	tst	r0,#0x2
# In case of the wake-up from POWER_OFF mode, go to POWER_OFF_WAKEUP handler. 
	bne	WAKEUP_POWER_OFF

#=============================================================================================
# StartPointAfterPowerOffWakeUp  
#=============================================================================================
	.global StartPointAfterPowerOffWakeUp
StartPointAfterPowerOffWakeUp:
# Set memory control registers
#.equ	ROM_BASE,	0x0		@ image store address (in Flash)
    ldr	    r0,=SMRDATA
.ifdef	EXEC_FROM_RAM
    ldr		lr,=Image_RO_Base
	sub		r0,r0,lr
	ldr		lr,=ROM_BASE
	add		r0,r0,lr
.endif
	ldmia   r0,{r1-r13}
	ldr	    r0,=BWSCON  	@ BWSCON Address 
	stmia   r0,{r1-r13}

.ifdef	EXEC_FROM_RAM
	ldr r0,=ROM_BASE
	ldr r1,=Image_RO_Base
	ldr r3,=Image_ZI_Limit
LoopRw:
    cmp  	r1, r3
	ldrcc   r2, [r0], #4
	strcc  	r2, [r1], #4
	bcc   	LoopRw
		
	ldr 	pc,	=Jump
Jump:
	nop
	nop
	nop
.endif

/*
    ldr	    r0,=SMRDATA
    ldr		lr,=Image_RO_Base
	sub		r0,r0,lr
	ldr		lr,=ROM_BASE
	add		r0,r0,lr
	ldmia   r0,{r1-r13}
	ldr	    r0,=BWSCON  	@ BWSCON Address
	stmia   r0,{r1-r13}

	ldr	r0, STR_OK
	ldr	r1, SerBase
	bl	PrintWord

	ldr	sp,=SVCStack
	bl copy_myself
	@ jump to ram
	ldr	r1, =on_the_ram
	add	pc, r1, #0
	nop
	nop
1:	b	1b		@ infinite loop

on_the_ram:
*/
# Initialize stacks
#	bl	InitStacks			@ if SVCstack is initialized before

#=============================================================================================
# InitStacks, initializing stacks of different mode
# Don't use DRAM operation, such as stmfd,ldmfd......
# 'msr cpsr,r1' can be used instead of 'msr cpsr_cxsf,r1'
#=============================================================================================
InitStacks: 
	mrs	r0,cpsr
	bic	r0,r0,#MODEMASK
	orr	r1,r0,#UNDEFMODE|NOINT
	msr	cpsr_cxsf,r1		@ UndefMode
	ldr	sp,=UndefStack
	
	orr	r1,r0,#ABORTMODE|NOINT
	msr	cpsr_cxsf,r1		@ AbortMode
	ldr	sp,=AbortStack

	orr	r1,r0,#IRQMODE|NOINT
	msr	cpsr_cxsf,r1		@ IRQMode
	ldr	sp,=IRQStack
    
	orr	r1,r0,#FIQMODE|NOINT
	msr	cpsr_cxsf,r1		@ FIQMode
	ldr	sp,=FIQStack

	bic	r0,r0,#MODEMASK|NOINT
	orr	r1,r0,#SVCMODE
	msr	cpsr_cxsf,r1		@ SVCMode
	ldr	sp,=SVCStack
	
# USER mode has not be initialized.
#	mov	pc,lr 				@ The LR register won't be valid if the current mode is not SVC mode.

#  Setup IRQ handler
	ldr	r0,=HandleIRQ       @ This routine is needed
	ldr	r1,=IsrIRQ          @ if there isn't 'subs pc,lr,#4' at 0x18, 0x1c
	str	r1,[r0]

# Copy and paste RW data/zero initialized data
	ldr	r0, = Image_RO_Limit@ Get pointer to ROM data
	ldr	r1, = Image_RW_Base	@ and RAM copy
	ldr	r3, = Image_ZI_Base   
	
# Zero init base => top of initialised data
	cmp	r0, r1				@ Check that they are different
	beq	F2
F1:       
	cmp	r1, r3				@ Copy init data
	ldrcc	r2, [r0], #4    @ --> LDRCC r2, [r0] + ADD r0, r0, #4         
	strcc	r2, [r1], #4    @ --> STRCC r2, [r1] + ADD r1, r1, #4
	bcc	F1
F2:       
	ldr	r1, = Image_ZI_Limit@ Top of zero init segment
	mov	r2, #0
B5:      
	cmp	r3, r1				@ Zero init
	strcc	r2, [r3], #4
	bcc	B5

	MRS	r0, CPSR
	BIC	r0, r0, #0x80		@ IRQ enable
	MSR	CPSR_cxsf, r0
	
/* jump to Main() */	
.ifdef THUMBCODE		@ for start-up code for Thumb mode
	orr	lr,pc,#1
	bx	lr
	.thumb
	bl	Main			@ Don't use main() because...
.else
	.arm
	bl	Main			@ Don't use main() because...
.endif
	b	.                       

/*
#ifdef CONFIG_S3C2410_NAND_BOOT
@
@ copy_myself: copy to ram
@
copy_myself:
	mov	r10, lr

	@ reset NAND
	ldr	r1, =NFCONF
	ldr	r2, =0xf830		@ initial value
	str	r2, [r1, #0x00]
	ldr	r2, [r1, #0x00]
	bic	r2, r2, #0x800		@ enable chip
	str	r2, [r1, #0x00]
	mov	r2, #0xff		@ RESET command
	strb	r2, [r1, #0x04]
	mov	r3, #0			@ wait 
1:	add	r3, r3, #0x1
	cmp	r3, #0xa
	blt	1b
2:	ldr	r2, [r1, #0x10]	@ wait ready
	tst	r2, #0x1
	beq	2b
	ldr	r2, [r1, #0x00]
	orr	r2, r2, #0x800		@ disable chip
	str	r2, [r1, #0x00]

	@ get read to call C functions (for nand_read())
	ldr	sp, =0x32000000 @DW_STACK_START	@ setup stack pointer
	mov	fp, #0			@ no previous frame, so fp=0

	@ copy to RAM
	ldr	r0, =0x30000000
	mov     r1, #0x0
	mov	r2, #0x20000
	bl	nand_read_ll

	tst	r0, #0x0
	beq	ok_nand_read
#ifdef CONFIG_DEBUG
bad_nand_read: 
	ldr	r0, STR_FAIL
	ldr	r1, SerBase
	bl	PrintWord
1:	b	1b		@ infinite loop 
#endif
	
ok_nand_read:
#ifdef CONFIG_DEBUG
	ldr	r0, STR_OK
	ldr	r1, SerBase
	bl	PrintWord
#endif

	@ verify
	mov	r0, #0
	ldr	r1, =0x33f00000
	mov	r2, #0x400	@ 4 bytes * 1024 = 4K-bytes
go_next:
	ldr	r3, [r0], #4
	ldr	r4, [r1], #4
	teq	r3, r4
	bne	notmatch
	subs	r2, r2, #4
	beq	done_nand_read	
	bne	go_next
notmatch:
#ifdef CONFIG_DEBUG
	sub	r0, r0, #4
	ldr	r1, SerBase
	bl	PrintHexWord
	ldr	r0, STR_FAIL
	ldr	r1, SerBase
	bl	PrintWord
#endif
1:	b	1b
done_nand_read:

#ifdef CONFIG_DEBUG
	ldr	r0, STR_OK
	ldr	r1, SerBase
	bl	PrintWord
#endif

	mov	pc, r10


@ clear memory
@ r0: start address
@ r1: length
mem_clear:
	mov	r2, #0
	mov	r3, r2
	mov	r4, r2
	mov	r5, r2
	mov	r6, r2
	mov	r7, r2
	mov	r8, r2
	mov	r9, r2

clear_loop:
	stmia	r0!, {r2-r9}
	subs	r1, r1, #(8 * 4)
	bne	clear_loop

	mov	pc, lr

#endif @ CONFIG_S3C2410_NAND_BOOT


#ifdef CONFIG_DEBUG
@ PrintHexNibble : prints the least-significant nibble in R0 as a
@ hex digit
@   r0 contains nibble to write as Hex
@   r1 contains base of serial port
@   writes ro with XXX, modifies r0,r1,r2
@   TODO : write ro with XXX reg to error handling
@   Falls through to PrintChar
PrintHexNibble:
	adr	r2, HEX_TO_ASCII_TABLE
	and	r0, r0, #0xF
	ldr	r0, [r2, r0]	@ convert to ascii
	b	PrintChar

@ PrintChar : prints the character in R0
@   r0 contains the character
@   r1 contains base of serial port
@   writes ro with XXX, modifies r0,r1,r2
@   TODO : write ro with XXX reg to error handling
PrintChar:
TXBusy:
	ldr	r2, [r1, #0x10]
	and	r2, r2, #4
	tst	r2, #4
	beq	TXBusy	
	str	r0, [r1, #0x20]
	mov	pc, lr

@ PrintWord : prints the 4 characters in R0
@   r0 contains the binary word
@   r1 contains the base of the serial port
@   writes ro with XXX, modifies r0,r1,r2
@   TODO : write ro with XXX reg to error handling
PrintWord:
	mov	r3, r0
	mov	r4, lr
	bl	PrintChar

	mov	r0, r3, LSR #8		@ shift word right 8 bits 
	bl	PrintChar

	mov	r0, r3, LSR #16		@ shift word right 16 bits 
	bl	PrintChar
	
	mov	r0, r3, LSR #24		@ shift word right 24 bits 
	bl	PrintChar

	mov	r0, #'\r'
	bl	PrintChar

	mov	r0, #'\n'
	bl	PrintChar

	mov	pc, r4

@ PrintHexWord : prints the 4 bytes in R0 as 8 hex ascii characters
@   followed by a newline
@   r0 contains the binary word
@   r1 contains the base of the serial port
@   writes ro with XXX, modifies r0,r1,r2
@   TODO : write ro with XXX reg to error handling
PrintHexWord:
	mov	r4, lr
	mov	r3, r0
	mov	r0, r3, LSR #28
	bl	PrintHexNibble
	mov	r0, r3, LSR #24
	bl	PrintHexNibble
	mov	r0, r3, LSR #20
	bl	PrintHexNibble
	mov	r0, r3, LSR #16
	bl	PrintHexNibble
	mov	r0, r3, LSR #12
	bl	PrintHexNibble
	mov	r0, r3, LSR #8
	bl	PrintHexNibble
	mov	r0, r3, LSR #4
	bl	PrintHexNibble
	mov	r0, r3
	bl	PrintHexNibble

	mov	r0, #'\r'
	bl	PrintChar

	mov	r0, #'\n'
	bl	PrintChar

	mov	pc, r4
	.align	2
HEX_TO_ASCII_TABLE:
	.ascii	"0123456789ABCDEF"
STR_STACK:
	.ascii	"STKP"
STR_UNDEF:
	.ascii	"UNDF"
STR_SWI:
	.ascii	"SWI "
STR_PREFETCH_ABORT:
	.ascii	"PABT"
STR_DATA_ABORT:
	.ascii	"DABT"
STR_IRQ:
	.ascii	"IRQ "
STR_FIQ:
	.ascii	"FIQ"
STR_NOT_USED:
	.ascii	"NUSD"
	.align 2
STR_OK:
	.ascii	"OK  "
STR_FAIL:
	.ascii	"FAIL"
STR_CR:
	.ascii  "\r\n"
#endif

.align 4
SerBase:
#if defined(CONFIG_SERIAL_UART0)
	.long ULCON0
#elif defined(CONFIG_SERIAL_UART1)
	.long ULCON1
#elif defined(CONFIG_SERIAL_UART2)
	.long ULCON2
#else
#error not defined base address of serial
#endif
*/

#=============================================================================================
#SMRDATA
# Memory configuration should be optimized for best performance 
# The following parameter is not optimized.                     
# Memory access cycle parameter strategy
# 1) The memory settings is  safe parameters even at HCLK=75Mhz.
# 2) SDRAM refresh period is for HCLK=75Mhz. 
#=============================================================================================
	.ltorg
SMRDATA:
	.long (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
	.long ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))   @ GCS0
	.long ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))   @ GCS1 
	.long ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))   @ GCS2
	.long ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))   @ GCS3
	.long ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))   @ GCS4
	.long ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))   @ GCS5
	.long ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))    @ GCS6
	.long ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))    @ GCS7
	.long ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)    

	.long 0x32            @ SCLK power saving mode, BANKSIZE 128M/128M
   	.long 0x30            @ MRSR6 CL=3clk
   	.long 0x30            @ MRSR7
#	.long 0x20            @ MRSR6 CL=2clk
#	.long 0x20            @ MRSR7

#=======================================================================================================================
# ARM core's exception and user interrupt handler store address 
# The address may be different between the different assemble after link.
#=============================================================================================
	.align
.equ	HandleReset,	_ISR_STARTADDRESS
.equ	HandleUndef,	_ISR_STARTADDRESS+4
.equ	HandleSWI,		_ISR_STARTADDRESS+4*2
.equ	HandlePabort,	_ISR_STARTADDRESS+4*3
.equ	HandleDabort,	_ISR_STARTADDRESS+4*4
.equ	HandleReserved,	_ISR_STARTADDRESS+4*5
.equ	HandleIRQ,		_ISR_STARTADDRESS+4*6
.equ	HandleFIQ,		_ISR_STARTADDRESS+4*7

#Don't use the label 'IntVectorTable',
#The value of IntVectorTable is different with the address you think it may be.
#IntVectorTable
.equ	HandleEINT0,    _ISR_STARTADDRESS+4*8
.equ	HandleEINT1,	_ISR_STARTADDRESS+4*9
.equ	HandleEINT2, 	_ISR_STARTADDRESS+4*10
.equ	HandleEINT3,	_ISR_STARTADDRESS+4*11
.equ	HandleEINT4_7,	_ISR_STARTADDRESS+4*12
.equ	HandleEINT8_23,	_ISR_STARTADDRESS+4*13
.equ	HandleRSV6,		_ISR_STARTADDRESS+4*14
.equ	HandleBATFLT,	_ISR_STARTADDRESS+4*15
.equ	HandleTICK,		_ISR_STARTADDRESS+4*16
.equ	HandleWDT,		_ISR_STARTADDRESS+4*17
.equ	HandleTIMER0,	_ISR_STARTADDRESS+4*18
.equ	HandleTIMER1,	_ISR_STARTADDRESS+4*19
.equ	HandleTIMER2, 	_ISR_STARTADDRESS+4*20
.equ	HandleTIMER3, 	_ISR_STARTADDRESS+4*21
.equ	HandleTIMER4, 	_ISR_STARTADDRESS+4*22
.equ	HandleUART2, 	_ISR_STARTADDRESS+4*23
.equ	HandleLCD,		_ISR_STARTADDRESS+4*24
.equ	HandleDMA0,		_ISR_STARTADDRESS+4*25
.equ	HandleDMA1,		_ISR_STARTADDRESS+4*26
.equ	HandleDMA2,		_ISR_STARTADDRESS+4*27
.equ	HandleDMA3,		_ISR_STARTADDRESS+4*28
.equ	HandleMMC,		_ISR_STARTADDRESS+4*29
.equ	HandleSPI0,		_ISR_STARTADDRESS+4*30
.equ	HandleUART1,	_ISR_STARTADDRESS+4*31
.equ	HandleRSV24,	_ISR_STARTADDRESS+4*32
.equ	HandleUSBD,		_ISR_STARTADDRESS+4*33	
.equ	HandleUSBH,     _ISR_STARTADDRESS+4*34	
.equ	HandleIIC,		_ISR_STARTADDRESS+4*35  	
.equ	HandleUART,     _ISR_STARTADDRESS+4*36 	
.equ	HandleSPI1,     _ISR_STARTADDRESS+4*37 	
.equ	HandleRTC,		_ISR_STARTADDRESS+4*38
.equ	HandleADC,		_ISR_STARTADDRESS+4*39
.end
