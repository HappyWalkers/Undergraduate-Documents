#include <stdio.h>
#include <stdlib.h>
void BubbleSort(int a[], int len)
{
	for(int i=0;i<=len;i++)
	{
		for(int j=i+1;j<len;j++)
		{
			if(a[i]>a[j])
			{
				int x=a[i];
				a[i]=a[j];
				a[j]=x;
			}
		}
	}
}

void main()
{
	int a[10]={10,9,8,7,6,5,4,3,2,1};
	printf("the array before sort is:");
	for(int i=0;i<=9;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n");
	
	BubbleSort(a,10);
	
	printf("the array after sort is:");
	for(int i=0;i<=9;i++)
	{
		printf("%d",a[i]);
	}
}
