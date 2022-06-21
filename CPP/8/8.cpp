#include<iostream>
using namespace std;
void main()
{
	int x,y,n;
	x=y=1;
	n=--x&&++y;
	cout<<"n="<<n<<"y="<<y<<endl;
	n=(--x)||(++y);
	cout<<n<<endl;
	cout<<"x="<<x<<"y="<<y<<endl;
}