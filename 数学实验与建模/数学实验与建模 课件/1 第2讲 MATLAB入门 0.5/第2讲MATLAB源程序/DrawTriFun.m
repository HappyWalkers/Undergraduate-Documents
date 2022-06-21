clear all % 清空变量空间 Workspace
close all % 关闭所有图形窗口
clc  % 命令窗口清屏

% 画正弦曲线
x = (0 : 0.01*pi : 2*pi);
y1 = sin(x);

% 二次函数
y2 = fQuadric(x);

% 画图预处理
XMIN = min(x); 
XMAX = max(x); 
YMIN = min([y1 y2]); 
YMAX = max([y1 y2]);

% 画图
figure;
plot(x, y1, 'r-');
hold on;
plot(x, y2, 'k:');
legend('正弦函数', '二次函数', 'Location', 'SouthWest');
xlabel('x轴');
ylabel('y轴');
title('函数画图');
axis([XMIN XMAX YMIN YMAX])


