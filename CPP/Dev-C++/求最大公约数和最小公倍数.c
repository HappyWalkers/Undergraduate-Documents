#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("please enter two number:");
	int i,j;
	scanf("%d%d",&i,&j);
	if(i>j)
	{
		int t=i;
		i=j;
		j=t;
	}
	int m;
	int x=i,y=j;
    do
    {
        m=y%x;
    	y=x;
    	x=m;
	}while(m!=0);
    printf("最大公约数为：%d",y);
	printf("最小公倍数：%d",i*j/y);
}
