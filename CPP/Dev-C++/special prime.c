#include <stdio.h>
#include <stdlib.h>

int is_prime(int n)
{
	int i;
	for(i=2;i<=n/2;i++)
	{
		if(n%i==0)
		return 0;
	}
	return 1;
}

void split(int n,int a[])
{
	for(int i=0;;i++)
	{
		a[i]=n%10;
		n/=10;
		if(i==3)break;
	}
	return;
}
int sum(int a[])
{
	int all=0;
	int i;
	for(i=0;i<10;i++)
	{
		all+=a[i];
	}
	return all;
}
void main()
{
	int a[10]={0};
	int i;
	int flag=0;
	for(i=2;i<=5000;i++)
	{
		if(is_prime(i))
		{
			split(i,a);
			int j;
			for(j=0;j<4;j++)
			{
				if(is_prime(a[j]))
				{
					flag=1;
				}
				else
				{
					flag=0;
					break;
				}
			}
			if(flag==1 && is_prime(sum(a)))
			{
				printf("we find a special prime: %d\n",i);
			}
		}
	}
}
