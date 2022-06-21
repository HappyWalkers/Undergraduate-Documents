#include<iostream>
#include<cmath>
using namespace std;
class point
{
public:
	point(int a=0,int b=0){x=a;y=b;}
	int xcord(){return x;}
	int ycord(){return y;}
private:
	int x,y;
};
class Distance
{
public:
	Distance(point q1,point q2);
	double getdist(){return dist;}
private:
	point p1,p2;
	double dist;
};
Distance::Distance(point q1,point q2):p1(q1),p2(q2)
{
	double x=double(p1.xcord()-p2.xcord());
	double y=double(p1.ycord()-p2.ycord());
	dist=sqrt(x*x+y*y);
}
void main()
{
	point p(0,0),q(1,1);
	Distance dis(p,q);
	cout<<"the distance is:"<<dis.getdist()<<endl;
}