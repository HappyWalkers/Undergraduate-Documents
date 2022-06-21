#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	printf("please input two number:");
	long i,j;
	scanf("%ld%ld",&i,&j);
	if(i>j)
	{
		long t=i;
		i=j;
		j=t;
	}
	
	int t=0;
	long x,y;
	long a[100],b[100],c[100],d[100];
	for(x=1;x<=(long)sqrt(i*j);x++)
	{
		y=i*j/x;
		if((i*j)%y!=0)
		{
			continue;
		}
//	printf("%d\n",t);
		a[++t]=x;
		c[t]=x;
		b[t]=y;
		d[t]=y;
	}
//	int u;
//	for(u=1;u<=100;u++)
//	printf("%ld %ld\n",a[u],b[u]);
	int m,n;
	int num=0;
	for(m=1;m<=t;m++)
	{
		do
		{
		    n=b[m]%a[m];
			b[m]=a[m];
			a[m]=n;
		}while(n!=0);
		if(b[m]==i)
		{
		num++;
         printf("以%ld，%ld为最大公约数和最小公倍数的两个数分别为：%ld,%ld\n",i,j,c[m],d[m]);
     }
	}
	printf("共有情况%d种",num);
}
