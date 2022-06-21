/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "system_init.h"
#include "cmsis_os.h"

/* Private macro -------------------------------------------------------------*/
#define mutexSHORT_DELAY     ((uint32_t) 20)
#define mutexNO_DELAY        ((uint32_t) 0)
#define mutexTWO_TICK_DELAY  ((uint32_t) 2)

/* Private variables ---------------------------------------------------------*/
static osMutexId osMutex;

/* Variables used to detect and latch errors. */
static __IO uint32_t HighPriorityThreadCycles = 0, MediumPriorityThreadCycles = 0, LowPriorityThreadCycles = 0;

/* Handles of the two higher priority tasks, required so they can be resumed (unsuspended). */
static osThreadId osHighPriorityThreadHandle, osMediumPriorityThreadHandle;

/* Private function prototypes -----------------------------------------------*/
static void MutexHighPriorityThread(void const *argument);
static void MutexMeduimPriorityThread(void const *argument);
static void MutexLowPriorityThread(void const *argument);

void System_Init(void);

/* Main program */
int main(void)
{
  System_Init();
  
  /* Configure LED1 */
  BSP_LED_Init(LED1);
  
  /* Creates the mutex  */
  osMutexDef(osMutex);
  osMutex = osMutexCreate(osMutex(osMutex));
  
  if(osMutex != NULL)
  {
    /* Define and create the high priority thread */
    osThreadDef(MutHigh, MutexHighPriorityThread, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
    osHighPriorityThreadHandle = osThreadCreate(osThread(MutHigh), NULL);
    
    /* Define and create the medium priority thread */
    osThreadDef(MutMedium, MutexMeduimPriorityThread, osPriorityLow, 0, configMINIMAL_STACK_SIZE);
    osMediumPriorityThreadHandle = osThreadCreate(osThread(MutMedium), NULL);
    
    /* Define and create the low priority thread */
    osThreadDef(MutLow, MutexLowPriorityThread, osPriorityIdle, 0, configMINIMAL_STACK_SIZE);
    osThreadCreate(osThread(MutLow), NULL);
  }
  
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  for(;;);
}

/* Mutex High Priority Thread */
static void MutexHighPriorityThread(void const *argument)
{  
  /* Just to remove compiler warning. */
  (void) argument;
  
  for(;;)
  {
    /* The first time through the mutex will be immediately available, on
    subsequent times through the mutex will be held by the low priority thread
    at this point and this Take will cause the low priority thread to inherit
    the priority of this tadhr.  In this case the block time must be
    long enough to ensure the low priority thread will execute again before the
    block time expires.  If the block time does expire then the error
    flag will be set here. */
    if(osMutexWait(osMutex, mutexTWO_TICK_DELAY) != osOK)
    {
      /* Toggle LED 1 to indicate error */
      BSP_LED_Toggle(LED1);
    }
    
    /* Ensure the other thread attempting to access the mutex
    are able to execute to ensure they either block (where a block 
    time is specified) or return an error (where no block time is 
    specified) as the mutex is held by this task. */
    osDelay(mutexSHORT_DELAY);
    
    /* We should now be able to release the mutex .  
    When the mutex is available again the medium priority thread
    should be unblocked but not run because it has a lower priority
    than this thread.  The low priority thread should also not run 
    at this point as it too has a lower priority than this thread. */
    osMutexRelease(osMutex);
    
    /* Keep count of the number of cycles this thread has performed. */
    HighPriorityThreadCycles++;
    BSP_LED_Toggle(LED1);
    
    /* Suspend ourselves to the medium priority thread can execute. */
    osThreadSuspend(NULL);
  }
}

/* Mutex Medium Priority Thread */
static void MutexMeduimPriorityThread(void const *argument)
{
  /* Just to remove compiler warning. */
  (void) argument;
  
  for(;;)
  {
    /* This thread will run while the high-priority thread is blocked, and the
    high-priority thread will block only once it has the mutex - therefore
    this call should block until the high-priority thread has given up the 
    mutex, and not actually execute past this call until the high-priority 
    thread is suspended. */
    if(osMutexWait(osMutex, osWaitForever) == osOK)
    {
      if(osThreadGetState(osHighPriorityThreadHandle) != osThreadSuspended)
      {
        /* Did not expect to execute until the high priority thread was
        suspended. */
      }
      else
      {
        /* Give the mutex back before suspending ourselves to allow
        the low priority thread to obtain the mutex. */
        osMutexRelease(osMutex);
        
        osThreadSuspend(NULL);
      }
    }
    
    /* The High and Medium priority threads should be in lock step. */
    if(HighPriorityThreadCycles != (MediumPriorityThreadCycles + 1))
    {
    }
    
    /* Keep count of the number of cycles this task has performed so a 
    stall can be detected. */
    MediumPriorityThreadCycles++;
    printf("\n\rMutexMeduimPriorityThread is running\n\r");
  }
}

/* Mutex Low Priority Thread */
static void MutexLowPriorityThread(void const *argument)
{
  /* Just to remove compiler warning. */
  (void) argument;
  
  for(;;)
  {
    /* Keep attempting to obtain the mutex.  We should only obtain it when
    the medium-priority thread has suspended itself, which in turn should only
    happen when the high-priority thread is also suspended. */
    if(osMutexWait(osMutex, mutexNO_DELAY) == osOK)
    {
      /* Is the high and medium-priority threads suspended? */
      if((osThreadGetState(osHighPriorityThreadHandle) != osThreadSuspended) || (osThreadGetState(osMediumPriorityThreadHandle) != osThreadSuspended))
      {
      }
      else
      {
        /* Keep count of the number of cycles this task has performed 
        so a stall can be detected. */
        LowPriorityThreadCycles++;
        printf("\n\rMutexLowPriorityThread is running\n\r");
        
        /* We can resume the other tasks here even though they have a
        higher priority than the this thread. When they execute they
        will attempt to obtain the mutex but fail because the low-priority 
        thread is still the mutex holder.  this thread will then inherit 
        the higher priority.  The medium-priority thread will block indefinitely 
        when it attempts to obtain the mutex, the high-priority thread will only 
        block for a fixed period and an error will be latched if the 
        high-priority thread has not returned the mutex by the time this 
        fixed period has expired. */
        osThreadResume(osMediumPriorityThreadHandle);
        osThreadResume(osHighPriorityThreadHandle);
        
        /* The other two tasks should now have executed and no longer
        be suspended. */
        if((osThreadGetState(osHighPriorityThreadHandle) == osThreadSuspended) || (osThreadGetState(osMediumPriorityThreadHandle) == osThreadSuspended))
        {
        }				
        
        /* Release the mutex, disinheriting the higher priority again. */
        if(osMutexRelease(osMutex) != osOK)
        {
        }
      }
    }
    
#if configUSE_PREEMPTION == 0
    {
      taskYIELD();
    }
#endif
  }
}
