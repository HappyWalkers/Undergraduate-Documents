#=============================================================================================
# File name	: 2410swis.s
# Author	: embest
# Descript	: S3C2410 
# History	:
#			(1) R.X.Huang, Programming start, March 12, 2005
#=============================================================================================

/*------------------------------------------------------------------------------------------*/
/*	 								constant define						 				    */
/*------------------------------------------------------------------------------------------*/

#*******************************************************************************
#* func Name      : SWI_ISR
#* Description    : This macro used to deal with the swi exception handler.
#* Input          : none
#* Output         : none
#*******************************************************************************
    .extern  SWI_ISR
SWI_ISR:
	movs pc,lr

#*******************************************************************************
#* Macro Name     : SAVE_CONTEXT
#* Description    : This macro used to save the context before entering
#                   an exception handler.
#* Input          : The range of registers' number to store.
#* Output         : none
#*******************************************************************************
.macro SAVE_CONTEXT reg1, reg2
	ldmfd  sp!, {r\reg1 - r\reg2, lr}	/*# Save The workspace plus the current return*/
										/*# address lr_ mode into the stack.*/
	mrs    r1,spsr						/*# Save the spsr_mode into r1.*/
	ldmfd  sp!,{r1}						/*# Save spsr.*/
.endm

#*******************************************************************************
#* Macro Name     : RESTORE_CONTEXT
#* Description    : This macro used to restore the context to return from
#                   an exception handler and continue the program execution.
#* Input          : The range of registers' number to restore.
#* Output         : none
#*******************************************************************************
.macro RESTORE_CONTEXT reg1, reg2
	ldmfd   sp!,{r1}					/*# Restore the saved spsr_mode into r1.*/
	msr     spsr_cxsf,r1				/*# Restore spsr_mode.*/
	ldmfd   sp!, {r\reg1 - r\reg2, pc}^	/*# Return to the instruction following...
										  # ...the exception interrupt.*/
.endm

#*******************************************************************************
#* Function Name  : Exception Handler
#* Description    : This function called when undefined instruction
#                   exception is entered.
#* Input          : none
#* Output         : none
#*******************************************************************************

TTab:
        SAVE_CONTEXT 0,12	/*# Save the workspace plus the current*/
							/*# return address lr_ und and spsr_und.*/
        bl      .			/*# Branch to exception handler.*/
        RESTORE_CONTEXT 0,12 /*# Return to the instruction following...*/
							/*# ...the undefined instruction.*/
