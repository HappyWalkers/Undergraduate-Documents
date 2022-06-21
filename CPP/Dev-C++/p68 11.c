#include <stdio.h>
int main()
{
	printf("please enter a number of two digit:");
	int x[3];
	int i;
	for(i=1;i<=2;i++)
	{
	scanf("%1d",&x[i]);
    }

	switch(x[1])
	{
	case 1:goto TAG1;
    case 2:printf("twenty-");goto TAG2;
    case 3:printf("thirty-");goto TAG2;
    case 4:printf("fourty-");goto TAG2;
    case 5:printf("fifty-");goto TAG2;
    case 6:printf("sixty-");goto TAG2;
    case 7:printf("seventy-");goto TAG2;
    case 8:printf("eighty-");goto TAG2;
    case 9:printf("ninety");goto TAG2;
    }
    
TAG1:
   	switch(x[2]){
    	case 1:printf("eleven");return 0;
		case 2:printf("twelve");return 0;
		case 3:printf("thirteen");return 0;
		case 4:printf("fourteen");return 0;
		case 5:printf("fifteen");return 0;
		case 6:printf("sixteen");return 0;
		case 7:printf("seventeen");return 0;
		case 8:printf("eighteen");return 0;
		case 9:printf("nineteen");return 0;
	}
	
TAG2:
	switch(x[2]){
		case 1:printf("one");break;
		case 2:printf("two");break;
		case 3:printf("three");break;
		case 4:printf("four");break;
		case 5:printf("five");break;
		case 6:printf("six");break;
		case 7:printf("seven");break;
		case 8:printf("eight");break;
		case 9:printf("nine");break;
	}
}
