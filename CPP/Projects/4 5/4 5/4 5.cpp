// 4 5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;
void main()
{
	float x0,x1,x2,fx0,fx1,fx2;
	do
	{cout<<"enter x1,x2:";
	cin>>x1>>x2;
	fx1=2*(x1*x1*x1)-4*(x1)*(x1)+3*(x1)-6;
	fx2=2*(x2*x2*x2)-4*(x2*x2)+3*(x2)-6;
	}while (fx1*fx2>0);
	do
	{x0=(x1+x2)/2;
	fx0=2*x0*x0*x0-4*x0*x0+3*x0-6;
	if((fx0*fx1)<0)
	{x2=x0;
	fx2=fx0;
	}
	else
	{x1=x0;
	fx1=fx0;
	}
	}while(fabs((double)fx0)>1e-5);
	cout<<"x="<<x0<<'\n';
}


