#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	if((n-m)%k!=0 || (n-m)==0)
	printf("UnHappy£¡");
	else if((n-m)%k==0)
	printf("Happy!");
	return 0;
}
