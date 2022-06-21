#include <stdio.h>
//input the score of five students and get its sum,ave,after that,get the ave ,max, min of five courses
int main()
{
	printf("please enter five scores of a student, and press the Enter, and repeat that untill getting five students:\n ");
	int a[6][6];
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=5;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	
	int std_sum[5];
	float std_ave[5];
	for(int i=1;i<=5;i++)//std_sum
	{
		std_sum[i]=a[i][1]+a[i][2]+a[i][3]+a[i][4]+a[i][5];
		printf("the sum of No.%d students is:",i);
		printf("%d\n",std_sum[i]);
	}
	
	for(int i=1;i<=5;i++)//std_ave
	{
		std_ave[i]=std_sum[i]/5.0f;
		printf("the ave of No.%d students is:",i);
		printf("%.2f\n",std_ave[i]);
	}
	
	float cor_ave[5];
	int max[5];
	int min[5];
	for(int i=1;i<=5;i++)//the ave of every course
	{
		cor_ave[i]=(a[1][i]+a[2][i]+a[3][i]+a[4][i]+a[5][i])/5.0f;
		printf("the ave of No.%d course is:");
		printf("%.2f\n",cor_ave[i]);
	}
	
	for(int i=1;i<=5;i++)//the max of every course
	{
		int max=0;
	    for(int j=1;j<=5;j++)
	    {
	    	if(max<a[j][i])
	    	max=a[j][i];
		}
		printf("the max of No.%d course is:",i);
		printf("%d\n",max);
	}
	
	for(int i=1;i<=5;i++)//the min of every course
	{
		int min=100;
	    for(int j=1;j<=5;j++)
	    {
	    	if(min>a[j][i])
	    	min=a[j][i];
		}
		printf("the min of No.%d course is:",i);
		printf("%d\n",min);
	}
}
