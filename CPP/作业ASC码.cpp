// 作业1。。.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
int main()
{
	int i=0,asci;
	char c;
	cout<<"\t              ASC码对照表"<<endl;
	for(asci=32;asci<=126;asci++)
	{c=asci;
	cout<<c<<"="<<asci<<'\t';
	i++;
	if(i==7)
	{
		i=0;
		cout<<endl;
	}
	}
	cout<<endl;
	return 0;
}

