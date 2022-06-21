#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char str[100][10]={0};
	char sum[3];
	char exp;
	int flag=0;
	int result=0;
	scanf("%s",sum);
	
	for(int i=0;i<100;i++)
	{
		scanf("%s",str[i]);
		flag++;
		if(getchar()=='\n')break;
	}
	
	for(int i=0;i<flag;i++)
	{
		result+=atoi(str[i]);
	}
	
	printf("Total: %d",result);
}
