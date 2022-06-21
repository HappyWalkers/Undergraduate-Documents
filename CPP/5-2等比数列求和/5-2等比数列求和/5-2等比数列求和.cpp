// 5-2等比数列求和.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
double f(float a,float q,int n)
{
	double s=0,ai=a;
	int i;
	for(i=1;i<=n;)
	{s=s+ai;i++;ai=ai*q;}
	return (s);
}
void main()
{float a,q;
int n;
a=1;q=0.5;
cout<<"请输入一个整数n:";
cin>>n;
cout<<"级数的和为："<<f(a,q,n)<<endl;
cout<<"表达式a/(1-q)的值为："<<a/(1-q)<<endl;
}