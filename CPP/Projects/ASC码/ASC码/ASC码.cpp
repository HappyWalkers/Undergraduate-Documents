#include"stdafx.h"
#include<iostream>
using namespace std;
int main()
{
	char c;
	cout<<"ÇëÊäÈëÒ»¸ö×Ö·û:";
	cin>>c;
	if((c>='A'&&c<='Z')||(c>='a'&&c<='z'));
		cout<<(int)c<<endl;
	return 0;
}
