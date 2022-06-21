#include<iostream.h>
int main()
{
	int a,q,n,sum;
	a=1;q=2;n=sum=0;
	do {
		sum=sum+a;
		++n;
		a=a*q;
	}while(sum<100);
	--n;
	cout<<n<<endl;
	return 0;
}