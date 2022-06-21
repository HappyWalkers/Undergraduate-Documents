#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {//debug,没有的不能用，有的不超过 ,意料之外的好处是可以自动避免相同的重量
	int num[7]={0};
	for(int i=1;i<=6;i++)
	{
		scanf("%d",num+i);
	}
//	for(int i=1;i<=6;i++)
//	{
//		printf("%d\n",num[i]);
//	}
	int count=0;
	int min=0,max=0;
	int gue[7]={0};
	
	if(num[1])min=1;
	else if(num[2])min=2;
	else if(num[3])min=3;
	else if(num[4])min=5;
	else if(num[5])min=10;
	else if(num[6])min=20;
	
	max=num[1]*1+num[2]*2+num[3]*3+num[4]*5+num[5]*10+num[6]*20;
	if(max>1000)return 0;
	for(int i=min;i<=max;i++)
	{
		int k=i;
		if(num[6]>=k/20)
		{
			gue[6]=k/20;
			k=k%20;
		}
		else
		{
			gue[6]=num[6];
			k=k-20*num[6];
		}
		
		if(num[5]>=k/10)
		{
			gue[5]=k/10;
			k=k%10;
		}
		else
		{
			gue[5]=num[5];
			k=k-10*num[5];
		}
		
		if(num[4]>=k/5)
		{
			gue[4]=k/5;
			k=k%5;
		}
		else
		{
			gue[4]=num[4];
			k=k-5*num[4];
		}
		
		if(num[3]>=k/3)
		{
			gue[3]=k/3;
			k=k%3;
		}
		else
		{
			gue[3]=num[3];
			k=k-3*num[3];
		}
		
		if(num[2]>=k/2)
		{
			gue[2]=k/2;
			k=k%2;
		}
		else
		{
			gue[2]=num[2];
			k=k-2*num[2];
		}
		
		if(num[1]>=k/1)
		{
			gue[1]=k/1;
			k=k%1;
		}
		else
		{
			gue[1]=num[1];
			k=k-1*num[1];
		}
		
//		for(int x=1;x<=6;x++)
//		{
//			printf("%d\n",gue[x]);
//		}
//		printf("\n");
		
		if(k==0)count++;
	}
	printf("Total=%d",count);

	return 0;
}
