#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n=1;
    float HalfPi = 1.0+ 1.0/(4.0*n*n-1.0);
    // 1+1/(4n^2-1)
    float tmp=1.0;
    do
    {
        n++;
        tmp=1.0/(4.0*n*n-1.0);
        HalfPi *=(1.0+tmp);
    } while ( tmp>1e-6);
    return 2.0*HalfPi;
}
