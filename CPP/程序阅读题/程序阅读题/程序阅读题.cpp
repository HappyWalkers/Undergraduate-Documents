// �����Ķ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
int f(int a)
{
	auto b=0;
	static int c=1;
	b=b+1;
	c=c+1;
	return a+b+c;
}
void main()
{
	int a=2,i;
	for(i=0;i<3;i++)cout<<f(a)<<"";
	cout<<endl;
}