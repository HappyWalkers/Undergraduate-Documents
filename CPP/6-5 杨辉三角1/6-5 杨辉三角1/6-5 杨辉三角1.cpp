// 6-5 杨辉三角.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{int i,j,a[5][5];
  for(i=0;i<5;i++)
   {a[i][0]=1;a[i][i]=1;
       for(j=1;j<i;j++)a[i][j]=a[i-1][j-1]+a[i-1][j];}
       for(i=0;i<5;i++)
       {cout<<"\n";
        for(j=0;j<=i;j++)
			cout<<setw(6)<<a[i][j];}
        cout<<"\n";
        return 0;
}