//====================================================
//文    件: ex06_Thread.c
//功能描述: 实验六范例代码
//维护记录: 2008-06-13  V1.0    lijian<lijian@sunnorth.com.cn>
//====================================================
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define msleep(m)	usleep(m*1000)

time_t end_time;
//====================================================
// 语法格式：void ThreadA(cyg_addrword_t data)
// 功能描述: 主线程
// 入口参数: data	-	由OS传递
// 出口参数: 无
//====================================================
void ThreadA(void *arg)
{
	while(time(NULL) < end_time)
	{
		printf("Thread A prints something...\n");
		msleep(300);
	}
}

//====================================================
// 语法格式：void ThreadB(cyg_addrword_t data)
// 功能描述: 主线程
// 入口参数: data	-	由OS传递
// 出口参数: 无
//====================================================
void ThreadB(void *arg)
{
	while(time(NULL) < end_time)
	{
		printf("Thread B prints something...\n");
		msleep(700);
	}
}

int main(int argc, char *argv[])
{
	pthread_t a_th_id;
	pthread_t b_th_id;
	int ret;
	
	end_time = time(NULL) + 10;			// 运行10秒
	ret = pthread_create(&a_th_id, NULL, (void*)ThreadA, NULL);
	if(ret != 0)
	{
		perror("pthread_create: idx_th");
		exit(EXIT_FAILURE);
	}
	ret = pthread_create(&b_th_id, NULL, (void*)ThreadB, NULL);
	if(ret != 0)
	{
		perror("pthread_create: mon_th");
		exit(EXIT_FAILURE);
	}
	pthread_join(a_th_id, NULL);
	pthread_join(b_th_id, NULL);
	exit(EXIT_SUCCESS);
}
