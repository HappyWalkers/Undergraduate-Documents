#include<stdio.h> 
int main(void)
{
	int h,l,w;
	double v,wei;
	h=8;
	l=12;
	w=10;
	v=h*l*w;
	wei=ceil(v/166);
	printf("Dimensions: %d%d%d\n",l,w,h);
	printf("Volumr(cubic inches): %lf\n",v);
	printf("Dimensional weight (pounds): %lf\n",wei);
	return 0;
}
