// 5-6 e数列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
long int ef(int n);
void main()
{
	int i,n;
	long int e;
	for(i=3;;i++)
		{
			e=ef(i);
			if(e<=30000)
				cout<<"e="<<ef(i)<<endl;
			else break;}
}
long int ef(int n)
{
	if(n==1)return 1;
	else if(n==2)return 1;
	else return(n-1)*ef(n-1)+(n-2)*ef(n-2);
}
