#include "led.h"
#include "Basic.h"

uint16 T_delay = 10;
void main(void){
  INIT_LED();
  for( ;; )
  {
     LEDprintf(LED1_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED2_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED3_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED4_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED5_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED6_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED7_ON,BYTE_5);
     Delay(T_delay);
     LEDprintf(LED8_ON,BYTE_5);
     Delay(T_delay);
  }
}