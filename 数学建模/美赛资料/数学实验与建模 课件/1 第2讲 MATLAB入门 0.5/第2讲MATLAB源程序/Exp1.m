close all   % 关闭所有图形对象
clear all   % 清空 workspace
clc

a = eye(3);

disp('a=');
disp(a);

x = 1;
y = fquad(x);
disp(y)

a = [1 2 3 4];
x = [1 0 2];
y = fquadImp(x,a);
disp(y)

x = 10;
y = 3*x^2 + 4*x + 5 ...
    + sin(x) + 10*cos(x);

