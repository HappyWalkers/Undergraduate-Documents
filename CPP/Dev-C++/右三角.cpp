#include<stdio.h>
int main()
{
    for(int i=1;i<=3;i++)
    {
    for(int j=1;j<=2*i-1;j++)
    printf("*");
    printf("\n");
    }
    for(int i=1;i<=2;i++)
    {
    for(int j=3;j>=i*2-1;j--)
    printf("*");
    printf("\n");
    }
}

