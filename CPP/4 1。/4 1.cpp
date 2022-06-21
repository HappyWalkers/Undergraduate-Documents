#define E 0.000001
#include<iostream>
#include<cmath>
using namespace std;
void main()
{  int i,k=1;
   float x,y,t=1,s,r=1;
   cout<<"Please enter x=";
   cin>>x;
   for(s=x,y=x,i=2;fabs(r)>E;i++)
   {   
	   t=t*(i-1);
	   y=y*x*x;
	   k=k*(-1);
	   r=k*y/t/(2*i-1);
	   s=s+r;
   }
   cout<<"S="<<s<<endl;
}
