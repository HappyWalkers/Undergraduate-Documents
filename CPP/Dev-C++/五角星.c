#include<stdio.h>
int main()
{
    int i,j;
     for(j=1;j<=7;j++)    //上三角形
     {
         
    for(i=23;i>=j;i--)
    {
        printf(" ");
    }
    
    
    for( i=1;i<=2*j-1;i++)
    {    
        printf("*");
    }
    
    printf("\n");
    }
    
    for(j=1;j<=4;j++)//中间四行
{
        for(i=1;i<=(j-1)*4;i++)
        printf(" ");
        
        for(i=47;i>=8*(j-1);i--)
        printf("*");
        
        printf("\n");
        }
        
        for(j=1;j<=2;j++)//之后两行
        {
            for(i=12;i>=j;i--)
            printf(" ");
            
            for(i=1;i<=23+2*(j-1);i++)
            printf("*");
            
            printf("\n");
        }
        
        for(i=1;i<=5;i++)//the last 5 lines
        {
            for(j=10;j>=i;j--)
            printf(" ");
            
            for(j=12;j>=3*(i-1);j--)
            printf("*");
            
            for(j=1;j<=1+8*(i-1);j++)
            printf(" ");
            
            for(j=12;j>=3*(i-1);j--)
            printf("*");
            
            printf("\n");
        }
    return 0;
}

