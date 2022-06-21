#include <stdio.h>
#include <stdlib.h>
int main()
{
	double QuarterPi=0;
    int n=1;
    double tmp;
    do
    {
        tmp = 1.0/(2.0*n-1);
        if(n%2==0)
            tmp=tmp*(-1.0);
        QuarterPi+=tmp;
        n++;
    }while ( fabs(tmp)> 1e-6);
    return 4.0*QuarterPi;
}
