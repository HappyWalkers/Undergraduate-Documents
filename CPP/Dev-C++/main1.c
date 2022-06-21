#include<stdio.h>
#define FACTOR (9.0f/5.0f) 
#define FREEZING 32.0f
int main()
{
	float f,c;
	printf("enter celsius temperature: ");
	scanf("%f",&c);
	f=c*FACTOR+FREEZING;
	printf("fahrenheit equivalent: %.1f\n",f);
	return 0;
}
