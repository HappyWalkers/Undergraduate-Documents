#include<iostream.h>
int main()
{
	int m,max,min;
	cout<<"输入数m:"<<endl;
	cin>>m;
	max=min=m;
	while(cin>>m,m!=0)
	{
		if(m>max)
			max=m;
		if(m<min)
			min=m;
	}
	cout<<"最大值="<<max<<endl;
	cout<<"最小值="<<min<<endl;
	return 0;
}