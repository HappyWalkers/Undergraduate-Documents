/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32756g_eval.h"

/* DMA stream parameters definitions. You can modify these parameters to select*/
/*But note that only DMA2 Streams are capable of Memory to Memory transfers. */
#define DMA_INSTANCE               DMA2_Stream0
#define DMA_CHANNEL                DMA_CHANNEL_0
#define DMA_INSTANCE_IRQ           DMA2_Stream0_IRQn
#define DMA_INSTANCE_IRQHANDLER    DMA2_Stream0_IRQHandler

#define BUFFER_SIZE              32

#endif /* __MAIN_H */
