clear
close all
clc

f=[6 3 4];
A=[1,2,-3];
b=[80];
Aeq=[1 1 1];
beq=[120];
vlb=[30,0,20];
vub=[inf, 50,inf];
[x,fval]=linprog(f,A,b,Aeq,beq,vlb,vub);
disp(['x= ' num2str(x')]);
disp(['z= ' num2str(fval)]);














