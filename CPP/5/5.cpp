#include<iostream>
using namespace std;
int max(int,int);           //声明自定义函数
void main()                 //主函数
{
	int a,b,c;
	cout<<"input two number:\n";
	cin>>a>>b;
	c=max(a,b);             //调用max函数，将得到的值赋给c
	cout<<"max="<<c<<endl;
}
int max(int x,int y)        //定义max函数，函数值为整型，形式参数x，y为整型
{
	int z;                  //max函数中的声明部分，定义本函数中用到的变量z为整型
	if(x>y)
		z=x;
	else
	    z=y;
	return(z);              //将z的值返回，通过max带回调用处
}
