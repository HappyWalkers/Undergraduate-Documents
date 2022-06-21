#include <stdio.h>
#include <stdlib.h>
#include<math.h>
double fun(double x)
{
	return x*x*x-3.0*x+1.0;
}

double dfun(double x)
{
	return 3.0*x*x-3.0;
}

int main()
{
	double x=0,x0=0;
	do
	{
		x0=x;
		x=x0-fun(x)/dfun(x);
//		printf("%lf\n",x);
	}while(fabs(x-x0)>=1e-5);
	printf("数值解为：%lf",x);
}
