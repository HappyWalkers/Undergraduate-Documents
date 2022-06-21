#ifndef	__SYSTEMTIME_h__
#define	__SYSTEMTIME_h__
//	write your header here

#define SYSTICK_WAITASYNC			1 // 是否需要异步延时

void SystemTimeInit(void);
void SystemTickISR(void);
unsigned long SystemTick(void);
void SystemTickReset(void);
void SystemTickWait(unsigned int tick);
#if defined(SYSTICK_WAITASYNC) && (SYSTICK_WAITASYNC == 1)
typedef struct WaitInfo{
	struct WaitInfo *next;
	unsigned long tick;
	int flag;
} WaitInfo;
void SystemTickWaitAsync(WaitInfo *info, unsigned int tick);
int SystemTickWaitFinished(WaitInfo *info);
void SystemTickClearWait(WaitInfo *info);

#endif//SYSTICK_WAITASYNC

#endif
