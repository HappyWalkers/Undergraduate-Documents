#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
    int x=0;
	char a[10];
	int first[4]={0};
	int second[4]={0};
	int cnt=0;
	int ans1[100]={0};
	int ans2[100]={0};

log:
	for(int i=1;i<=3;i++)//read char and trans to num
	{
	scanf("%s",a);
	if(strcmp(a,"one")==0)	first[i]=1;
	if(strcmp(a,"two")==0)	first[i]=2;
	if(strcmp(a,"three")==0)first[i]=3;
	if(strcmp(a,"four")==0)first[i]=4;
	if(strcmp(a,"five")==0)first[i]=5;
	if(strcmp(a,"six")==0)	first[i]=6;
	if(strcmp(a,"seven")==0)first[i]=7;
	if(strcmp(a,"eight")==0)first[i]=8;
	if(strcmp(a,"nine")==0)first[i]=9;
	if(strcmp(a,"zero")==0)first[i]=0;
	if(a[0]=='+') break;
	cnt++;
	}
	
	++x;
	for(int i=1;i<=cnt;i++)//calculate the first ans
	{
		ans1[x]+=first[i]*pow(10,cnt-i);
	}
	cnt=0;
	
	for(int i=1;i<=3;i++)//read char and trans to num
	{
	scanf("%s",a);
	if(strcmp(a,"one")==0)	second[i]=1;
	if(strcmp(a,"two")==0)	second[i]=2;
	if(strcmp(a,"three")==0)second[i]=3;
	if(strcmp(a,"four")==0)second[i]=4;
	if(strcmp(a,"five")==0)second[i]=5;
	if(strcmp(a,"six")==0)	second[i]=6;
	if(strcmp(a,"seven")==0)second[i]=7;
	if(strcmp(a,"eight")==0)second[i]=8;
	if(strcmp(a,"nine")==0)second[i]=9;
	if(strcmp(a,"zero")==0)second[i]=0;
	if(a[0]=='=') break;
	cnt++;
	}
	
	for(int i=1;i<=cnt;i++)//calculate the second ans
	{
		ans2[x]+=second[i]*pow(10,cnt-i);
	}
	
	if(!(ans1[x]==0 && ans2[x]==0))//loop,but output when meeting 0&0
	{
		cnt=0;
		goto log;
	}

	for(int i=1;i<=x;i++)
	{
		if(ans1[i]+ans2[i]!=0)
		printf("%d\n",ans1[i]+ans2[i]);
	}
	return 0;
}
