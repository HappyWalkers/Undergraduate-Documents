
// 。。.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int main()
{
	cout<<"\t\t\t九 九 乘 法 表"<<endl;
	cout<<"\t\t\t---------------"<<endl;
	for(int i=1;i<=9;i++)
	{  
		for(int u=1;u<=i-1;u++)
			cout<<'\t';
		for(int j=i;j<=9;j++)
			cout<<i<<"×"<<j<<'='<<i*j<<'\t';
		cout<<endl;
	
}
return 0;
}