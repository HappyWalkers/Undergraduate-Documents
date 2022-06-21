#include<stdio.h>
int main()
{
	int i,j; 
    for( i=1;i<=4;i++)
    {
        for( j=1;j<=i;j++)
        printf(" ");
        for(j=7;j>=2*i-1;j--)
        printf("*");
        printf("\n");
    }
}

