#include <stdio.h>
#include <stdlib.h>
int main()//reverse a sentence
{
	printf("Enter a sentence:");
	char a[100];
	gets(a);
	char end; //get the end of a sentence
	int i=0;
	do
	{ 
		if(a[i]=='.' || a[i]=='?' || a[i]=='!')
		{
			end=a[i];
			break;
		}
		i++;
	}while(1);
	printf("Reversal of sentence: ");//ex
	
	int loca;//get the location of the ' '
	int p;//get the location of the last ' '
	for(int j=i;j>=0;j--)//reverse the sentence
	{
		if(a[j]==' ')
		{
			loca=j;
    	p=0;
		do
		{
			printf("%c",a[++loca]);
			p++;
		}while(a[loca+1]!=' ' && a[loca+1]!='?');
		printf(" ");
		}
	}
	int lastone=0;
	do
		{
			printf("%c",a[lastone++]);
		}while(lastone!=loca-p);
	printf("%c",end);
}
