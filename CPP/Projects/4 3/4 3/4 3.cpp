// 4 3.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>
using namespace std;
	void main()
{   
	int i,j,k;
	for (i=1;i<5;i++)
		for(j=1;j<5;j++)
			for(k=1;k<5;k++)
			{
				if(i!=k&&i!=j&&j!=k)
					cout<<i<<j<<k<<endl;
			}
}
