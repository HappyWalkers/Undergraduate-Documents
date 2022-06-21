// 静态成员函数测试.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
class MyObj
{
	int i,s;
	static int k;
public:
	MyObj()
	{
		s=0;
		for(i=1;i<=10;i++)
		{s+=i;k++;}
	}
	void Display()
	{
		cout<<"i="<<i<<",k="<<k<<",s="<<s<<endl;
	}

};
int MyObj::k=0;
void main()
{
	MyObj A;
	A.Display();
	MyObj B;
	B.Display();
}

