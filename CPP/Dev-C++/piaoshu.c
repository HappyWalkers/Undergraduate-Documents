#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int nth[1000]={0};
	char a;
	for(int i=0;i<1000;i++)
   	{
    	if((a=getchar())=='\n')break;
    	char exp[20]={0};
    	gets(exp);
    	char des[20]={0};
    	des[0]=a;
    	strcat(des,exp);
    	nth[i]=atoi(des);
   	}

//	for(int i=0;i<1000;i++)
//	{
//		if(nth[i]==0)break;
//		printf("%d\n",nth[i]);
//	}
	return 0;
}
