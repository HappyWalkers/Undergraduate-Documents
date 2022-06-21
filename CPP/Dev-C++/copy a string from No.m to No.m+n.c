#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	printf("Enter a string: ");
	char des[100]={0};
	gets(des);
	
	printf("Enter m and n: ");
	int m,n;
	scanf("%d%d",&m,&n);
	
	printf("the copy of this string from No.m to No.m+n is: ");
	char *a=&des[m-1];
	for(int i=0;i<n;i++)
	{
		putchar(*(a+i));
    }
	return 0;
}
