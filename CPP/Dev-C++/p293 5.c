#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int ct(int a,int b)
{
	return a*60+b;
}

void invct(int time,int* h,int* m)
{
	*h=time/60;
	*m=time-(*h)*60;
}

int main(int argc, char *argv[]) {
	struct TIME{
		int start_time;
		int arrival_time;
	}time[8]={ {ct(8,0),ct(10,16)}, {ct(9,43),ct(11,52)},{ct(11,19),ct(13,31)},{ct(12,47),ct(15,0)},{ct(14,0),ct(16,8)},{ct(15,45),ct(17,55)},{ct(19,0),ct(21,20)},{ct(21,45),ct(23,58)}};
	
	printf("Enter a 24-hour time:(hh:mm) ");
	int time1,time2,timeg;
	scanf("%d:%d",&time1,&time2);
	timeg=ct(time1,time2);
//	printf("%d\n",timeg);
	
	int time1_st;
	int time2_st;
	int min=fabs(timeg-time[0].start_time);
	for(int i=0;i<8;i++)
	{
		if(min > fabs(timeg-time[i].start_time))
		{
			min=fabs(timeg-time[i].start_time);
			time1_st=time[i].start_time;
			time2_st=time[i].arrival_time;
		}
	}
//	printf("%d %d\n",time1_st,time2_st);
	
	int t1_h,t1_m,t2_h,t2_m;
	invct(time1_st,&t1_h,&t1_m);
	invct(time2_st,&t2_h,&t2_m);
//	printf("%d %d\n",t1_h,t1_m);
//	printf("%d %d\n",t2_h,t2_m);
	if(t1_h<12)
	{
		printf("Closet departure time is %d:%d a.m., ",t1_h,t1_m);
		if(t2_h<12)
		{
			printf("arriving at %d:%d a.m.",t2_h,t2_m);
		}
		else
		{
			printf("arriving at %d:%d p.m.",t2_h-12,t2_m);
		}
	}
	else if(t1_h==12)
	{
		printf("Closet departure time is %d:%d p.m., ",t1_h,t1_m);
		if(t2_h<12)
		{
			printf("arriving at %d:%d a.m.",t2_h,t2_m);
		}
		else
		{
			printf("arriving at %d:%d0 p.m.",t2_h-12,t2_m);
		}
	}
	else
	{
		printf("Closet departure time is %d:%d p.m., ",t1_h-12,t1_m);
		if(t2_h<12)
		{
			printf("arriving at %d:%d a.m.",t2_h,t2_m);
		}
		else
		{
			printf("arriving at %d:%d p.m.",t2_h-12,t2_m);
		}
	}

	return 0;
}
