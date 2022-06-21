clear
close all
clc

load('AllData.mat');

% newgrnn, newrb, newrbe, newpnn
net = newgrnn(INSData(:,4:5)', INSData(:,6)');
HDData = sim(net, INSData(:,4:5)')';

figure;
plot3(INSData(:,4),INSData(:,5),INSData(:,6), '-k.');
hold on;
plot3(INSData(:,4),INSData(:,5),HDData, '-r.');
plot3(INSData(:,1),INSData(:,2),INSData(:,3), '-b.');
plot3(INSData(1,4),INSData(1,5),INSData(1,6), 'k*');
legend('实测数据', '拟合数据','设计数据');
xlabel('坐标X(m)');
ylabel('坐标Y(m)');
zlabel('高程H(m)');





% 将"实测数据"用直线、圆、直缓、圆缓形成拟合曲线。
% 现有的"设计数据"是用其它方法得到的，需要大量人工交互。
% 我们的目标是减少人工干预或不需要人工干预。
