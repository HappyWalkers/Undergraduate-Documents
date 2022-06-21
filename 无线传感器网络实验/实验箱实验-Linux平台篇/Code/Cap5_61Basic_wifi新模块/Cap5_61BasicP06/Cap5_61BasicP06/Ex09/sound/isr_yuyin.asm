//======================================================
// 文件名称：	ISR.asm
// 功能描述：	中断服务程序
// 维护记录：	2006-08-30	v1.0
//======================================================
.INCLUDE SPCE061A.inc
.INCLUDE s480.inc
//.INCLUDE hardware.inc
.TEXT
//==============================================================================
//汇编格式:FIQ_TMB
//功能描述：FIQ_TMB中断用于调用语音播报函数
//入口参数：无
//出口参数：无
//=============================================================================
.PUBLIC _IRQ1
_IRQ1:
	push r1,r5 to [sp]
	r1 = C_IRQ1_TMA
	test r1,[P_INT_Ctrl]
	jnz L_IRQ1_TMA
	pop r1,r5 from[sp]
	reti
L_IRQ1_TMA:
	[P_INT_Clear] = r1
	call F_FIQ_Service_SACM_S480
	pop r1,r5 from [sp]
	reti




