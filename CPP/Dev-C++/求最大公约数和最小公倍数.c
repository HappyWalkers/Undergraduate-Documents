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
    printf("���Լ��Ϊ��%d",y);
	printf("��С��������%d",i*j/y);
}
