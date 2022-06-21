#include<iostream.h>
int main()
{
	int i=0,asci;
	char c;
    cout<<"\t          ASC¢òÂë¶ÔÕÕ±í"<<endl;
	for(asci=32;asci<=126;asci++)
	{
		c=asci;
	    cout<<c<<"="<<asci<<'\t';
		i++;
		if(i==7)
		{
			i=0;
			cout<<endl;
		}
	}
	cout<<endl;
	return 0;
}
