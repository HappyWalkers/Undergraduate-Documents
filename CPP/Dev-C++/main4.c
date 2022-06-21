#include<stdio.h>
int main()
{
	int x;
	printf("please enter the amount of money:");
	scanf("%d",&x);
	int a,b,c,d;
	a=x/20;
	x=x-a*20;
	b=x/10;
	x=x-b*10;
	c=x/5;
	x=x-c*5;
	d=x;
	printf("$20 bills:%d\n",a);
	printf("$10 bills:%d\n",b);
	printf("$5 bills:%d\n",c);
	printf("$10 bills:%d\n",d);
}
