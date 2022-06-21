#include<stdio.h>
int main()
{
	printf("Enter a number between 0 and 32767:");
	int x;
	scanf("%d", &x);
	int a[6];
	for (int i = 1; i <= 5; i++)
	{
		a[i] = x % 8;
		x = x / 8;
	}
	int t = a[1] + a[2] * 10 + a[3] * 100 + a[4] * 1000 + a[5] * 10000;
	if (t >= 10000)
		printf("In octal,your number is:%5d",t);
	else
		printf("In octal,your number is:0%-5d",t);
	return 0;
}
