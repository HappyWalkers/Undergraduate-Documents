#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

char* inv(char* mes)//inverse the array
{
	int cnt=0;
	char inv_mes[100];
	for(int i=0;i<100;i++)
	{
		if(mes[i]!=0)cnt++;
	}
	
	int i=0;
	do
	{
		inv_mes[i++]=mes[--cnt];
	}while(cnt!=0);
	return inv_mes;
}

int judge(char *mes)//judge
{
	if(strcmp(mes,inv(mes)))
	return 0;
	else
	return 1;
}

int main(int argc, char *argv[]) {
	printf("Enter a message: ");//input
	char mes[100]={0};
	char exp[100]={0};
	gets(exp);
//	puts(exp);

    int i=0,j=0;
	while(1)//find char
	{
		if(exp[i]>='a' && exp[i]<='z')
    	{
            mes[j++]=exp[i];
       	}
       	
       	else if(exp[i]>='A' && exp[i]<='Z')
       	{
 //    		putchar(exp[i]);
       		exp[i]=tolower(exp[i]);
 //    		putchar(exp[i]);
       		mes[j++]=exp[i];
        }
        i++;
        
        if(exp[i]==0)
        break;
	}
	
	puts(mes);
	
	int a=judge(mes);//judge if huiwen or not
	if(1==a)printf("Palindrome");
	if(0==a)printf("Not a palindrome");
	return 0;
}
