#include<stdio.h>  


int main()
{
    int weight[]={1,2,3,5,10,20};
    int num[6];
    scanf("%d%d%d%d%d%d",num,num+1,num+2,num+3,num+4,num+5); 
	     
    int i,j,k;
    int flag[1001]={0};
    int current=0;  
	flag[0]=1;
	
	for(i=0;i<6;i++)
	{ 
		for(j=1;j<=num[i];j++){ 
			for(k=0;k<=current;k++)
			{
				if(flag[k]==1)
				{
					flag[k+j*weight[i]]=1;
				}
			} 
		} 
		current+=num[i]*weight[i];
	}
     
    int cnt=0;
    for(i=1;i<1001;i++){
    	if(flag[i]){
    		cnt++;
		}
	} 
	
	printf("Total=%d\n",cnt);
	 
    return 0; 
} 
c
