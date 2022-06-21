// 作业累加.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
void main()
{
	int a,s,d,n;
	cout<<"请输入n的值"<<endl;
	cin>>n;
	for(a=1,d=0;a<=n;a++)
	{
		s=0;
		s+=a;
		d+=s;
	}
	cout<<"s="<<d<<endl;
}
