#include<iostream.h>
#include<cmath>
int main()
{
	float a,b,c,disc,x1,x2,realpart,imagepart;
	cout<<"�����������ϵ����һ����ϵ���ͳ�����:";
	cin>>a>>b>>c;
	if(fabs(a)<=1e-6)
		cout<<"�˷��̲��Ƕ�Ԫһ�η���"<<endl;
	else
	{disc=b*b-4*a*c;
	if(fabs(disc)<=1e-6)
	   {x1=-b/(2*a);
	    cout<<"������������ȵ�ʵ��:"<<x1<<endl;
	}
	else if(disc>1e-6)
	{x1=(-b+sqrt(disc))/(2*a);
	x2=(-b-sqrt(disc))/(2*a);
	cout<<"��������������ʵ��:"<<x1<<','<<x2<<endl;
	}
	else
	{realpart=(-b)/(2*a);
	imagepart=sqrt(-disc)/(2*a);
	cout<<"���������������:"<<endl;
	cout<<realpart<<'+'<<imagepart<<'i'<<endl;
	cout<<realpart<<'-'<<imagepart<<'i'<<endl;
	}
	}
	return 0;
}

