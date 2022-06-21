#include<iostream>
using namespace std;
void main()
{
	cout<<"\t\t\t三节行列式计算器"<<endl;
	int a,b,c,d,e,f,g,h,i;
	cout<<"请按从左至右的顺序，从第一行到第三行依次输入三阶行列式的9个数字,每输入一个数字按一个空格";
	cin>>a>>b>>c>>d>>e>>f>>g>>h>>i;
	cout<<"此三节行列式的值为："<<a*e*i+d*h*c+b*f*g-c*e*g-b*d*i-f*h*a<<endl;
}