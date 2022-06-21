#include <stdio.h>
#include <stdlib.h>
#include<math.h>
double fun(double x)
{
	return x*x*x-3.0*x+1.0;
}

int main()
{
	double x1=-1.0;
	double x2=1.0;
	double x=0;
//	printf("%lf %lf %lf\n",x1,x2,x);
	do
    {
        x=(x1+x2)/2.0;
        if(fun(x)*fun(x2)>0)
        {
            x2=x;
 //  	printf("%lf %lf %lf\n",x1,x2,x);
        }
        else
        {
            x1=x;
    //	printf("%lf %lf %lf\n",x1,x2,x);
        }
 // 	printf("%lf %lf %lf\n",x1,x2,x);
    }while (fabs(x1-x2)>1e-6);
	printf("数值解为:%lf",x);
}
