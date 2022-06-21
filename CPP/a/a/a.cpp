// a.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
using namespace std;
class A{
public:
	A(){data=0;}
	A(int x){data=x;}
	~A(){}
	int getdata()const{return data;}
	void setdata(int n){data=n;}
private:
	int data;
};
void main()
{
	const A a(5);
	A b(8);
	cout<<a.getdata()<<endl;
}