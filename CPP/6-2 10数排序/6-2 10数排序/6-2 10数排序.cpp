// 6-2 10数排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int a[11]={0};
	int i;
	for(i=1;i<11;i++)
		cin>>a[i];
	int n,m;
	for(m=1;m<11;m++)
		{ 
	        for(n=1;n<11-m;n++)
				if(a[n]<a[n+1])
			{
				int t;
			    t=a[n];
			    a[n]=a[n+1];
			    a[n+1]=a[n];
		    } 
			 cout<<a[n];
	}
}
