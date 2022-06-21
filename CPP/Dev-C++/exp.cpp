#include <stdio.h>
#include <stdlib.h>
int main()
{
    short x=0x0809;
    short y=0x9080;
    short z=x|y;
    
    char a[100];
    char b[100];
    char c[100];
    
    itoa(x,a,2);
    itoa(y,b,2);
    itoa(z,c,2);
    
    printf("x=%s\n",a);
    printf("y=%s\n",b);
    printf("z=%s\n",c);
    printf("z>0?%d",z>0);
}
