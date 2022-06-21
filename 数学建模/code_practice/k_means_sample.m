%演示数据
%% 1 random sample
%随机生成三组数据
a = rand(30,2) * 2;
b = rand(30,2) * 5;
c = rand(30,2) * 10;
figure(1);
subplot(2,2,1); 
plot(a(:,1), a(:,2), 'r.'); hold on
plot(b(:,1), b(:,2), 'g*');
plot(c(:,1), c(:,2), 'bx'); hold off
grid on;
title('raw data');

%% 2 K-means cluster
X = [a; b; c];  %需要聚类的数据点
xstart = [2 2; 5 5; 8 8];  %初始聚类中心
subplot(2,2,2);
plot(X(:,1), X(:,2), 'kx'); hold on
plot(xstart(:,1), xstart(:,2), 'r*'); hold off
grid on;
title('raw data center');

[Idx, Center] = K_means(X, xstart);
subplot(2,2,4);
plot(X(Idx==1,1), X(Idx==1,2), 'kx'); hold on
plot(X(Idx==2,1), X(Idx==2,2), 'gx');
plot(X(Idx==3,1), X(Idx==3,2), 'bx');
plot(Center(:,1), Center(:,2), 'r*'); hold off
grid on;
title('K-means cluster result');

disp('xstart = ');
disp(xstart);
disp('Center = ');
disp(Center);