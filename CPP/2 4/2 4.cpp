#include<iostream.h>
#include<cmath>
int main()
{
	float a,b,c,disc,x1,x2,realpart,imagepart;
	cout<<"请输入二次项系数、一次项系数和常数项:";
	cin>>a>>b>>c;
	if(fabs(a)<=1e-6)
		cout<<"此方程不是二元一次方程"<<endl;
	else
	{disc=b*b-4*a*c;
	if(fabs(disc)<=1e-6)
	   {x1=-b/(2*a);
	    cout<<"方程有两个相等的实根:"<<x1<<endl;
	}
	else if(disc>1e-6)
	{x1=(-b+sqrt(disc))/(2*a);
	x2=(-b-sqrt(disc))/(2*a);
	cout<<"方程有两个不等实根:"<<x1<<','<<x2<<endl;
	}
	else
	{realpart=(-b)/(2*a);
	imagepart=sqrt(-disc)/(2*a);
	cout<<"方程有两个共轭复根:"<<endl;
	cout<<realpart<<'+'<<imagepart<<'i'<<endl;
	cout<<realpart<<'-'<<imagepart<<'i'<<endl;
	}
	}
	return 0;
}

