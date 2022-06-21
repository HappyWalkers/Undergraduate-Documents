#include<iostream.h>
int main()
{
	int num1,num2,num3,max;
	cout<<"请输入三个整数:";
	cin>>num1>>num2>>num3;
	if(num1>num2)
		max=num1;
	else
		max=num2;
	if(num3>max)
		max=num3;
	cout<<"三个整数中的最大值 max="<<max<<endl;
	return 0;
}