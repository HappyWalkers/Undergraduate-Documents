// 5-3a的n次幂除以前n个正整数之和.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
double f(float a,int n)
{double s=0;
if(n<0) cout<<"n<0,输入错误！"<<endl;
else if(n==0) s=1;
else s=a*f(a,n-1);
return(s);
}
double g(int n)
{double s=0;int i;
for(i=1;i<=n;i++)
	s=s+i;
return(s);
}
void main()
{
	float a;
	int n;
	a=2;n=0.5;
	cout<<"请输入一个实数a和一个整数n：";
	cin>>a>>n;
	cout<<"a的n次幂/(1+2+3+...+n)="<<f(a,n)/g(n)<<endl;
}