function c1ex1
syms x;  % 定义符号变量
f=sin(x)/(x^2+4*x+3);   % 定义函数
f1=diff(f,x,1)    % 求一阶导数
f4=diff(f,x,4)    % 求 4 阶导数