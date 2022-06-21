// 7 4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
void main()
{
	char a[80];
	int i,j;
	cout<<"Input a string:\n";
	cin.getline(a,80,'\n');
	for(i=j=0;a[i];i++)
		if(a[i]>='a'&&a[i]<='z')a[j++]=a[i];
	a[j]='\0';
	cout<<"Then new string is:\n";
		cout<<a<<endl;
}