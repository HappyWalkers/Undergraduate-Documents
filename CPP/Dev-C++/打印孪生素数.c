#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	printf("please enter a begining number and a ending number:");
	long beg,end;
	scanf("%ld%ld",&beg,&end);
//	printf("%ld%ld",beg,end);
	if(beg>end)
	{
		long x=beg;
		beg=end;
		end=x;
	}
//	printf("%ld%ld",beg,end);
	long t=0; 
	int flag=1;
	long m;
	long pri=0;
	for(t=beg;t<=end;t++)
	{
		for(pri=2;pri<=(long)sqrt(t);pri++)
		{
			m=t/pri;
			printf("%ld %ld %ld\n",t,pri,m);
			if(t==pri*m)
			{
				flag=0;
				break;
			}
		}
		
		if(flag==0) 
		{
//			printf("%ld %ld %ld\n",t,pri,m);
		    continue;	
    	}
		else
		{
//			printf("%d",flag);
//			printf("%ld %ld %ld\n",t,pri,m);
		    for(pri=2;pri<=(int)sqrt(t+2);pri++)
		{
			m=(t+2)/pri;
			if((t+2)==pri*m)
			{
				flag=0;
				break;
			}
		}
		if(flag==0)
		{
		continue;
	    }
		if(t==1)
		{
		continue;
	    }
		printf("%ld %ld\n",t,t+2);
    	}
    	
	}
	return 0;
}
