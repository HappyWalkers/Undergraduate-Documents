/**
  主程序：系统初始化，配置UART接口，将printf函数重定向至串口，向PC发送并接收字符串，再将接收到的字符串发送给PC。
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
		switch (HAL_UART_Receive(&Uart_Handle, (uint8_t*)my_aRxBuffer, 1, TIMEOUT))//从键盘读入输入，第三个参数是输入字符的个数，存入my_aRxBuffer
		{
			case HAL_OK:
				BSP_LED_Toggle(LED1);
				printf("%s",my_aRxBuffer );//打印输入的那个字符
				int i=0;
				while(1){
					i++;
					if(i==10)break;//循环读入10个字符
					switch (HAL_UART_Receive(&Uart_Handle, (uint8_t*)my_aRxBuffer, 1, TIMEOUT))//读入
					{
					case HAL_OK:
						BSP_LED_Toggle(LED1);//LED变化状态
						//printf("hh");
						printf("%s", my_aRxBuffer);//回显，打印输入的字符
						break;
					case HAL_TIMEOUT:
						printf("Timeout!\n\r");
						break;
					default:
						printf("Error!\n\r");
						break;
					}
				}
				printf("\n\r");//打印回车换行
				
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
