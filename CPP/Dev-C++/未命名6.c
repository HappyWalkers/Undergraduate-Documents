#include<stdio.h>
int find(int i,int a[100])
{
	int j;
	int t=0;
	for(j=1;j<i;j++)
	{
		if(i%j==0)
		{
			a[t++]=j;
		}
	}
	return a[100];
}
int main()
{
	int i=100;
	int a[100];
	a[100]=find(i,a[100]);
	printf("%d",a[0]);
}
