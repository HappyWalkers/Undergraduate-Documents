#ifndef __DEF_H__
#define __DEF_H__

#define UINT32T unsigned int
#define INT32T	int
#define UINT16T unsigned short
#define INT16T	short int
#define UINT8T  unsigned char
#define	INT8T  char

#define TRUE 	1
#define FALSE 	0
#define OK		1
#define FAIL	0
#define FileEnd	1
#define	NotEnd	0

#define False 0
#define True !False

/* Sets the result on bPort */
#define BIT_SET(bPort,bBitMask)        (bPort |= bBitMask)
#define BIT_CLR(bPort,bBitMask)        (bPort &= ~bBitMask)

/* Returns the result */
#define GET_BIT_SET(bPort,bBitMask)    (bPort | bBitMask)
#define GET_BIT_CLR(bPort,bBitMask)    (bPort & ~bBitMask)

/* Returns 0 if the condition is False & a non-zero value if it is True */
#define TEST_BIT_SET(bPort,bBitMask)   (bPort & bBitMask)
#define TEST_BIT_CLR(bPort,bBitMask)   ((~bPort) & bBitMask)

#endif /*__DEF_H__*/

