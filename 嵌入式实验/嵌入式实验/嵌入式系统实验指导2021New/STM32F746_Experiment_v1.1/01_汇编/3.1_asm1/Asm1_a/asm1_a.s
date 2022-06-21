;*********************************************************************************************
; NAME:	 asm1_a.s													                                                   *
; Author: 	 TYW	/WUHAN R&D Center,Embest								                                   *
; Desc:	 ARM instruction examples									                                           *
; History:	 2007.5.1													                                               *
;*********************************************************************************************

;/*-----------------------------------------------------------------------------------------*/
;/*	 			    	constant define				  		 				                                        */
;/*-----------------------------------------------------------------------------------------*/
x			EQU	45						        ;  x=45
y			EQU	64						        ;  y=64/
stack_top	EQU	0x30200000				; define the top address for stacks 
	                      
          export Reset_Handler

;/*---------- ------------------------------------------------------------------------------*/
;/*	 					code			 				 			*/
;/*-----------------------------------------------------------------------------------------*/
	AREA text,CODE,READONLY
		export 
Reset_Handler                   ; code start */
		ldr		sp, =stack_top
		mov		r0, #x					      ; put x value into R0
		str		r0, [sp]				      ; save the value of R0 into stacks
		mov		r0, #y					      ; put y value into R0
		ldr		r1, [sp]				      ; read the data from stack,and put it into R1
		add		r0, r0, r1				    ;R0=R0+R1	
		str		r0, [sp]
stop
 		b		stop 					          ; end the code £¬cycling
		end								