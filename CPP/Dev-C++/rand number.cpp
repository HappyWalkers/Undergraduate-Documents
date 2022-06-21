#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	srand((unsigned)time(NULL));
	for(int i=1;i<=5;i++)
      {
      	for(int j=1;j<=5;j++)
      	{
      		printf("%d\t",rand()%100);
		}
		printf("\n");
	  }
}
