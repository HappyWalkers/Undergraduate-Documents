#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	wchar_t a[5];
//	setlocale(LC_ALL,"zh_CN");
//	wscanf(L"%s",a);
	gets(a);
	puts(a);
	wprintf(L"%c",a[0]);
//	for( int i=0;i<5;i++)
//	{
////		printf("%c",a[i]);
//		wprintf(L"%c",a[i]);
////		if(a[i]=='กฎ' || a[i]=='กฎ')printf("there is a flag");
//	}
	
//	char a[10]={0};
//	gets(a);
////	printf("%c%c",a[0],a[1]);
////	printf("%c%c",a[0],a[1]);
//	
////	puts(a);
////	for(int i=0;i<10;i++)
////	{
////		printf("%c",a[i]);
////	}
//	for(int i=0;i<10;i=i+2)
//	{
//		if((a[i],a[i+1])=='กฎ' || (a[i],a[i+1])=='กฏ')printf("there is a flag\n");
//	}
	return 0;
}
