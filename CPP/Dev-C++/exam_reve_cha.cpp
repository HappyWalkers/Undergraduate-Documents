#include <stdio.h>
#include <stdlib.h>
int main()
{
	char a[10]="abcdefghi";
	int i=0,j=8;//a[9]='/0'
	while(1)
	{
		if(j<=i)break;
		char temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		i++;
		j--;
	}
	puts(a);
}
