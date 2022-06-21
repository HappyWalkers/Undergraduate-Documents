#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
int main()
{
	char a[100]={0};
	printf("Enter first word: ");
	gets(a);
	int b[100]={0};
	
	for(int i=0;i<=99;i++)//transform to ascii
	{
		b[i]=tolower(a[i]);
	}
	
	printf("Enter second word: ");
	char c[100]={0};
	gets(c);
	int d[100]={0};
	
	for(int i=0;i<=99;i++)//transform to ascii
	{
		d[i]=tolower(c[i]);
	}
	
	for(int i=0;i<=99;i++)//compare b and d
	{
		for(int j=0;j<=99;j++)
		{
			if(b[i]==d[j])
			{
				d[j]=0;
				break;
			}
		}
	}
	
	int count=0;//judge
	for(int i=0;i<=99;i++)
	{
		if(d[i]==0)count++;
	}
	if(count==100)printf("The words are anagrama");
	else printf("The words are not anagram");
}
