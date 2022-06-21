#include<iostream.h>
void main()
{
	int n,i;
	cout<<"\nplease input a number:";
	cin>>n;
	cout<<n<<'=';
	for(i=2;i<=n;i++)
	{
		while(n!=i)
		{
			if(n%i==0)
			{cout<<i<<'*';
			n/=i;
			}
			else
				break;
		}
	}
	cout<<n<<endl;
}

            