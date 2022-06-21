#include "stdafx.h"
#include "string"
#include "iostream"
using namespace std;
class wheel
{
public:
	wheel(string s="w"):name(s){cout<<name;}
	~wheel(){cout<<name;}
private:
	string name;
};
class bicycle
{
public:
	bicycle(string br="G",string r="R",string f="F"):brand(br),rear(r),front(f){cout<<brand;}
	~bicycle(){cout<<brand;}
private:
	wheel rear,front;
	string brand;
};
int main()
{
	bicycle bike;
	return 0;
}