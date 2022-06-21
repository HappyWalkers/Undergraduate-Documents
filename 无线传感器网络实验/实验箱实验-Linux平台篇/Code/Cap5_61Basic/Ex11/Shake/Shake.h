/**************************************************************
*   File Name:  Shake.h
*   Introductions:
*   Last Modify Date: 2013.07.22
*   Modify:
*   Author: GuoZhenjiang < zhenjiang.guo@sunplusapp.com >
**************************************************************/

#ifndef	__SHAKE_H__
#define	__SHAKE_H__

#include "SPCE061A.h"

#define WARNING 	0
#define NORMAL	 	1


//extern void SetShakeFlag(uint8 newFlag);
extern void ShakeInit(void);
extern unsigned char ShakeRefresh(void);

#endif  // __SHAKE_H__

