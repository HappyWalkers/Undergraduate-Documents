#include <stdio.h>
int main()
{
	long long j;
	printf("please input a number:");
	scanf("%lld",&j);
	int i;
	for( i=2;i<=(int)sqrt(j);i++)
	{
	int x=j/i;
	if(j==x*i)
	{
	printf("this number is not a prime number");
	return 0;
	}
}
printf("this number is a prime number");
}
