#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int judge(int a[],int b[]);//判断谁更大，lcy在前，ypop在后，每次一份,直接输出
int find(int a[]);//找到对子中一样的部分?
int judge_pri(int a);//判断骰子点数优先级，高优先级，数字大
int judge_type(int a[]);//判断骰子数种类，豹子1，对子2，点子3 每次一份

int judge_type(int a[])//判断骰子数种类，豹子1，对子2，点子3 每次一份
{
	if(a[1]==a[2] && a[2]==a[3])
	{
		return 1;
	}
	if(a[1]==a[2] || a[1]==a[3] || a[2]==a[3])
	{
		return 2;
	}
	return 3;
}

int judge_pri(int a)//判断骰子点数优先级，高优先级，数字大
{
	switch(a)
	{
		case 1:return 6;
		case 6:return 5;
		case 5:return 4;
		case 4:return 3;
		case 3:return 2;
		case 2:return 1;
	}
}

int find(int a[])//找到对子中一样的部分?
{
	if(a[1]==a[2])
	return a[1];
	if(a[1]==a[3])
	return a[1];
	if(a[2]==a[3])
	return a[2];
}

int judge(int a[],int b[])//判断谁更大，lcy在前，ypop在后，每次一份,直接输出
{
	if(a[0]<b[0])//豹子，对子，点子依次减小 
	{
		printf("lcy\n");
		return 0;
	}
	if(a[0]>b[0])
	{
		printf("Ypop\n");
		return 0;
	}
	
	if(a[0]==b[0] && a[0]==1)//豹子
	{
		if( judge_pri(a[1]) > judge_pri(b[1]) )
		{
			printf("lcy\n");
	    	return 0;
		}
		else
		{
			printf("Ypop\n");
		    return 0;
		}
	}
	
	if(a[0]==b[0] && a[0]==2)//对子
	{
		if( judge_pri( find(a) ) > judge_pri( find (b) ) )
		{
			printf("lcy\n");
	    	return 0;
		}
		else
		{
			printf("Ypop\n");
		    return 0;
		}
	}
	
	if(a[0]==b[0] && a[0]==3)//点子
	{
		if(a[1]+a[2]+a[3] > b[1]+b[2]+b[3])
		{
			printf("lcy\n");
	    	return 0;
		}
		if(a[1]+a[2]+a[3] < b[1]+b[2]+b[3])
		{
			printf("Ypop\n");
		    return 0;
		}
		if(a[1]+a[2]+a[3] == b[1]+b[2]+b[3])
		{
			printf("Draw\n");//一样大
        	return 0;
	    }
	}
}

int main(int argc, char *argv[]) {
	int lcy[1000][4],ypop[1000][4];
	int times_k;
	
	scanf("%d",&times_k);
	for(int i=1;i<=times_k;i++)
	{
		for(int j=1;j<=3;j++)//input lcy
		{
			scanf("%d",&lcy[i][j]);
		}
		for(int j=1;j<=3;j++)//input ypop
		{
			scanf("%d",&ypop[i][j]);
		}
	}
	
	for(int i=1;i<=times_k;i++)
	{
		lcy[i][0]=judge_type(lcy[i]);
		ypop[i][0]=judge_type(ypop[i]);
	}
	
	for(int i=1;i<=times_k;i++)
	{
		judge( lcy[i] , ypop[i] );
	}

	return 0;
}
