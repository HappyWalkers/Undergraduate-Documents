#include <stdio.h>
#include <stdlib.h>
int IsPrime(int num)
{
    if(num<3)
        return 0;
    int i;
    for (i=2; i<=num-1; i++)
    {
        if(num%i==0)
            return 0;
    }
    return 1;
}

void PrintAllTwinPrimes(int start, int end)
{
    int min = start>end?  end:start;
    int max = start>end?  start:end;
    int i;
    for ( i=min; i<max; i++)
    {
        if(IsPrime(i) && IsPrime(i+2))
        {
            printf("%d,%d\n",i,i+2);
        }
    }
}

int main()
{
	printf("please enter a begining number and a ending number:");
	int beg,end;
	scanf("%d%d",&beg,&end);
	PrintAllTwinPrimes(beg,end);
}
