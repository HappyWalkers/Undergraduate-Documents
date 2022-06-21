#include<stdio.h>
int main()
{
	printf("enter a number of three digit:");
	int x;
	scanf("%d",&x);
	int a[4];
	for(int i=1;i<=3;i++)
	{
		a[i]=x%10;
		x=x/10;
	}
	printf("the answer is:%d",a[1]+a[2]+a[3]);
	return 0;
}
