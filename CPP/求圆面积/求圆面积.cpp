//*****ex1 1.cpp*****
#define PI 3.14159
#include<iostream>
using namespace std;
float sum(float x);
void main()
{
	float r,s;
	cout<<"input r:";
	cin>>r;
	s=sum(r);
	cout<<"r="<<r<<" "<<"s="<<s<<endl;

}
float sum(float x)
{
	return PI*x*x;
}
