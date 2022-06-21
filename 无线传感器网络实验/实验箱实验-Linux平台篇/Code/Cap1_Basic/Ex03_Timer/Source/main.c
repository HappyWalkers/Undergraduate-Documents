#include "timer.h"

void main(void){
  init_timer_1();
  for( ;; )
    glint_led(LED1);

}
