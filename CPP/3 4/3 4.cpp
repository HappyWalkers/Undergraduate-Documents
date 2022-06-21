#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int n;
	float d,sum=0,rmb1,rmb2;
	while(1)
	{
		cout<<"请输入单价和数量:";
		cin>>d>>n;
		if(n==0)
			break;
		sum=sum+d*n;
	}
	cout<<"-------------------"<<endl;
	cout<<setiosflags(ios::fixed)<<setprecision(2);
	cout<<"总计："<<sum<<endl;
	cout<<"应收："<<sum<<endl;
	cout<<"--------------------"<<endl;
	cout<<"现金：";
	cin>>rmb1;
	rmb2=rmb1-sum;
	cout<<"找零："<<rmb2<<endl;
	return 0;
}