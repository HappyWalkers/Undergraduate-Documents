
// 5-5 ��ȫ��2-500.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout<<"��2��500��֮�ڵ���ȫ��֮��="<<s<<endl;
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