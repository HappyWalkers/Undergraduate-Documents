#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int judge(int a[],int b[]);//�ж�˭����lcy��ǰ��ypop�ں�ÿ��һ��,ֱ�����
int find(int a[]);//�ҵ�������һ���Ĳ��֡
int judge_pri(int a);//�ж����ӵ������ȼ��������ȼ������ִ�
int judge_type(int a[]);//�ж����������࣬����1������2������3 ÿ��һ��

int judge_type(int a[])//�ж����������࣬����1������2������3 ÿ��һ��
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

int judge_pri(int a)//�ж����ӵ������ȼ��������ȼ������ִ�
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

int find(int a[])//�ҵ�������һ���Ĳ��֡
{
	if(a[1]==a[2])
	return a[1];
	if(a[1]==a[3])
	return a[1];
	if(a[2]==a[3])
	return a[2];
}

int judge(int a[],int b[])//�ж�˭����lcy��ǰ��ypop�ں�ÿ��һ��,ֱ�����
{
	if(a[0]<b[0])//���ӣ����ӣ��������μ�С 
	{
		printf("lcy\n");
		return 0;
	}
	if(a[0]>b[0])
	{
		printf("Ypop\n");
		return 0;
	}
	
	if(a[0]==b[0] && a[0]==1)//����
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
	
	if(a[0]==b[0] && a[0]==2)//����
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
	
	if(a[0]==b[0] && a[0]==3)//����
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
			printf("Draw\n");//һ����
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
