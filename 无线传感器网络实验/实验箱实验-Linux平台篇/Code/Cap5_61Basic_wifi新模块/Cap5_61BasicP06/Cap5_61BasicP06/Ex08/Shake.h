#ifndef	__SHAKE_H__
#define	__SHAKE_H__
//	write your header here

#include "SPCE061A.h"

#define WARNING 	0
#define NORMAL	 	1




#define SHAKE_IN 			C_Bit0					//震动传感器输入IOA0

#define SET_IOA_BIT(b)		do { *P_IOA_Buffer |= (b); } while(0)
#define CLR_IOA_BIT(b)		do { *P_IOA_Buffer &=~(b); } while(0)
#define READ_IOA_BIT(b)		((*P_IOA_Data & (b)) ? 1 : 0)

#endif
