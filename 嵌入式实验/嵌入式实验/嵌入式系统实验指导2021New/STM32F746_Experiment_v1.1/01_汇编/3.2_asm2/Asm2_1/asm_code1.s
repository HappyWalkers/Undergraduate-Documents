;#*********************************************************************************************
;# NAME:	ARMcode.s																		 *
;# Author: 	EWUHAN  R & D Center, st																			 *
;# Desc:	ARMcode examples																 *
;#          copy words from src to dst														 *
;# History:	shw.He 2005.02.22																 *
;#*********************************************************************************************

;/*------------------------------------------------------------------------------------------*/
;/*	 								code								 				    */
;/*------------------------------------------------------------------------------------------*/
		
		GLOBAL	Reset_Handler
		area start,code,readwrite
		entry
		code32
num		EQU		20									         ;/*  Set number of words to be copied */

Reset_Handler
		ldr		r0, =src						;/*  r0 = pointer to source block */
		ldr		r1, =dst						;/*  r1 = pointer to destination block */
		mov		r2, #num						;/*  r2 = number of words to copy */

		ldr		sp, =0x30200000						;/*  set up stack pointer (r13) */
blockcopy       
		movs	r3,r2, LSR #3					;/*  number of eight word multiples */
		beq		copywords						;/*  less than eight words to move ? */

		stmfd	sp!, {r4-r11}					;/*  save some working registers */
octcopy
		ldmia	r0!, {r4-r11}					;/*  load 8 words from the source */
		stmia	r1!, {r4-r11}					;/*  and put them at the destination */
		subs	r3, r3, #1						;/*  decrement the counter */
		bne		octcopy							;/*  ... copy more */

		ldmfd	sp!, {r4-r11}					;/*  don't need these now - restore originals */

copywords
		ands	r2, r2, #7						;/*  number of odd words to copy */
		beq		stop							;/*  No words left to copy ? */
wordcopy
		ldr		r3, [r0], #4					;/*  a word from the source */
		str		r3, [r1], #4					;/*  store a word to the destination */
		subs	r2, r2, #1						;/*  decrement the counter */
		bne		wordcopy						;/*  ... copy more */

stop
		b		stop

;/*------------------------------------------------------------------------------------------*/
;/*	 								make a word pool					 				    */
;/*------------------------------------------------------------------------------------------*/
		ltorg
src
		dcd		1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4
dst
		dcd		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		end


