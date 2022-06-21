#include <stdio.h>
#include <stdlib.h>
#define V 1

//compare Input with location of every ball, same is one, different is zero
int find(double x, double *loc, int num, int i)
{
	for(int k=1;k<=100;k++)
	{
		if(k==i)continue;
		if(x==loc[k])return 1;
		if(k==num)return 0;
	}
	return 0;
}

int main()
{
	//get the n L t
	printf("Enter the number of ball,the length of line and the time after beginning: ");
	int num;
	double len;
	int t;
	scanf("%d %lf %d",&num,&len,&t);
	
	//get location of every ball
	printf("Enter the location of these balls:");
	double loc[101]={0};
	for(int i=1;i<=100;i++)
	{
		scanf("%lf",&loc[i]);
		if(i==num)break;
	}
	
	//calculate the location
	int v[101]={0};
	for(int i=1;i<=100;i++)//initialize v
	{
		v[i]=1;
		if(i==num)break;
	}
	
	for(int j=1;;j++)//timing 0.5s
	{
		for(int i=1;i<=100;i++)//location of every ball
    	{
		loc[i]=loc[i]+v[i]*0.5;
		if(i==num)break;
	    }
	    
	    for(int i=1;i<=100;i++)//v of every ball
	    {
	    if(loc[i]==0 || loc[i]==len)v[i]=-1*v[i];//change the v when crash the ends
		if(find(loc[i],loc,num,i))v[i]=-1*v[i];//change the v when crash the ball
		if(i==num)break;
		}
	    
	    if(j==t*2)//print the answer
		{
			for(int i=1;i<=100;i++)
        	{
	    	printf("%g ",loc[i]);
	    	if(i==num)break;
         	}
         	break;
		}
	}
}
