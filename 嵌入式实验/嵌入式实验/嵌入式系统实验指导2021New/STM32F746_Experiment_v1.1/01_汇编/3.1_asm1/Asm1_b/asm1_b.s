;#********************************************************************************************
;# NAME:		asm1_b.s													                                               *
;# Author: 	WUHAN R&D Center, Embest									                                       *
;# Desc:		ARM instruction examples									                                       *
;# History:	TianYunFang 2007.05.12										                                       *
;#********************************************************************************************
;/*------------------------------------------------------------------------------------------*/
;/*	 					constant define		 			 				                                               */
;/*------------------------------------------------------------------------------------------*/
x			EQU 45							      ;/* x=45 */
y			EQU	64							      ;/* y=64 */
z			EQU	87								    ;/* z=87 */
stack_top	EQU	0x30200000			  ;/* define the top address for stacks*/
			                 export	Reset_Handler

;/*-------------------------------------------------------------------------------------------*/
;/*	 					                           code						 	                                    */
;/*-------------------------------------------------------------------------------------------*/
	AREA text,CODE,READONLY

Reset_Handler										;/* code start */
		mov		r0, #x 								;/* put x value into R0  */
		mov		r0, r0, lsl #8						;/* R0 = R0 << 8  */
		mov		r1, #y								;/* put y value into R1  */
		add		r2, r0, r1, lsr #1					;/* R2 = (R1>>1) + R0 */
		ldr		sp, =stack_top
		str		r2, [sp]

		mov		r0, #z								;/* put z value into R0  */
		and		r0, r0, #0xFF						;/* get low 8 bit from R0 */
		mov		r1, #y								;/* put y value into R1  */
		add		r2, r0, r1, lsr #1					;/* R2 = (R1>>1) + R0 */
		
		ldr		r0, [sp]							;/* put y value into R1 */
		mov		r1, #0x01
		orr		r0, r0, r1
		mov		r1, R2								;/* put y value into R1  */
		add		r2, r0, r1, lsr #1					;/* R2 = (R1>>1) + R0  */

stop
		b		stop								    ;/* end the code £¬cycling*/
		END
