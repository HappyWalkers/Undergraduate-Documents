/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "system_init.h"
#include "cmsis_os.h"

#define blckqSTACK_SIZE   configMINIMAL_STACK_SIZE
#define QUEUE_SIZE        (uint32_t) 1

/* Private variables ---------------------------------------------------------*/
osMessageQId osQueue;
uint32_t ProducerValue = 0, ConsumerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void System_Init(void);

/* Thread function that creates an incrementing number and posts it on a queue. */
static void MessageQueueProducer(const void *argument);

/* Thread function that removes the incrementing number from a queue and checks that
   it is the expected number. */
static void MessageQueueConsumer(const void *argument);

/* Main program */
int main(void)
{
  System_Init();
  
  /* Configure LED1 */
  BSP_LED_Init(LED1);
  
  /* Create the queue used by the two tasks to pass the incrementing number.
  Pass a pointer to the queue in the parameter structure. */
  osMessageQDef(osqueue, QUEUE_SIZE, uint16_t);
  osQueue = osMessageCreate(osMessageQ(osqueue), NULL);
  
  /* Note the producer has a lower priority than the consumer when the tasks are spawned. */
  osThreadDef(QCons, MessageQueueConsumer, osPriorityBelowNormal, 0, blckqSTACK_SIZE);
  osThreadCreate(osThread(QCons), NULL);
  
  osThreadDef(QProd, MessageQueueProducer, osPriorityBelowNormal, 0, blckqSTACK_SIZE);
  osThreadCreate(osThread(QProd), NULL);
  
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  for(;;);
}

/* Message Queue Producer Thread */
static void MessageQueueProducer(const void *argument)
{
  for(;;)
  {		
    osMessagePut(osQueue, ProducerValue, 100);
    
    printf("\n\rMessage produced\n\r");
    
    /* Increment the variable we are going to post next time round.  The
    consumer will expect the numbers to follow in numerical order. */
    ++ProducerValue;

    osDelay(1000);
  }
}

/* Message Queue Consumer Thread */
static void MessageQueueConsumer(const void *argument)
{
  osEvent event;
  
  for(;;)
  {
    /* Get the message from the queue */
    event = osMessageGet(osQueue, 100);
    
    if(event.status == osEventMessage)
    {
      if(event.value.v == ConsumerValue)
      {
        /* Toggle LED1 to indicate success */
        BSP_LED_Toggle(LED1);
        
        /* Increment the value we expect to remove from the queue next time round. */
        ++ConsumerValue;
      }
    }		
  }
}
