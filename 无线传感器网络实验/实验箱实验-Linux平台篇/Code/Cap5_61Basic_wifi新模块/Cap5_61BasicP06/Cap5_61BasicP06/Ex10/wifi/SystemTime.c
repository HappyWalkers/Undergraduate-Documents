//============================================================================
//	文件名称：	SystemTime.c
//	功能描述：	系统时间
//	维护记录：	lijian<lijian@sunplusapp.com>	2013-3-12
//==========================================================================
#include "SystemTime.h"
#include "SPCE061A.h"
#include <string.h>

static volatile unsigned long _sysTick = 0;
static WaitInfo *waitQueue = NULL;
void SystemTimeInit(void)
{
	_sysTick = 0;
}

// 需在1KHz中断中调用
void SystemTickISR(void)
{
	if(*P_INT_Ctrl & C_IRQ4_1KHz)
	{
		_sysTick++;
#if defined(SYSTICK_WAITASYNC) && (SYSTICK_WAITASYNC == 1)
		if(waitQueue != NULL)
		{
			WaitInfo *prev = NULL;
			WaitInfo *cur = waitQueue;
			while(cur != NULL)
			{
				if(cur->tick == _sysTick)
				{
					cur->flag = 1;
					// remove it from the queue
					if(prev == NULL)
					{
						waitQueue = cur->next;
						cur = cur->next;
					}
					else
					{
						prev->next = cur->next;
						cur = cur->next;
					}
				}
				else
				{
					prev = cur;
					cur = cur->next;
				}
			}
		}
#endif
	}
}

unsigned long SystemTick(void)
{
	return _sysTick;
}

void SystemTickReset(void)
{
	_sysTick = 0;
}

void SystemTickWait(unsigned int tick)
{
	unsigned long _t = _sysTick + tick;

	while(_sysTick != _t);
}

#if defined(SYSTICK_WAITASYNC) && (SYSTICK_WAITASYNC == 1)
void SystemTickWaitAsync(WaitInfo *info, unsigned int tick)
{
	info->next = waitQueue;
	waitQueue = info;
	info->tick = _sysTick + tick;
	info->flag = 0;
}

int SystemTickWaitFinished(WaitInfo *info)
{
	return info->flag;
}

void SystemTickClearWait(WaitInfo *info)
{
	if(waitQueue == NULL)
		return;
	if(waitQueue == info)
	{
		waitQueue = info->next;
	}
	else
	{
		WaitInfo *prev = waitQueue;
		WaitInfo *cur = waitQueue->next;
		while(cur != NULL)
		{
			if(cur == info)
			{
				prev->next = info->next;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
	}
}
#endif
