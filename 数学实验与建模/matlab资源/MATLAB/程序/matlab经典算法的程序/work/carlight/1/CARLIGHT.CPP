#include<stdio.h>
#include<math.h>
#define step 1
void f(float x,float y,float z,float b,float *new_x,float *new_y)
{float t1,t2,m1,m2,n1,n2,p1,p2,m,n,p,t;
t1=sqrt(x*x+(b-y)*(b-y)+(15-z)*(15-z));
t2=sqrt(4*x*x+4*y*y+3600);
t=t1*t2;
m1=-4*x*x/t;
n1=4*y*(b-y)/t;
p1=120*(z-15)/t;
t=sqrt(x*x+(b-y)*(b-y)+(15-z)*(15-z));
m2=-x/t;
n2=(b-y)/t;
p2=(15-z)/t;
m=m1-m2;
n=n1-n2;p=p1-p2;
*new_x=x+m*(25000-z)/p;
*new_y=y+n*(25000-z)/p;
}
int main()
{float k1=21.6,k2,l=3.12;
 float x,y,z,b,new_x=0,new_y=0,nx=1,ny=1;
 FILE *fout=NULL;
 clrscr();
 if((fout=fopen("c:\\grid.txt","wt"))==NULL)return -1;
 printf("please wait...\n");
 for(z=k1;z>=0;z=z-step)
 {k2=sqrt(60*z);
  for(x=-k2;x<=k2;x=x+step)
  {if(x!=0)y=sqrt(fabs(60*z-x*x));
   else y=0;
   for(b=-l/2;b<=l/2;b=b+step)
   {f(x,y,z,b,&new_x,&new_y);
   fprintf(fout,"%f %f\n",new_x,new_y);
   }
   if(x!=0)y=-sqrt(fabs(60*z-x*x));else y=0;
   for(b=-l/2;b<=l/2;b=b+step)
   {f(x,y,z,b,&new_x,&new_y);
   fprintf(fout,"%f %f\n",new_x,new_y);
   }
  }
 }
fclose(fout);printf("finished!");getch();return 0;
}