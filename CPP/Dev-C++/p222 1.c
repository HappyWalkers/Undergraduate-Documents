#include <stdio.h>
#include <stdlib.h>
int main()
{
	char a[100][20]={0};
	int i=0;
	do
	{
		printf("Enter word: ");
		gets(a[i]);
		i++;
	}while(strlen(a[i-1])!=4);
	
	char* min=a[0];
	char* max=a[0];
	
	for(int i=0;i<=99;i++)
	{
		if(strlen(a[i])==0)break;
		if(strcmp(a[i],min)<0)min=a[i];
		if(strcmp(a[i],max)>0)max=a[i];
	}
	
	printf("Smallest word: ");
	printf("%s\n",min);
	
	printf("Largest word: ");
	printf("%s",max);
}
