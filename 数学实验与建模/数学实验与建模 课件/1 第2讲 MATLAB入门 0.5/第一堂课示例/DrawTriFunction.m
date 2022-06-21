clear all % 清除workspace
close all % 关闭所有图形窗口
clc % 清除命令窗口

% 计算三角函数值
x = (0 : 0.01*pi : 2*pi);
y = sin(x);

% 三角函数绘图
figure;
plot(x, y, '-k');
xlabel('x轴');
ylabel('y轴');
title('正弦函数绘图');
axis([min(x) max(x) min(y) max(y)]);
grid on;






