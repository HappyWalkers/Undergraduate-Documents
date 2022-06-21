#include "Control.h"
#include "UART.h"

uint8 ControlState = 0;

uint8 ControlSet( uint8 ControlData )
{
  P1SEL &= 0X0F;
  P1DIR |= 0XF0;
  //改变继电器控制状态，同时保持低四位状态不变。
  P1 &= (ControlData << 4) | 0X0F;
  P1 |= (ControlData << 4) & 0XF0;
  return ControlData;
}

void Dis_ConState( uint8 ConState )
{
  //AU 状态
  UART0_Send( "AU:", 3 );
  if( 0X01 == ( ConState & 0X01 ))
    UART0_Send( " on\t", sizeof(" on\t")-1 );
  else
    UART0_Send( "off\t", sizeof("off\t")-1 );
  //AD 状态
  UART0_Send( "AD:", 3 );
  if( 0X02 == ( ConState & 0X02 ))
    UART0_Send( " on\t", sizeof(" on\t")-1 );
  else
    UART0_Send( "off\t", sizeof("off\t")-1 );

  //BU 状态
  UART0_Send( "BU:", 3 );
  if( 0X04 == ( ConState & 0X04 ))
    UART0_Send( " on\t", sizeof(" on\t")-1 );
  else
    UART0_Send( "off\t", sizeof("off\t")-1 );

  //BD 状态
  UART0_Send( "BD:", 3 );
  if( 0X08 == ( ConState & 0X08 ))
    UART0_Send( " on\t", sizeof(" on\t")-1 );
  else
    UART0_Send( "off\t", sizeof("off\t")-1 );

  UART0_Send( "\r\n", 2 );
}