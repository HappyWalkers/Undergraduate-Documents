// 9 4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
class complex
{
	float
		a,b;
public:
	complex(){}
	complex(float x,float y)
	{a=x;b=y;}
	void mult(complex &s)
	{
		if(&s==this)
			cout<<"���������"<<endl;
		else
		{
			float x=a*s.a-b*s.b;
			float y=a*s.b+b*s.a;
			a=x;b=y;
		}
	}
	void display()
	{
		if(b>0)
			cout<<a<<"+"<<b<<"i"<<endl;
		else
		cout<<a<<"-"<<-b<<"i"<<endl;
	}
	};
	void main()
	{
		complex s1(2,3),s2(3,4);
		cout<<"����s1:";s1.display();
		cout<<"����s2:";s2.display();
		s1.mult(s2);
		cout<<"��˽��:";s1.display();
		cout<<endl;
	}