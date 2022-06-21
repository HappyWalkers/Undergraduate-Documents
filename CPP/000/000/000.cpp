#include "stdafx.h"
#include "iostream"
#include "string"
using namespace std;

template <typename T>T fun(T x,int n){return x+n;}


int main(){
	char a='c';
	cout<<fun(a,1);
	return 0;
}