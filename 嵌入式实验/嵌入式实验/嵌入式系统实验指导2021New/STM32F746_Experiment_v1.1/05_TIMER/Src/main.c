/**
  主程序：系统初始化后使用串口通信对Timer3的自动重载寄存器（ARR）初值进行选择，通过配置预分频，
	将Timer3的时钟频率设置为10KHz，在配置好定时器后开启定时器中断。Timer3的计数器寄存器从0开始以10KHz的频率递增，
	当其值大于ARR寄存器中的数值时，产生上溢，即定时器中断。
	注意：此例程中，每产生一次定时器中断，LED发生一次跳变，即模式1中LED闪烁频率为0.5Hz，模式2中LED闪烁频率为5Hz
**/
#include "main.h"
#include "system_init.h"

#define TIMEOUT   1000000       // 1000 seconds

/* Prescaler declaration */
uint8_t uRxBuffer = '1';			// 默认选择模式"1. 10000"
double ARRValue = 10000 - 1;// 默认ARR寄存器值为10000 - 1

extern UART_HandleTypeDef   UartHandle;
extern TIM_HandleTypeDef    TimHandle;

void System_Init(void);
void Timer_Config(uint16_t ARRValue);
    
/* main */
int main(void)
{
  System_Init();
	
	while (1) {
  
		printf("\n\r************************************\n\r");
		printf("* Timer counter frequency is 10KHz *\n\r* Upcounting mode                  *\n\r* Initial value is 0               *");
		printf("\n\r************************************\n\r");
		printf("\n\r Input data \n\r");

		uint8_t bef[10], aft[10], b = 0, a = 0;//bef:小数点前的数字，aft：小数点后的数字，b：bef的下表，a:aft的下下标
		uint8_t Flag = 1;//标志，判断是否有小数点
		for (int i = 0; i < 10; ++ i ) {//最大可以输入十个字符
			/* Receive data from UART */
			HAL_UART_Receive(&UartHandle, (uint8_t*)&uRxBuffer, 1, TIMEOUT);//接受键盘输入，将输入存入uRxBuffer，第三个参数表示可以读入的个数
			printf("%c", uRxBuffer);//将键盘输入打印查看
			if ((uRxBuffer >= '0' && uRxBuffer <= '9') || uRxBuffer == '.') { //如果输入值为0-9 或者 小数点 的话
				if (uRxBuffer == '.'){//如果输入为小数点
					Flag = 0;//标志位置0，表示已经遇到小数点
					continue;//继续下一个循环，因为小数点不读入存数字的数组
				}
				if (Flag) bef[b ++ ] = uRxBuffer - '0';//如果还没遇到小数点，将数字存入bef
				else aft[a ++ ] = uRxBuffer - '0';//遇到小数点之后，将数字存入aft
			} else break;//如果键盘输入值不是0-9或者小数点，就退出循环
		}
		printf("\n\r");//打印一个回车换行
		double ansbef = 0;//小数点之前的数值
		for (int i = 0; i < b; ++ i) {//循环，将小数点之前的数字组拼在一起
			ansbef = ansbef * 10 + bef[i];
		}
		
		double ansaft = 0;//小数点之后的数值
		for (int i = a - 1; i >= 0; -- i) {//循环，将小数点之后的数字组拼在一起
			ansaft = ansaft * 0.1 + aft[i];
		}
		ansaft *= 0.1;//最后一次循环完，再乘以0.1
		
		ARRValue = ansbef + ansaft; //频率，将小数点之前和之后的数字拼在一起
		ARRValue = 1 / ARRValue;//周期，频率之分1，单位：1/10k s
		ARRValue *= 5000;//周期
		
		printf("%lf", ARRValue);

		Timer_Config(ARRValue);	//使用Tim3在这里面配置中断

		/* Start the TIM Base generation in interrupt mode */
		HAL_TIM_Base_Start_IT(&TimHandle);
		
		printf("\n\rExample finished\n\r");
	}
  
  while (1)
  {
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED1);
}
