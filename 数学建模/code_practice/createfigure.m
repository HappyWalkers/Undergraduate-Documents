function createfigure(YMatrix1, Y1)
%CREATEFIGURE(YMatrix1, Y1)
%  YMATRIX1:  y ���ݵľ���
%  Y1:  stem y

%  �� MATLAB �� 20-Feb-2020 23:56:51 �Զ�����

% ���� figure
figure1 = figure;

% ���� subplot
subplot1 = subplot(2,1,1,'Parent',figure1);
hold(subplot1,'on');

% ʹ�� plot �ľ������봴������
plot1 = plot(YMatrix1,'Parent',subplot1);
set(plot1(1),'DisplayName','Observed');
set(plot1(2),'DisplayName','Forecast','Marker','.');

% ���� ylabel
ylabel('degree');

% ���� title
title('Forecast');

box(subplot1,'on');
% ���� legend
legend(subplot1,'show');

% ���� subplot
subplot2 = subplot(2,1,2,'Parent',figure1);
hold(subplot2,'on');

% ���� stem
stem(Y1,'Parent',subplot2);

% ���� ylabel
ylabel('Error');

% ���� xlabel
xlabel('time');

% ���� title
title('RMSE = 0.67912');

box(subplot2,'on');
