function createfigure(YMatrix1, Y1)
%CREATEFIGURE(YMatrix1, Y1)
%  YMATRIX1:  y 数据的矩阵
%  Y1:  stem y

%  由 MATLAB 于 20-Feb-2020 23:56:51 自动生成

% 创建 figure
figure1 = figure;

% 创建 subplot
subplot1 = subplot(2,1,1,'Parent',figure1);
hold(subplot1,'on');

% 使用 plot 的矩阵输入创建多行
plot1 = plot(YMatrix1,'Parent',subplot1);
set(plot1(1),'DisplayName','Observed');
set(plot1(2),'DisplayName','Forecast','Marker','.');

% 创建 ylabel
ylabel('degree');

% 创建 title
title('Forecast');

box(subplot1,'on');
% 创建 legend
legend(subplot1,'show');

% 创建 subplot
subplot2 = subplot(2,1,2,'Parent',figure1);
hold(subplot2,'on');

% 创建 stem
stem(Y1,'Parent',subplot2);

% 创建 ylabel
ylabel('Error');

% 创建 xlabel
xlabel('time');

% 创建 title
title('RMSE = 0.67912');

box(subplot2,'on');
