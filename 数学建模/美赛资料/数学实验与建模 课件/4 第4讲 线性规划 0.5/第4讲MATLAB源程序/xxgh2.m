clear
close all
clc

c= -[0.4 0.28 0.32 0.72 0.64 0.6];
A=[ 0.01 0.01 0.01 0.03 0.03 0.03;
    0.02 0    0 0.05 0 0;
    0    0.02 0 0 0.05 0;
    0    0    0.03 0 0 0.08];
b=[850 700 100 900];
vlb=0*c;
[x,fval]=linprog(c,A,b,[],[],vlb);
disp(['x= ' num2str(x')]);
disp(['z= ' num2str(-fval)])
