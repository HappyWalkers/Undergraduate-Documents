#include <stdio.h>
int ama(int n)
{
	int i;
	int x=1;
	for(i=1;i<=n;i++)
	{
		x*=i;
	}
	return 
	x;
}
int main()//print e
{
	printf("to get the value of e, enter a number of int:");
	unsigned n;
	scanf("%ud",&n);
	
	int i;
	double e=1.0f;
	for(i=1;i<=n;i++)
	{
		double x;
		x=1.0f/ama(i);
		e+=x;
	}
	printf("the value of e is:%lf",e);
}
