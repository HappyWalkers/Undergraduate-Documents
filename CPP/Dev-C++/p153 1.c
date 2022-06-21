#include <stdio.h>
#include <stdlib.h>

void show_array(int a[])
{
	int i;
	for(i=1;i<=10;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

void swit(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void selection_sort(int a[],int n)//a[] is the array waited for being sorted, n is the number of this array
{
	if(n==1)return;
	int max=1;//max is the logo of the max number in this array
	int i;
	for(i=1;i<=n;i++)
	{
		if(a[i]>a[max])
		{
			max=i;
			swit(&a[i],&a[max]);
		}
	}
	swit(&a[max],&a[n]);
	
	selection_sort(a,--n);
}
void main()
{
	printf("Enter 10 int numher for selection sort: ");
	
	int a[11];
	int i;
	for(i=1;i<=10;i++)
	{
		
		scanf("%d",&a[i]);
	}
	
	printf("the array before sort is: ");
	show_array(a);
	
	selection_sort(a,10);
	
	printf("the array after sort is: ");
	show_array(a);
}
