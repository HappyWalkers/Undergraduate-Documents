#include <iostream.h>
const float PI=3.14159;
int main()
{
	int r;
	cout<<"Բ���:"<<endl;
	for(r=1;PI*r*r<=100;r++)
	{
		cout<<"Բ�뾶="<<r<<",Բ���="<<PI*r*r<<endl;
	}
	return 0;
}