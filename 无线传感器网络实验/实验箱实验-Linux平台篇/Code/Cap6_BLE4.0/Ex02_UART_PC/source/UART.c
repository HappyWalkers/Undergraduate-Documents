#include "UART.h"
/***************************************************************************
    * Configure UART
    *
    */

void Init_UART0(BaudSel_t baud,uint8 PERCFG_U0CFG_ALT)
{
    // Initialise UART protocol (start/stop bit, data bits, parity, etc.):
    // 1bit start/stop 8bit data no parity no flow
    // USART mode = UART (U0CSR.MODE = 1).

    //PERCF_U0CFG  select the UART 0 Alternative Location
    PERCFG = (PERCFG & ~PERCFG_U0CFG) | PERCFG_U0CFG_ALT;
    if(PERCFG_U0CFG_ALT == PERCFG_U0CFG_ALT1)
      P0SEL |= BIT5 | BIT4 | BIT3 | BIT2;
    else if(PERCFG_U0CFG_ALT == PERCFG_U0CFG_ALT2)
      P1SEL |= BIT5 | BIT4 | BIT3 | BIT2;

    U0CSR |= U0CSR_MODE;
    switch(baud)
    {
      case BAUD_2400:      U0GCR |= 6;     U0BAUD |= 59;    break;
      case BAUD_4800:      U0GCR |= 7;     U0BAUD |= 59;    break;
      case BAUD_9600:      U0GCR |= 8;     U0BAUD |= 59;    break;
      case BAUD_14400:     U0GCR |= 8;     U0BAUD |= 216;   break;
      case BAUD_19200:     U0GCR |= 9;     U0BAUD |= 59;    break;
      case BAUD_28800:     U0GCR |= 9;     U0BAUD |= 216;   break;
      case BAUD_38400:     U0GCR |= 10;    U0BAUD |= 59;    break;
      case BAUD_57600:     U0GCR |= 10;    U0BAUD |= 216;   break;
      case BAUD_76800:     U0GCR |= 11;    U0BAUD |= 59;    break;
      case BAUD_115200:    U0GCR |= 11;    U0BAUD |= 216;   break;
      case BAUD_230400:    U0GCR |= 12;    U0BAUD |= 216;   break;
      default         :    U0GCR |= 11;    U0BAUD |= 216;   break; //BAUD_115200;
    }
    URX0IF = 0; // ��ʼ����ɺ�������ڽ����жϱ�־λ
}

/***********************************************************
**  ��������: UART0_Send
**  ʵ�ֹ���: UART0 ��������
**  ��ڲ���: pData:�������������׵�ַ
**            len:���������ݵ��ֽ���
**  ���ؽ��: None
***********************************************************/
void UART0_Send( char* pData,int len )
{
  int i;
  for(i=0;i<len;i++)
  {
    //��д��������
    U0DBUF = *pData++;
    //�ȴ���ǰ�ֽڷ��ͽ���
    while(UTX0IF == 0)
      ;
    UTX0IF = 0;
  }
}
