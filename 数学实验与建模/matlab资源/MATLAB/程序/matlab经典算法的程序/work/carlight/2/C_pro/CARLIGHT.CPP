#include<stdio.h>
#include<math.h>
#define step 0.2
void pannel(float x0,float y0,float z0,float b,float *x,float *y)
{float f1,f2,f3,l20x,l20y,l20z;

f1=-2*x0*x0+2*y0*(b-y0)+60*(z0-15);
f2=4*x0*x0+4*y0*y0+3600;
f3=sqrt(x0*x0+(b-y0)*(b-y0)+(15-z0)*(15-z0));

l20x=(4*f1*x0+f2*x0)/(f2*f3);
l20y=(4*f1*y0-f2*(b-y0))/(f2*f3);
l20z=(-120*f1-f2*(15-z0))/(f2*f3);

*x=x0+(25000-z0)*l20x/l20z;
*y=y0+(25000-z0)*l20y/l20z;
}
int main()
{float x0,y0,z0,b,l=3.8,x,y;
 FILE *fout=NULL;
 clrscr();
 if((fout=fopen("c:\\gridcar.txt","wt"))==NULL)return -1;
 printf("please wait...\n");
 for(z0=21.6;z0>=0;z0=z0-step)
 {
  for(x0=-sqrt(60*z0);x0<=sqrt(60*z0);x0=x0+step)
  {y0=sqrt(fabs(60*z0-x0*x0));
   for(b=-l/2;b<=l/2;b=b+step)
   {pannel(x0,y0,z0,b,&x,&y);
   fprintf(fout,"%f %f\n",x,y);}
   y0=-sqrt(fabs(60*z0-x0*x0));
   for(b=-l/2;b<=l/2;b=b+step)
   {pannel(x0,y0,z0,b,&x,&y);
   fprintf(fout,"%f %f\n",x,y);
   }
  }
 }
fclose(fout);printf("finished!");getch();return 0;
}