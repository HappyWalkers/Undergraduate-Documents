clear
close all
clc

%首先输入下列系数：
f = [13 9 10 11 12 8];
A =  [0.4 1.1 1 0 0 0
      0 0 0 0.5 1.2 1.3];
b = [800; 900];
Aeq=[1 0 0 1 0 0
     0 1 0 0 1 0
     0 0 1 0 0 1];
beq=[400 600 500];
vlb = zeros(6,1);

%然后调用linprog函数：
[x1,fval1] = linprog(f,A,b,Aeq,beq,vlb);

intconstrain = (1:6);
[x2, fval2] = intlinprog(f, intconstrain,A,b,Aeq,beq,vlb);

disp('linprog结果');
disp(['x= ' num2str(x1')]);
disp(['z= ' num2str(fval1)])

disp('intlinprog');
disp(['x= ' num2str(x2')]);
disp(['z= ' num2str(fval2)])
