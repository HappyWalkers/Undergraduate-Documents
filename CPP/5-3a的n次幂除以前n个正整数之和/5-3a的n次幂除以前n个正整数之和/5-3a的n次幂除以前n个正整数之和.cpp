// 5-3a��n���ݳ���ǰn��������֮��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
double f(float a,int n)
{double s=0;
if(n<0) cout<<"n<0,�������"<<endl;
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
	cout<<"������һ��ʵ��a��һ������n��";
	cin>>a>>n;
	cout<<"a��n����/(1+2+3+...+n)="<<f(a,n)/g(n)<<endl;
}