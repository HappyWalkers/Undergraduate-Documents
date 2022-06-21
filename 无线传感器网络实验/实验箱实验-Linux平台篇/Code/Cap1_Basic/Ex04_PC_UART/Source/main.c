#include "UART.h"
#include "Basic.h"


void main(void)
{	
#define SENDSTRING "Hello World!\r\n"
    LEDPortInit();
    UART0_Init( BAUD_115200 );

    for( ; ; )
    {
      UART0_Send( SENDSTRING, sizeof(SENDSTRING)-1);

      SET_LED_D8;  //P1 &= ~0x02; //P2 &= 0xfe;  //
      Delay(5);  //Delay(5);
      CLR_LED_D8;  //P2 |= 0x01;  //
      Delay(120);
    }
}
