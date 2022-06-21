// 9 3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
class counter
{int n;
public:
	counter(int i=0){n=i;}
	void init_counter(int m){n=m;}
	void in_counter(){n++;}
	void de_counter(){n--;}
	int get_counter(){return n;}
	void display(){cout<<n<<endl;}
};
void main()
{
	counter a;
	a.in_counter ();
	a.display();
	a.init_counter (10);
	a.display();
	a.de_counter();
	cout<<a.get_counter()<<endl;
}