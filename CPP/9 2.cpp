// 9 2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
class Box
{
	int x,y,z,v,s;
public:
	void init(int x1=0,int y1=0,int z1=0){x=x1;y=y1;z=z1;}
	void volue(){v=x*y*z;}
	void area(){s=2*(x*y+x*z+y*z);}
	void display()
	{cout<<"x="<<x<<",y="<<y<<",z="<<z<<endl;
	cout<<"s="<<s<<",v="<<v<<endl;
	}
};
void main()
{
	Box a;
	a.init (2,3,4);
	a.volue();
	a.area();
	a.display();
}
