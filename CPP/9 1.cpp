// 9 1.cpp : �������̨Ӧ�ó������ڵ㡣
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
		else cout<<"���ݴ���\n";
	}
	void display(){cout<<"!="<<p<<endl;}
};
void main()
{
	int n;
	cout<<"������һ������:";
		cin>>n;
	fac a(n);
	cout<<n;
	a.display();
}