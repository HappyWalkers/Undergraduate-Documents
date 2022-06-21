// 4 4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<cmath>
using namespace std;
void main()
{
	long int i,x,y,z;
	for(i=1;i<100000;i++)
	{x=sqrt(i+100.);
	 y=sqrt(i+268.);
	 if(x*x==i+100&&y*y==i+268)
		cout<<i<<'\n';
	 
	}
	
}

