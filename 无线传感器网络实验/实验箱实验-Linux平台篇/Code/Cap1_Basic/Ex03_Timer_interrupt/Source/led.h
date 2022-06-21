#ifndef _LED_
#define _LED_

#include <ioCC2530.h>

#define HIGH 1
#define LOW 0
#define SER P1_0
#define RCK P1_1
#define SRCK P1_2
#define BYTE_5 0x80
#define LED1 0x01
#define LED2 0x02
#define LED3 0x04
#define LED4 0x08
#define LED5 0x10
#define LED6 0x20
#define LED7 0x40
#define LED8 0x80

void INIT_LED(void);
void LEDprintf(unsigned char data,unsigned char byte);

#endif



