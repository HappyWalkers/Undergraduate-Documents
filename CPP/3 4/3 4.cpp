#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int n;
	float d,sum=0,rmb1,rmb2;
	while(1)
	{
		cout<<"�����뵥�ۺ�����:";
		cin>>d>>n;
		if(n==0)
			break;
		sum=sum+d*n;
	}
	cout<<"-------------------"<<endl;
	cout<<setiosflags(ios::fixed)<<setprecision(2);
	cout<<"�ܼƣ�"<<sum<<endl;
	cout<<"Ӧ�գ�"<<sum<<endl;
	cout<<"--------------------"<<endl;
	cout<<"�ֽ�";
	cin>>rmb1;
	rmb2=rmb1-sum;
	cout<<"���㣺"<<rmb2<<endl;
	return 0;
}