
// 5-5 完全数2-500.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
int is_complete(int x);
double sum(int n);
void main()
{
	int i;double s;
	for(i=2;i<=500;i++)
	if(is_complete(i)==1)
	{cout<<i<<endl;s=sum(i);}
	cout<<"【2，500】之内的完全数之和="<<s<<endl;
}
int is_complete(int x)
{int n,s;
s=1;
for(n=2;n<x;n++)
if(x%n==0)s=s+n;
if(x==s)return 1;
else return 0;
}
double sum(int n)
{static double s=0;
s=s+n;
return s;
}