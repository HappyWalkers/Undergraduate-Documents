#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	printf("Enter a positive number: ");
	double dest=0;
	scanf("%lf",&dest);
	
	double guess=1;
	double ans=1;
	for(int i=1;;i++)
	{
		guess=ans;
		ans=(guess+dest/guess)/2;
		if(fabs(guess-ans)<0.00001*guess)
		{
			printf("Square root: ");
			printf("%lf",ans);
			break;
		}
	}
}
