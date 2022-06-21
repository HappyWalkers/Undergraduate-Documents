// 6-4 二维数表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int a[6][6],i,j;
	for(i=0;i<6;i++)
	{for(j=0;j<6;j++)
	{if((j==0)||(i==j))a[i][j]=1;
	else if(i<j)a[i][j]=j-i+1;
	else a[i][j]=a[i-1][j-1]+a[i-1][j];
	cout<<setw(6)<<a[i][j];
	}
	cout<<'\n';
	}
	return 0;
}
