#include <stdio.h>
#include <stdlib.h>
int main()
{
	long i,j;
	long k;
	printf("please input a begining number and a ending number£º");
	scanf("%ld%ld",&i,&j);
	if(i>j)
	{
		int x=i;
		i=j;
		j=x;
	}
	else
	for(k=i;k<=j;k++)
	{
		int flag=1;
		long m;
		for(m=2;m<=(long)sqrt(k);m++)
		{
			long n=k/m;
			if(k==n*m)
			{
				flag=0;
				break;
			}
		}
		if(flag==0)continue;
		if(k==1)continue;
		printf("%ld\n",k);
	}
}
