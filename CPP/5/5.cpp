#include<iostream>
using namespace std;
int max(int,int);           //�����Զ��庯��
void main()                 //������
{
	int a,b,c;
	cout<<"input two number:\n";
	cin>>a>>b;
	c=max(a,b);             //����max���������õ���ֵ����c
	cout<<"max="<<c<<endl;
}
int max(int x,int y)        //����max����������ֵΪ���ͣ���ʽ����x��yΪ����
{
	int z;                  //max�����е��������֣����屾�������õ��ı���zΪ����
	if(x>y)
		z=x;
	else
	    z=y;
	return(z);              //��z��ֵ���أ�ͨ��max���ص��ô�
}
