/**
  �������ϵ�����ϵͳӲ����ʼ���Լ�uC/OS-III��ʼ������ɳ�ʼ�������󴴽�����
	����AppTaskStart���ڸ���������ɰ弶֧�ְ�BSP��CPUģ��ĳ�ʼ������BSP��ʼ��
	�����н�PA0����Ӧ����S2������ΪEXTI0���ж�Դ���½��ش������ٴ�������Ӧ������
	Task_A��Task_B��Task_A������S3�Ƿ񱻰��²��ͷţ���S3�ͷ�ʱ��Task_B�����ź�����
	Task_B�����ȡ�ź���������ȡ���ź������ʹ�����Ϣ������/Ϩ��LED1��EXTI0�жϷ�
	�������Task_A��ͬ����Task_B�����ź�����
**/
#include  <stdarg.h>
#include  <stdio.h>
#include  <math.h>
#include  <stm32f7xx_hal.h>
#include "stm32756g_eval.h"

#include  <cpu.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <os.h>
#include  <os_app_hooks.h>

#include  <app_cfg.h>
#include  <bsp.h>

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
#include  <app_serial.h>
#endif
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

//#define  APP_TASK_EQ_0_ITERATION_NBR              16u
//#define  APP_TASK_EQ_1_ITERATION_NBR              18u


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
/* --------------- APPLICATION GLOBALS ---------------- */
static  OS_TCB       AppTaskStartTCB;
static  CPU_STK      AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

/* --------------- SEMAPHORE TASK TEST --------------- */
static  OS_TCB       Task_ATCB;
static  CPU_STK      Task_AStk[APP_CFG_TASK_OBJ_STK_SIZE];

static  OS_TCB       Task_BTCB;
static  CPU_STK      Task_BStk[APP_CFG_TASK_OBJ_STK_SIZE];

#if (OS_CFG_SEM_EN > 0u)
static  OS_SEM       wait_key_sem;
#endif

unsigned char Toggle_En = 1;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart (void  *p_arg);
static  void  AppTaskCreate(void);
static  void  AppObjCreate (void);

static  void  Task_A(void *p_arg);
static  void  Task_B(void *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*
* Notes       : 1) STM32F7xx HAL library initialization:
*                      a) Configures the Flash prefetch, intruction and data caches.
*                      b) Configures the Systick to generate an interrupt. However, the function ,
*                         HAL_InitTick(), that initializes the Systick has been overwritten since Micrium's
*                         RTOS has its own Systick initialization and it is recommended to initialize the
*                         Systick after multitasking has started.
*
*********************************************************************************************************
*/

int main(void)
{
    OS_ERR   err;
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR  cpu_err;
#endif

    HAL_Init();                                                 /* ��ʼ��HAL                                       */

    Mem_Init();                                                 /* ��ʼ���ڴ����ģ��                                   */
    Math_Init();                                                /* ��ʼ����ѧ�㷨ģ�飨������������ӣ�                 */

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet((CPU_CHAR *)"STM32F746xx",
                (CPU_ERR  *)&cpu_err);
#endif

    BSP_IntDisAll();                                            /* �ر��ж�                                             */

    OSInit(&err);                                               /* ��ʼ��uC/OS-III                                      */
    App_OS_SetAllHooks();

    OSTaskCreate(&AppTaskStartTCB,                              /* �����������̣��ڴ˳����������жϣ����ж�                                         */
                  "App Task Start",
                  AppTaskStart,
                  0u,
                  APP_CFG_TASK_START_PRIO,
                 &AppTaskStartStk[0u],
                  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10u],
                  APP_CFG_TASK_START_STK_SIZE,
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &err);

    OSStart(&err);                                              /* ����uC/OS-III                                        */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
        ;
    }
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR      err;
    CPU_INT32U  r0;
    CPU_INT32U  r1;
    CPU_INT32U  r2;
    CPU_INT32U  r3;
    CPU_INT32U  r4;
    CPU_INT32U  r5;
    CPU_INT32U  r6;
    CPU_INT32U  r7;
    CPU_INT32U  r8;
    CPU_INT32U  r9;
    CPU_INT32U  r10;
    CPU_INT32U  r11;
    CPU_INT32U  r12;


   (void)p_arg;

    r0  =  0u;                                                  /* Initialize local variables.                          */
    r1  =  1u;
    r2  =  2u;
    r3  =  3u;
    r4  =  4u;
    r5  =  5u;
    r6  =  6u;
    r7  =  7u;
    r8  =  8u;
    r9  =  9u;
    r10 = 10u;
    r11 = 11u;
    r12 = 12u;

    BSP_Init();                                                 /* ��ʼ���弶֧�ְ����ڴ˳����������ⲿ�ж�0                                   */
    CPU_Init();                                                 /* ��ʼ��CPUģ��                                        */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

		UART_Config();
		
		/* Initialize LCD Communication for Application ...  		*/
		BSP_LCD_Config();
    APP_TRACE_DBG(("Creating Application kernel objects\r\n"));
		AppObjCreate();                                             /* ��������ͨ�Ź�����ʹ�õ��ź����ȶ���                 */

    APP_TRACE_DBG(("Creating Application Tasks\r\n"));
    AppTaskCreate();                                            /* ����Ӧ������                                         */

    BSP_LED_Off(LED1);

    while (DEF_TRUE) {                                          /* ���������������ѭ��                                 */
        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);

        if ((r0  !=  0u) ||                                     /* Check task context.                                  */
            (r1  !=  1u) ||
            (r2  !=  2u) ||
            (r3  !=  3u) ||
            (r4  !=  4u) ||
            (r5  !=  5u) ||
            (r6  !=  6u) ||
            (r7  !=  7u) ||
            (r8  !=  8u) ||
            (r9  !=  9u) ||
            (r10 != 10u) ||
            (r11 != 11u) ||
            (r12 != 12u)) {
           APP_TRACE_INFO(("Context Error\r\n"));
        }
    }
}

