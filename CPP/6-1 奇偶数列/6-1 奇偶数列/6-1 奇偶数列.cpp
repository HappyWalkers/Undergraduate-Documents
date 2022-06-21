// 6-1 奇偶数列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int i,a[21]={0,1,1};
	for(i=3;i<21;i++)
		if(i%2==1)
			a[i]=a[i-1]+a[i-2];
		else
			a[i]=a[i-1]-a[i-2];
	cout<<"The results:"<<endl;
	for(i=1;i<21;i++)
	{if(i%5==1) cout<<endl;
	cout<<setw(6)<<a[i];
	}
	cout<<endl;
	return 0;
}
