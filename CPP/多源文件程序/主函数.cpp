#include <iostream>
using namespace std;
extern int n;
extern double f(int n);
void main()
{
	double s;int n;
	cout<<"please input interger n:";
	cin>>n;
	s=f(n);
	cout<<"s="<<s<<endl;
}