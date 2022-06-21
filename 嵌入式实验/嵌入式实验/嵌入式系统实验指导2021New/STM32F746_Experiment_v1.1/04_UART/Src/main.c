/**
  ������ϵͳ��ʼ��������UART�ӿڣ���printf�����ض��������ڣ���PC���Ͳ������ַ������ٽ����յ����ַ������͸�PC��
**/
#include "main.h"
#include "UART_Config.h"

#define BUFFERSIZE	10
#define TIMEOUT			30000     /* 30 seconds */

extern UART_HandleTypeDef Uart_Handle;
void UART_Config(void);

/* UART recieve buffer */
uint8_t aRxBuffer[BUFFERSIZE + 1];
uint8_t my_aRxBuffer[1+1];

void Sys_Init(void);
void SystemClock_Config(void);

/* main */
int main(void)
{
  Sys_Init();
	
	/* Configure the UART peripheral */
  UART_Config();
	printf("\n\rSystem initialize success\n\r");
	
	while(1){
		
		printf("\n\r**** UART-HyperTerminal communication ****\n\rPlease enter 10 characters using keyboard...\n\r");
		printf("The input is: ");
		switch (HAL_UART_Receive(&Uart_Handle, (uint8_t*)my_aRxBuffer, 1, TIMEOUT))//�Ӽ��̶������룬�����������������ַ��ĸ���������my_aRxBuffer
		{
			case HAL_OK:
				BSP_LED_Toggle(LED1);
				printf("%s",my_aRxBuffer );//��ӡ������Ǹ��ַ�
				int i=0;
				while(1){
					i++;
					if(i==10)break;//ѭ������10���ַ�
					switch (HAL_UART_Receive(&Uart_Handle, (uint8_t*)my_aRxBuffer, 1, TIMEOUT))//����
					{
					case HAL_OK:
						BSP_LED_Toggle(LED1);//LED�仯״̬
						//printf("hh");
						printf("%s", my_aRxBuffer);//���ԣ���ӡ������ַ�
						break;
					case HAL_TIMEOUT:
						printf("Timeout!\n\r");
						break;
					default:
						printf("Error!\n\r");
						break;
					}
				}
				printf("\n\r");//��ӡ�س�����
				
				break;
			case HAL_TIMEOUT:
				printf("Timeout!\n\r");
				break;
			default:
				printf("Error!\n\r");
				break;
		}
	}
  
  printf("\n\rExample finished\n\r");
	
  while (1)
  {
  }
}
