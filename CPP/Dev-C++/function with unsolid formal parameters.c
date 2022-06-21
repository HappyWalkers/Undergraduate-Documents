#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int sum(int cnt,...)
{
	int sum=0;
	va_list a;
	va_start(a,cnt);
	for(;cnt;--cnt)
	{
	sum=sum+va_arg(a,int);
	}
	va_end(a);
	return sum;
}

int main()
{
	printf("sum: %d",sum(3,1,2,3));
	return 0;
}