/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create Application Tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : �����񴴽�Ӧ������
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_ERR  os_err;

/* ---------- ����Ӧ������ --------- */
  	OSTaskCreate(&Task_ATCB,
                 "Kernel Objects Task A",
                  Task_A,
                  0,
                  APP_CFG_TASK_OBJ_PRIO,
                 &Task_AStk[0],
                  Task_AStk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
                  APP_CFG_TASK_OBJ_STK_SIZE,
                  0u,
                  0u,
                  0,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);

    OSTaskCreate(&Task_BTCB,
                 "Kernel Objects Task B",
                  Task_B,
                  0,
                  APP_CFG_TASK_OBJ_PRIO,
                 &Task_BStk[0],
                  Task_BStk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
                  APP_CFG_TASK_OBJ_STK_SIZE,
                  0u,
                  0u,
                  0,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);
}

/*
*********************************************************************************************************
*                                          AppObjCreate()
*
* Description : Create Application Kernel Objects.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : �����񴴽�����ͨ�Ź�����ʹ�õ��ź����ȶ���
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
    OS_ERR  os_err;

#if (OS_CFG_SEM_EN > 0u)
    OSSemCreate(&wait_key_sem,
                "Key Detection",
                 0u,
                &os_err);
#endif
}

/*
*********************************************************************************************************
*                                          Task_A()
*
* Description : Test uC/OS-III objects.
*
* Argument(s) : p_arg is the argument passed to 'Task_A' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : This is a task
*
* Note(s)     : ��������S3�Ƿ񱻰��²��ͷţ���S3�ͷ�ʱ��Task_B�����ź�����
*********************************************************************************************************
*/
void Task_A(void *p_arg)
{	   
	OS_ERR  err;
	unsigned char key_press = 0;

	while(DEF_TRUE)
	{
		OSTimeDly(30, OS_OPT_TIME_DLY, &err);
    if (BSP_PB_GetState(BUTTON_TAMPER) == RESET)		//�ж�S3����
			key_press = 1;
		if (BSP_PB_GetState(BUTTON_TAMPER) == SET)			//�ж�S3�ͷ�
		{
			if(key_press == 1)
			{
				key_press = 0;
				OSSemPost(&wait_key_sem, OS_OPT_POST_1, &err);
			}
		}	
	}
}
/*
*********************************************************************************************************
*                                          Task_B()
*
* Description : Test uC/OS-III objects.
*
* Argument(s) : p_arg is the argument passed to 'Task_B' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : This is a task
*
* Note(s)     : ������ȴ�Task_A���жϷ�������������ź���������ȡ���ź���ʱ����/Ϩ��LED1���򴮿ڷ������ݡ�
*********************************************************************************************************
*/
void Task_B(void *p_arg)
{			  
	OS_ERR  err;
	CPU_TS  ts;

	while(DEF_TRUE)
	{
		OSSemPend(&wait_key_sem,
                  0,
                  OS_OPT_PEND_BLOCKING,
                  &ts,
                  &err);
		BSP_LED_Toggle(LED1);	//Toggle after key release
		APP_TRACE_DBG(("Get a Semaphore from Task A or EXTI0\n\r"));
		OSTimeDly(50, OS_OPT_TIME_DLY, &err);
		Toggle_En = 1;
	}
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  * EXTI0�жϷ����ӳ�����Task_B�����ź�����
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  OS_ERR  err;
	if(GPIO_Pin == WAKEUP_BUTTON_PIN)		//��S2����������ж�
  {
    if(Toggle_En == 1)
		{
			OSSemPost(&wait_key_sem, OS_OPT_POST_1, &err);
			Toggle_En = 0;				//=0���ύ�ź����󣬻�û�жԵƽ��д����ı�־
		}
  }
}
