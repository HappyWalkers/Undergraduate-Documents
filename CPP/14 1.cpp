#include<iostream>
using namespace std;
void main()
{
	int i;
	cout.setf(ios::hex | ios::showbase | ios::uppercase);
	for (i = 0;i < 26;i++)
	{
		cout.width(6);
		cout << ('A' + i);
		if (i % 10 == 9)cout.put('\n');
	}
	cout.put('\n');
}