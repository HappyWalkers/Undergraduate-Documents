#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int x,flag=0;
	int a[5]={0};
	scanf("%d",&x);
	if(x%3==0)
	{
		a[1]=3;
	}
	if(x%5==0)
	{
		a[2]=5;
	}
	if(x%8==0)
	{
		a[3]=8;
	}
	if(x%11==0)
	{
		a[4]=11;
	}
	for(int i=1;i<=4;i++)
	{
		if(a[i]!=0)flag=1;
	}
	if(flag==1)
	{
		printf("Yes\n");
		for(int i=1;i<=4;i++)
		{
			if(a[i]!=0)
			printf("%d ",a[i]);
		}
	}
	else
	{
		printf("No");
	}
	return 0;
}
