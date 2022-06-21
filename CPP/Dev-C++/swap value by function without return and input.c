#include <stdio.h>
#include <stdlib.h>
int x=0;
void add()
{
	x++;
}
int main(int argc, char *argv[]) {
	printf("x=%d\n",x);
	x++;
	printf("x=%d\n",x);
	add();
	printf("x=%d\n",x);
	return 0;
}
