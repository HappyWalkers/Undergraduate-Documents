clear all % ��ձ����ռ� Workspace
close all % �ر�����ͼ�δ���
clc  % ���������

% ����������
x = (0 : 0.01*pi : 2*pi);
y1 = sin(x);

% ���κ���
y2 = fQuadric(x);

% ��ͼԤ����
XMIN = min(x); 
XMAX = max(x); 
YMIN = min([y1 y2]); 
YMAX = max([y1 y2]);

% ��ͼ
figure;
plot(x, y1, 'r-');
hold on;
plot(x, y2, 'k:');
legend('���Һ���', '���κ���', 'Location', 'SouthWest');
xlabel('x��');
ylabel('y��');
title('������ͼ');
axis([XMIN XMAX YMIN YMAX])


