#include<iostream.h>
int main()
{
	int m,max,min;
	cout<<"������m:"<<endl;
	cin>>m;
	max=min=m;
	while(cin>>m,m!=0)
	{
		if(m>max)
			max=m;
		if(m<min)
			min=m;
	}
	cout<<"���ֵ="<<max<<endl;
	cout<<"��Сֵ="<<min<<endl;
	return 0;
}