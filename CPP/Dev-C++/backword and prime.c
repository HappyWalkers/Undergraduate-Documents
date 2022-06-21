#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int is_prime(int x)
{
	if(x==1)return 0;
	for(int i=2;i<=sqrt(x);i++)
	{
		if(x%i==0)
		return 0;
	}
	return 1;
}

int is_backword(int x)
{
	int i=0;
	int a[10];
	while(1)
	{
		a[++i]=x%10;
		x=x/10;
		if(x==0)break;
	}
	int c=i;
	for(int j=1;j<=i;)
	{
		if(a[j++]!=a[c--])
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int l,r;
	int cnt=0;
	scanf("%d%d",&l,&r);
	for(int i=l;i<=r;i++)
	{
		if(is_prime(i) && is_backword(i))
		cnt++;
	}
	printf("%d",cnt);
	return 0;
}
