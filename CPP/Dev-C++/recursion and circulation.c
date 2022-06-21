#include <stdio.h>
#include <stdlib.h>

int factorial_recursion(int n)
{
	if(n==1)return 1;
	return n*factorial_recursion(n-1);
}

int factotial_circulation(int n)
{
	int x=1;
	for(int i=1;i<=n;i++)
	{
		x=x*i;
	}
	return x;
}

long long Fabonacci_recurision(long long n)
{
	if(n==1)return 1;
	if(n==2)return 1;
	return Fabonacci_recurision(n-1)+Fabonacci_recurision(n-2);
}

long long Fabonacci_circulation(long long n)
{
	if(n==1)return 1;
	if(n==2)return 1;
	long long m=1;
	long long l=1;
	long long x;
	for(long long i=1;i<=n-2;i++)
	{
		x=m+l;
		m=l;
		l=x;
	}
	return x;
}

void move(char a, char b)
{
	printf("%c-->%c\n",a,b);
}

void hanoi(int n,char a,char b,char c)
{
	if(n==1)move(a,c);
	
	else
	{
		hanoi(n-1,a,c,b);
		move(a,c);
		hanoi(n-1,b,a,c);
	}
}

int main()
{
	printf("%d\n",factorial_recursion(10));
	
	printf("%d\n",factotial_circulation(10));
	
	for(long long i=1;i<=100;i++)
	{
	printf("%lld\t",Fabonacci_recurision(i));
	}
	
	printf("\n");
	
	for(long long i=1;i<=100;i++)
	{
		printf("%lld\t",Fabonacci_circulation(i));
	}
	
	hanoi(3,'A','B','C');
}
