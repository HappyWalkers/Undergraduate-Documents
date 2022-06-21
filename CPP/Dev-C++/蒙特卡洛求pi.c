#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main()
{
	srand((unsigned int)time(NULL));
    long long m=0;
    long long n=100000000; //1ww
    double x,y,pi;
    long long i; 
    for(i=0; i<n;i++)
    {
        x = 1.0*rand()/RAND_MAX;
        y =1.0*rand()/RAND_MAX;
        if( (x*x+y*y)<=1.0)
        {
            m++;
        }
    }
    pi = 4.0*m/n;
    return  pi;
}
