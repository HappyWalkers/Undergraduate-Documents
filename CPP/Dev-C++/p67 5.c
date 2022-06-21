#include<stdio.h>
int main()
{
	float m;
	scanf("%f",&m);
	if(m<=750)printf("%f",m/100);
	else if(m<=2250)printf("%f",7.50+(m-750.0)*(1.0f/100.0f));
	else if(m<=3750)printf("%f",37.50+(m-2250.0)*(3.0f/100.0f));
	else if(m<=5250)printf("%f",82.50+(m-3750.0)*(4.0f/100.0f));
	else if(m<=7000)printf("%f",142.50+(m-5250.0)*(5.0f/100.0f));
	else printf("%f",230.00+(m-7000.0)*(6.0f/100.0f));
	return 0;
}
