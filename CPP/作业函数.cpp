
#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;
void main()
{
	double x,y;
	cout<<"ÇëÊäÈëxµÄÖµ"<<endl;
	cin>>x;
    if(x!=0)
	cout<<"y="<<sin(x)+sqrt(x*x+1)<<endl;
	else
	cout<<"y="<<cos(x)-x*x+3*x<<endl;
}
