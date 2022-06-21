clear
close all
clc

syms x y
As = [x.^2   2*x.*y   y.^2   2*x   2*y];

% 观测数据（转置成列向量，以便构造矩阵）
x0 = [5.764, 6.286, 6.759, 7.168, 7.408]';
y0 = [0.648, 1.202, 1.823, 2.526, 3.360]';

% 构造线性方程组 A a = b
A = subs(As, {x, y}, {x0, y0});
b = 0*x0 - 1;

% 显示中间过程
disp('线性方程组 Aa=b 系数:');
disp(num2str(double(A)));
disp(newline);

% 求解线性方程组
a = A\b;
disp('小行星轨道未知数 a 的值:');
disp(num2str(double(a)'));
disp(newline);

f = As * a + 1;
disp('小行星轨道方程:');
disp(matlabFunction(collect(As * round(double(a),4) + 1, x)));
disp(newline);

figure;
plot(x0, y0, 'k*');
hold on;
fimplicit(f, [3 8 -1 5]);
legend('观测点', '小行星轨迹','location','northwest');
xlabel('x');
ylabel('y');
axis([3.9 7.5 -0.3 3.9]);
title('小行星轨道');