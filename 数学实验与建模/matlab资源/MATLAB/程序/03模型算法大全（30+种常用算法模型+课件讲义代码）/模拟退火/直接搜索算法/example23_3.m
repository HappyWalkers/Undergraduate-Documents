function example23_3 
a=[-1 -2 0;-1 0 0];b=[-1;0]; 
[x,y]=patternsearch(@fun1,rand(1,3),a,b,[],[],[],[],@fun2);  %初始值必须为行向量 
x,y=-y 
%定义目标函数 
function y=fun1(x);   %x为行向量 
c1=[2 3 1]'; c2=[3 1 0]'; 
y=x*c1+x.^2*c2; y=-y; 
%定义非线性约束函数 
function [f,g]=fun2(x); 
f=[x(1)+2*x(1)^2+x(2)+2*x(2)^2+x(3)-10 
   x(1)+x(1)^2+x(2)+x(2)^2-x(3)-50 
   2*x(1)+x(1)^2+2*x(2)+x(3)-40]; 
g=x(1)^2+x(3)-2; 