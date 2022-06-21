#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int judge(int a[],int b[]);//ÅĞ¶ÏË­¸ü´ó£¬lcyÔÚÇ°£¬ypopÔÚºó£¬Ã¿´ÎÒ»·İ,Ö±½ÓÊä³ö
int find(int a[]);//ÕÒµ½¶Ô×ÓÖĞÒ»ÑùµÄ²¿·Ö¡
int judge_pri(int a);//ÅĞ¶Ï÷»×ÓµãÊıÓÅÏÈ¼¶£¬¸ßÓÅÏÈ¼¶£¬Êı×Ö´ó
int judge_type(int a[]);//ÅĞ¶Ï÷»×ÓÊıÖÖÀà£¬±ª×Ó1£¬¶Ô×Ó2£¬µã×Ó3 Ã¿´ÎÒ»·İ

int judge_type(int a[])//ÅĞ¶Ï÷»×ÓÊıÖÖÀà£¬±ª×Ó1£¬¶Ô×Ó2£¬µã×Ó3 Ã¿´ÎÒ»·İ
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

int judge_pri(int a)//ÅĞ¶Ï÷»×ÓµãÊıÓÅÏÈ¼¶£¬¸ßÓÅÏÈ¼¶£¬Êı×Ö´ó
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

int find(int a[])//ÕÒµ½¶Ô×ÓÖĞÒ»ÑùµÄ²¿·Ö¡
{
	if(a[1]==a[2])
	return a[1];
	if(a[1]==a[3])
	return a[1];
	if(a[2]==a[3])
	return a[2];
}

int judge(int a[],int b[])//ÅĞ¶ÏË­¸ü´ó£¬lcyÔÚÇ°£¬ypopÔÚºó£¬Ã¿´ÎÒ»·İ,Ö±½ÓÊä³ö
{
	if(a[0]<b[0])//±ª×Ó£¬¶Ô×Ó£¬µã×ÓÒÀ´Î¼õĞ¡ 
	{
		printf("lcy\n");
		return 0;
	}
	if(a[0]>b[0])
	{
		printf("Ypop\n");
		return 0;
	}
	
	if(a[0]==b[0] && a[0]==1)//±ª×Ó
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
	
	if(a[0]==b[0] && a[0]==2)//¶Ô×Ó
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
	
	if(a[0]==b[0] && a[0]==3)//µã×Ó
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
			printf("Draw\n");//Ò»Ñù´ó
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
