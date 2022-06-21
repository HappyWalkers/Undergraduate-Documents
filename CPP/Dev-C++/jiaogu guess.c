#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int ji(int x)
{
	return 3*x+1;
}

int ou(int x)
{
	return x/2;
}

int main(int argc, char *argv[]) {
	int x;
	scanf("%d",&x);
	int flag=0;
	while(1)
	{
		if(x%2==1)
		{
			printf("%d ",x);
			flag=1;
		}
		if(x%2==1)
		{
			x=ji(x);
		}
		else
		{
			x=ou(x);
		}
		if(x==1)
		break;
	}
	if(flag==0)printf("No number can be output !");
	return 0;
}
