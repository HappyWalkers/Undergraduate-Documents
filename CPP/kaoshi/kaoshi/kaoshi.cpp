//��� [900, 1000]����ż�������ӣ��������Ӳ���1�����������ж��ٸ���������С��һ����
#include<iostream>
using namespace std;
int count()
{
	int i;
	int x=0;
	int m=0;
	int n;
	for(i=1000;i>=900;i--)
	{
		int t;
		for(t=2;t<i;t++)
		{
			if(i%t==0)
				m++;
		}
		if(m%2==0)
		{
			n=i;
			x++;
		}
	}
	cout<<x<<n<<endl;
	return 0;
}
void main()
{
	count();
}