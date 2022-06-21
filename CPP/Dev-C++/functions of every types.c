#include <stdio.h>
#include <stdlib.h>

void f1()
{
	printf("this is a function without return and input\n");
}

void f2(int x)
{
	printf("this is the answer of a function without return: %d\n",x++);
}

int f3()
{
	return 3;
}

int f4(int x)
{
	return x++;
}

int main()
{
	f1();
	f2(1);
	printf("%d\n",f3());
	printf("%d\n",f4(3));
}
