#include <stdafx>
#include <iostream.h>
int main()
{
	cout<<"\t\t\t�� �� �� �� ��"<<endl;
	cout<<"\t\t\t---------------"<<endl;
	for(int i=1;i<=9;i++)
	{  
		for(int u=1;u<=i-1;u++)
			cout<<'\t';
		for(int j=i;j<=9;j++)
			cout<<i<<"��"<<j<<'='<<i*j<<'\t';
		cout<<endl;
	
}
return 0;
}