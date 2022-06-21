#include <stdio.h>
int findsum(int i,int* a)
{
	int j;
	int t=0;
	int x=0;
	for(j=1;j<i;j++)
	{
		if(i%j==0)
		{
			a[t++]=j;
			x+=a[t-1];
		}
	}
	return x;
}

int main()
{
	printf("enter a initial number and a ending number:");
	int init,end;
	scanf("%d%d",&init,&end);

	if(init>end)
	{
		int x;
		x=init;
		init=end;
		end=x;
	}

	int i;
	for(i=init;i<=end;i++)
	{
		int a[100];
		if(i==findsum(i,a))
		printf("%d\n",i);
	}
}


