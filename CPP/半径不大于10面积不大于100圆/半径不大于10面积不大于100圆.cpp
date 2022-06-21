#include <iostream.h>
const float PI=3.14159;
int main()
{
	int r;
	cout<<"圆面积:"<<endl;
	for(r=1;PI*r*r<=100;r++)
	{
		cout<<"圆半径="<<r<<",圆面积="<<PI*r*r<<endl;
	}
	return 0;
}