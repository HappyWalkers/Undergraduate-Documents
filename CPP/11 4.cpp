// 11 4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"
using namespace std;
template <class T>
void sort(T a[],int n)
{
	int i,j;
	T temp;
	for(i=1;i<n;i++)
	{
		j=i;
		temp=a[i];
		while(j>0&&temp<a[j-1])
		{
			a[j]=a[j-1];
			j--;
		}
		a[j]=temp;
	}
}
template<class T>
void disp(T a[],int n)
{
	int i;
	for(i=1;i<n;i++)
		cout<<a[i]<<"";
	cout<<endl;
}
void main()
{
	int a[]={3,8,2,6,7,1,4,9,5,0};
	char b[]={'i','d','a','j','b','f','e','c','g','h'};
	cout<<"��������"<<endl;
	cout<<" ԭ����";
	disp(a,10);
	sort(a,10);
	cout<<"�����У�";
	disp(a,10);
	cout<<"�ַ�����"<<endl;
	cout<<" ԭ���У�";
	disp(b,10);
	sort(b,10);
	cout<<" �����У�";
	disp(b,10);
}
