#include<stdio.h>
int main()
{
	int i; 
	int j;
    for(i=1;i<=3;i++)
    {
    for( j=4;j>=2*i-1;j--)
    printf(" ");
    for( j=1;j<=2*i-1;j++)
    printf("*");
    printf("\n");
    }
    
    for( i=1;i<=2;i++)
    {
        for( j=1;j<=2*i;j++)
        printf(" ");
        for( j=3;j>=2*i-1;j--)
        printf("*");
        printf("\n");
    }
}

