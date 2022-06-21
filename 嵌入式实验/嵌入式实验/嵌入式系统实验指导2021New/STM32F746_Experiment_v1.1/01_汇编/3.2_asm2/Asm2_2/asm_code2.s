;#*********************************************************************************************
;# NAME:	ARM_code2.s																		 *
;# Author: 	WUHAN R&D Center,Embest																	 *
;# Desc:	ARM instruction examples														 *
;#          Example for Condition Code														 *
;# History:	shw.He 2005.02.22																 *
;#*********************************************************************************************

;/*------------------------------------------------------------------------------------------*/
;/*	 								code								 				    */
;/*------------------------------------------------------------------------------------------*/
		
		area start,code,readwrite
		entry
		code32
num equ	2									;/*  Number of entries in jump table */
		export Reset_Handler
Reset_Handler
		mov		r0, #0						;/*  set up the three parameters */
		mov		r1, #3
		mov		r2, #2
		bl		arithfunc					;/*  call the function */

stop
		b		stop


;# ********************************************************************************************
;# * According R0 valude to execute the code													 *
;# ********************************************************************************************
arithfunc									;/*  label the function */
		cmp		r0, #num					;/*  Treat function code as unsigned integer */
		bhs		DoAdd						;/*  If code is >=2 then do operation 0. */

		adr		r3, JumpTable				;/*  Load address of jump table */
		ldr		pc, [r3,r0,LSL#2]			;/*  Jump to the appropriate routine */

JumpTable
		dcd		DoAdd
		dcd		DoSub

DoAdd
		add		r0, r1, r2					;/*  Operation 0, >1 */
		bx		lr 							;/*  Return */


DoSub
		sub		r0, r1, r2					;/*  Operation 1 */
		bx		lr							;/*  Return */

		end									;/*  mark the end of this file */
