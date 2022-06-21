// 。。。。。.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
using namespace std;
int is_prime(int x);
void main()
{
    int j,k;
	for(j=100;j=j;j=j+2)
	{for(k=3;k<=j/2;k=k+2)
	if((is_prime(k)==1)&&(is_prime(j-k)==1))
		cout<<j<<"="<<k<<"+"<<j-k<<endl;
	}
}
int is_prime(int x)
{
	int n;
	for (n=2;n<x;n++)
		if(x%n==0) return(0);
	return 1;
}
