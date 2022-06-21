#include <stdio.h>
/*void swap(int* a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
*/
int findsum(int i,int* a)
{
	int j;
	int t=0;
	int x=0;
	for(j=1;j<i;j++)
	{
		if(i%j==0)
		{
			a[t++]=j;
			x+=a[t-1];
		}
	}
	return x;
}

/*int sum(int a[100])
{
	int i;
	int x=0;
	for(i=0;i<100;i++)
	{
		x+=a[i];
	}
	return x;
	printf("%d",x);
}*/

int main()
{
	printf("enter a initial number and a ending number:");
	int init,end;
	scanf("%d%d",&init,&end);
//  printf("%d%d",init,end);
	if(init>end)
	{
		int x;
		x=init;
		init=end;
		end=x;
	}
//	printf("%d%d",init,end);
	int i;
	for(i=init;i<=end;i++)
	{
		int a[100];
//		printf("%d\n",a[1]);
//		printf("%d",a[2]);
//      printf("%d\n",sum(a));
//  	printf("%d",x);
		if(i==find(i,a))
		printf("%d\n",i);
	}
}


