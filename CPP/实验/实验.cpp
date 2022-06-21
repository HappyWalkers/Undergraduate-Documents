#include<iostream>
using namespace std;
class base
{
public:
	base() { func(); }
	virtual void func() { cout << "In class base" << endl; }
	virtual ~base()																																	
	{
		cout << "Destructing base object" << endl;
	}
};
class A :public base
{
public:
	A() { func(); }
	void f() { func(); }
	~A() { fund(); }
	void fund() { cout << "Destructing A object" << endl; }
};
class B :public A
{
public:
	B() {}
	void func() { cout << "In class B" << endl; }
	~B() { fund(); }
	void fund() { cout << "Destructing B object" << endl; }
};
void main()
{
	B b;
	b.func();
	base* p = new A;
	delete p;
}