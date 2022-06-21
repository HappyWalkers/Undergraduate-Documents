#include <stdio.h>
int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,0};
	int j=9,i=0;
	while(1)
	{
		if(j<=i)break;
		int temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		i++;
		j--;
	}
	for(int i=0;i<10;i++)
	{
		printf("%d",a[i]);
	}
	return 0;
}
