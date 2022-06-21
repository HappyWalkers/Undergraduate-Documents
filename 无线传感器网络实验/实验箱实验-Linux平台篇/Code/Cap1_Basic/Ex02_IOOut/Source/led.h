#ifndef _LED_
#define _LED_

#include <ioCC2530.h>

#define HIGH 1
#define LOW 0
#define SER P1_0
#define RCK P1_1
#define SRCK P1_2
#define BYTE_5 0x80
#define LED1_ON 0x01
#define LED2_ON 0x02
#define LED3_ON 0x04
#define LED4_ON 0x08
#define LED5_ON 0x10
#define LED6_ON 0x20
#define LED7_ON 0x40
#define LED8_ON 0x80


void INIT_LED(void);
void LEDprintf(unsigned char data,unsigned char byte);

#endif



