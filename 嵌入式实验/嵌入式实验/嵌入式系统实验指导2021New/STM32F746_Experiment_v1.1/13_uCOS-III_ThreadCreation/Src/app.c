/**
  主程序：上电后进行系统硬件初始化以及uC/OS-III初始化，完成初始化工作后创建启动
	任务：AppTaskStart，在该任务中完成板级支持包BSP和CPU模块的初始化，并创建
	两个应用任务AppTaskObj0和AppTaskObj1，其中AppTaskObj0任务产生信号量并向串
	口发送信息，AppTaskObj1任务获取信号量，若获取到信号量则发送串口信息。
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
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/* --------------- APPLICATION GLOBALS ---------------- */
static  OS_TCB       AppTaskStartTCB;
static  CPU_STK      AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

/* --------------- SEMAPHORE TASK TEST --------------- */
static  OS_TCB       AppTaskObj0TCB;
static  CPU_STK      AppTaskObj0Stk[APP_CFG_TASK_OBJ_STK_SIZE];

static  OS_TCB       AppTaskObj1TCB;
static  CPU_STK      AppTaskObj1Stk[APP_CFG_TASK_OBJ_STK_SIZE];

#if (OS_CFG_SEM_EN > 0u)
static  OS_SEM       AppTaskObjSem;
#endif

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart (void  *p_arg);
static  void  AppTaskCreate(void);
static  void  AppObjCreate (void);

static  void  AppTaskObj0  (void  *p_arg);
static  void  AppTaskObj1  (void  *p_arg);

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
* Notes       : 1) STM32F4xx HAL library initialization:
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

    HAL_Init();                                                 /* 初始化HAL库                                          */

    Mem_Init();                                                 /* 初始化内存管理模块                                   */
    Math_Init();                                                /* 初始化数学算法模块（生成随机数种子）                 */

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet((CPU_CHAR *)"STM32F746xx",
                (CPU_ERR  *)&cpu_err);
#endif

    BSP_IntDisAll();                                            /* 关闭中断                                             */

    OSInit(&err);                                               /* 初始化uC/OS-III                                      */
    App_OS_SetAllHooks();

    OSTaskCreate(&AppTaskStartTCB,                              /* 创建启动进程                                         */
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

    OSStart(&err);                                              /* 开启uC/OS-III                                        */

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

    BSP_Init();                                                 /* 初始化板级支持包                                     */
    CPU_Init();                                                 /* 初始化CPU模块                                        */

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
		AppObjCreate();                                             /* 创建任务通信过程中使用的信号量等对象                 */

    APP_TRACE_DBG(("Creating Application Tasks\r\n"));
    AppTaskCreate();                                            /* 创建应用任务                                         */

    BSP_LED_Off(LED1);

    while (DEF_TRUE) {                                          /* 启动任务进入无限循环，LED1闪烁                         */
        BSP_LED_Toggle(LED1);
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
* Note(s)     : 该任务创建应用任务
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_ERR  os_err;

/* ---------- 创建应用任务 --------- */
    OSTaskCreate(&AppTaskObj0TCB,
                 "Kernel Objects Task 0",
                  AppTaskObj0,
                  0,
                  APP_CFG_TASK_OBJ_PRIO,
                 &AppTaskObj0Stk[0],
                  AppTaskObj0Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
                  APP_CFG_TASK_OBJ_STK_SIZE,
                  0u,
                  0u,
                  0,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);

    OSTaskCreate(&AppTaskObj1TCB,
                 "Kernel Objects Task 0",
                  AppTaskObj1,
                  0,
                  APP_CFG_TASK_OBJ_PRIO,
                 &AppTaskObj1Stk[0],
                  AppTaskObj1Stk[APP_CFG_TASK_OBJ_STK_SIZE / 10u],
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
* Note(s)     : 该任务创建任务通信过程中使用的信号量等对象。
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
    OS_ERR  os_err;


#if (OS_CFG_SEM_EN > 0u)
    OSSemCreate(&AppTaskObjSem,
                "Sem Test",
                 0u,
                &os_err);

#endif

}


/*
*********************************************************************************************************
*                                          AppTaskObj0()
*
* Description : Test uC/OS-III objects.
*
* Argument(s) : p_arg is the argument passed to 'AppTaskObj0' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : This is a task
*
* Note(s)     : 该任务产生信号量并向串口发送信息。
*********************************************************************************************************
*/

static  void  AppTaskObj0 (void  *p_arg)
{
    OS_ERR  os_err;

    (void)p_arg;


    while (DEF_TRUE) {
#if (OS_CFG_SEM_EN > 0u)
        OSSemPost(&AppTaskObjSem,
                   OS_OPT_POST_1,
                  &os_err);
#endif

        OSTimeDlyHMSM( 0u, 0u, 0u, 10u,
                       OS_OPT_TIME_HMSM_STRICT,
                      &os_err);
        APP_TRACE_INFO(("Object test task 0 running ....\r\n"));				// 发送信息到串口
			
    }
}


/*
*********************************************************************************************************
*                                          AppTaskObj1()
*
* Description : Test uC/OS-III objects.
*
* Argument(s) : p_arg is the argument passed to 'AppTaskObj1' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : This is a task
*
* Note(s)     : 该任务等待信号量，若获取到信号量则发送串口信息，否则挂起任务，直到获取到信号量。
*********************************************************************************************************
*/

static  void  AppTaskObj1 (void  *p_arg)
{
    OS_ERR       os_err;

    (void)p_arg;

    while (DEF_TRUE) {

#if (OS_CFG_SEM_EN > 0u)
        OSSemPend(&AppTaskObjSem,
                   0,
                   OS_OPT_PEND_BLOCKING,
                   0,
                  &os_err);
#endif

        OSTimeDlyHMSM( 0u, 0u, 0u, 10u,
                       OS_OPT_TIME_HMSM_STRICT,
                      &os_err);
        APP_TRACE_INFO(("Object test task 1 running ....\r\n"));				// 发送信息到串口
			
    }
}
