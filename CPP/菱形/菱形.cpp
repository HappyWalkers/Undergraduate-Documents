#include<iostream.h>
int main()
{
	int row;
	cout<<"����������:";
	cin>>row;
	int i,j,n;
	n=row/2+1;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n-i;j++)
			cout<<' ';
        for(j=1;j<=2*i-1;j++)
			cout<<'*';
		cout<<endl;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=i;j++)
            cout<<' ';
	    for(j=1;j<=row-2*i;j++)
		    cout<<'*';
	    cout<<endl;
	}
return 0;
}