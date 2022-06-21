// 9 1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
class fac
{
	int p;
public:

	fac( int j)
	{
		p=1;
		if(j>=0)
			for(int i=1;i<=j;i++)p=p*i;
		else cout<<"数据错误\n";
	}
	void display(){cout<<"!="<<p<<endl;}
};
void main()
{
	int n;
	cout<<"请输入一个整数:";
		cin>>n;
	fac a(n);
	cout<<n;
	a.display();
}