clear
close all
clc

hos1=[239,1302];
hos2=[78,1151];
hos3=[30,1237];

x1=hos1(1);
x2=hos2(1);
x3=hos3(1);

y1=hos1(2);
y2=hos2(2);
y3=hos3(2);

a=dis(hos2,hos3);
b=dis(hos1,hos3);
c=dis(hos1,hos2);

p=(a+b+c)/2;
s=sqrt(p*(p-a)*(p-b)*(p-c));

g=y1*(c*c-b*b) + y2*(a*a-c*c) + y3*(b*b-a*a);
h=x1*(c*c-b*b) + x2*(a*a-c*c) + x3*(b*b-a*a);

mole_x=x1*(4*s+sqrt(3)*a*a) +x2*(4*s+sqrt(3)*b*b)+x3*(4*s+sqrt(3)*c*c)+g;
deno_x=12*s + sqrt(3)* (a*a+b*b+c*c);
x=mole_x/deno_x;

mole_y=y1*(4*s+sqrt(3)*a*a) +y2*(4*s+sqrt(3)*b*b)+y3*(4*s+sqrt(3)*c*c)-h;
deno_y=12*s + sqrt(3)* (a*a+b*b+c*c);
y=mole_y/deno_y;

feima=[x,y]
