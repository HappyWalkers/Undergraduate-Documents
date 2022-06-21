clear all
close all
clc

x0=linspace(-5,5,11);
y0=1./(1+x0.^2);
x=linspace(-5,5,100);
y1=1./(1+x.^2);

y = interp1(x0, y0, x, 'spline');

figure;
plot(x0, y0, 'k*','MarkerSize', 10);
hold on;
plot(x, y1, 'k-', 'LineWidth', 5);
plot(x, y, 'r:', 'LineWidth', 5);
xlabel('x');
ylabel('y');
title('样条插值示例');
legend('插值节点', '原始函数曲线', '插值曲线');

