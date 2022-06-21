#include <stdio.h>
int main()
{
	printf("Enter number of days in month:");
	int num;
	scanf("%d",&num);
	
	if(num<28 || num>31)
	{
		printf("error: number of days!");
		return 0;
	}
	
	printf("Enter starting day of the week(1=Sun,7=Sat):");
    unsigned int beg;
	scanf("%ud",&beg);
	
	if(beg>7 || beg==0)
	{
		printf("error: starting day!");
		return 0;
	}
	
	int i;
	for(i=1;i<beg;i++)
	{
		printf("\t");
	}
	
	for(i=1;i<=num;i++)
	{
		printf("%d\t",i);
		if(i==8-beg)printf("\n");
		if(i==15-beg)printf("\n");
		if(i==22-beg)printf("\n");
		if(i==29-beg)printf("\n");
	}
}
