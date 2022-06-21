
#include<iostream>
using namespace std;
void main()
{
	int i,j,n=0,k=0,min=0;
	for(i=1000;i>=900;i--)
	{
		for(j=2;j<i;j++)
			if(i%j==0) n++;
		if(n%2==0)
		{
			k++;
			min=i;
		}
	}
	cout<<"这样的数有"<<k<<"个"<<endl;
	cout<<"最小的为："<<min<<endl;
}
