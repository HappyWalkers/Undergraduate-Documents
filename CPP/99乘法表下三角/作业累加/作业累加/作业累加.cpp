// ��ҵ�ۼ�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
void main()
{
	int a,s,d,n;
	cout<<"������n��ֵ"<<endl;
	cin>>n;
	for(a=1,d=0;a<=n;a++)
	{
		s=0;
		s+=a;
		d+=s;
	}
	cout<<"s="<<d<<endl;
}
