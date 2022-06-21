// 7 5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
void secret(char* s)
{
	while(*s!=0)
	{
		if(*s>96&&*s<122)*s=*s+1;
		else if(*s==122)*s='a';
		s++;
	}
}
void desecret(char* s)
{
	while(*s!='\0')
	{
		if(*s>97&&*s<123)*s=*s-1;
		else if(*s==97)*s='z';
		s++;
	}
}
int main()
{
	char st[80];
	cout<<"Input a string:\n";
	cin.getline(st,80,'\n');
	cout<<st<<endl;
	secret(st);
	cout<<st<<endl;
	desecret(st);
	cout<<st<<endl;
	return 0;
}
