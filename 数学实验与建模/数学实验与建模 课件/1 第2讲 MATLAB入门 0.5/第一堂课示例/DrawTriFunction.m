clear all % ���workspace
close all % �ر�����ͼ�δ���
clc % ��������

% �������Ǻ���ֵ
x = (0 : 0.01*pi : 2*pi);
y = sin(x);

% ���Ǻ�����ͼ
figure;
plot(x, y, '-k');
xlabel('x��');
ylabel('y��');
title('���Һ�����ͼ');
axis([min(x) max(x) min(y) max(y)]);
grid on;






