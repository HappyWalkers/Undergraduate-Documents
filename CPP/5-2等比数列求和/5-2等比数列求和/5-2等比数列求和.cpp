// 5-2�ȱ��������.cpp : �������̨Ӧ�ó������ڵ㡣
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
cout<<"������һ������n:";
cin>>n;
cout<<"�����ĺ�Ϊ��"<<f(a,q,n)<<endl;
cout<<"���ʽa/(1-q)��ֵΪ��"<<a/(1-q)<<endl;
}