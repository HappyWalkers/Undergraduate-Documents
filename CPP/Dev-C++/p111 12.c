#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("Enter an expression: ");
	
	double a[100]={0};
	char b[100]={0};
	int i=0;
	for(i=1;;i++)//get the value or control of expression
	{
		scanf("%lf",&a[i]);
		scanf("%c",&b[i]);
		if(b[i]=='\n')
		{
			break;
		}
	}
	
	for(int j=1;j<=i;j++)//calculate the value of experssion
	{
		if(b[j]=='+')
		{
			a[j+1]=a[j]+a[j+1];
		}
		
		if(b[j]=='-')
		{
			a[j+1]=a[j]-a[j+1];
		}
		
		if(b[j]=='*')
		{
			a[j+1]=a[j]*a[j+1];
		}
		
		if(b[j]=='/')
		{
			a[j+1]=a[j]/a[j+1];
		}
		
		if(b[j]=='\n')
		{
			printf("Value of expression: ");
			printf("%g",a[j]);
			return 0;
		}
	}
}
