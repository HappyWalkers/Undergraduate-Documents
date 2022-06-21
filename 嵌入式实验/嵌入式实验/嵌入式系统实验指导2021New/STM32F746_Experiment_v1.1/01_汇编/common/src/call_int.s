/* For the fault of GNU GCC for ARM compiler to compile the interrupt function as:
    void user_handle(void) __attribute__ ((interrupt ("IRQ"))); // NOT RECOMMEND
    void user_handle(void); // RECOMMEND
#------------------------------------------------------------------------------
#- Entry function:	void	irqEntry(void)
#- Extern function:	void	isrHandle(void)
#------------------------------------------------------------------------------
#		.INCLUDE	"include.x"
*/
		.macro IRQHandle isrHandle:
		stmdb	sp!, {r0-r11, ip, lr}	/* save r0-r11, ip, lr */
		ldr		r0, =\isrHandle
		mov		lr, pc
		bx		r0						/* jump to user_handle(void) */
		ldmia	sp!, {r0-r11, ip, lr}	/* restore r0, ip, lr */
		subs	pc, r14, #4				/* return from interrupt */
		.endm

/* Examples showed as following:
@ void TSInt (void); ---> The interrupt handle function write as C program, it is user application func.
@ isrEINT2           ---> It is the interrupt vactor entry function to jump here, call by INTERRUPT  VECTOR TABLE.
@ TSP_INT            ---> modify Project ->Settings >Assembler >General category >Predefines: set as
								TSP_INT=1 
						  OR '#define TSP_INT' or '.EQU TSP_INT' in source file (except this file).
       .extern TSInt
       .global isrEINT2	
isrEINT2:
.ifdef TSP_INT
       IRQHandle TSInt
.endif
*/
@--------------------------------------------
       .extern int0_int
       .global isrEINT0
isrEINT0: 
.ifdef BUT1_INT
       IRQHandle int0_int
.endif

       .extern keyboard_int
       .global isrEINT1
isrEINT1: 
.ifdef KEY_INT
       IRQHandle keyboard_int
.endif
       .extern spi0_int
       .global isrSPI0
isrSPI0: 
.ifdef SPI0_INT
       IRQHandle spi0_int
.endif
       .extern spi1_int
       .global isrSPI1
isrSPI1: 
.ifdef SPI1_INT
       IRQHandle spi1_int
.endif
       .extern tsp_int
       .global isrADC
isrADC:
.ifdef TSP_INT
       IRQHandle tsp_int
.endif

       .extern int11_int
       .global isrEINT11_19
isrEINT11_19: 
.ifdef BUT2_INT
       IRQHandle int11_int
.endif

       .extern timer0_int
       .global isrTIMER0
isrTIMER0: 
.ifdef T0_INT
       IRQHandle timer0_int
.endif

       .extern timer1_int
       .global isrTIMER1
isrTIMER1: 
.ifdef T1_INT
       IRQHandle timer1_int
.endif

       .extern rtc_int
       .global isrRTC
isrRTC:
.ifdef RTC_INT
       IRQHandle rtc_int
.endif

       .extern BDMA0_Done
       .global isrBDMA0
isrBDMA0:
.ifdef IIS_INT
       IRQHandle BDMA0_Done
.endif

@-------------------------------------------- if no isr, return directly
		subs	pc, r14, #4				/* return from interrupt */
