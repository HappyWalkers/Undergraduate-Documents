
// 7 3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
void f(float a,float b,float *area,float &perimeter)
{
	*area=a*b;
	perimeter=2*(a+b);
}
void main()
{
	float length,width,x,y;
	cout<<"\nPlease input length and width:";
	cin>>length>>width;
	f(length,width,&x,y);
	cout<<"\narea="<<x<<"\nperimeter="<<y;
	cout<<'\n';
}
