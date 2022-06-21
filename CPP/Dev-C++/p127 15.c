#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("Enter message to be encrypted: ");
	char a[100];
	gets(a);

	printf("Enter shift amount (1-25): ");
	int amo;
	scanf("%d",&amo);

	char b[100]={0};
	for(int i=0;i<=99;i++)
	{
		if(a[i]>=90-amo+1 && a[i]<=90)b[i]=a[i]-26+amo;//up
		else if(a[i]>=122-amo+1 && a[i]<=122)b[i]=a[i]-26+amo;
		else if(a[i]>=65 && a[i]<90-amo+1)b[i]=a[i]+amo;
		else if(a[i]>=97 && a[i]<122-amo+1)b[i]=a[i]+amo;
		else b[i]=a[i];
	}
	
	printf("Encrypted message: ");
	puts(b);
}
