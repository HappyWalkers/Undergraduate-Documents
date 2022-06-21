
#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2530.h>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned int uint16;
typedef unsigned char uint8;

void delay(uint);
void PortInit(void);
void PortTest_FlashAll(uint8 num);
void PortTest_FlowLED(uint8 num);
void Delay(uint n);


#endif//__BASIC_H__