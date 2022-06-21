#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("Enter a string composed of int: ");
	char a[100];
	scanf("%s",a);
	
	printf("the number of the string is: ");
	for(int i=0;;i++)
	{
		if(a[i]=='\0')break;
		printf("%d",a[i]-'0');
	}
}
