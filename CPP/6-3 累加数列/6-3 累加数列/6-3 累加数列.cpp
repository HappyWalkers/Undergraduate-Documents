// 6-3 累加数列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	static int num[10]={1};
	int i,j;
	for(j=0;j<10;++j)
		for(i=0;i<j;++i)
		num[j]+=num[i];
	for(j=0;j<10;++j)
		cout<<num[j]<<'\n';
	return 0;
}
