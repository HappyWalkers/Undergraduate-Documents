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
legend('ʵ������', '�������','�������');
xlabel('����X(m)');
ylabel('����Y(m)');
zlabel('�߳�H(m)');





% ��"ʵ������"��ֱ�ߡ�Բ��ֱ����Բ���γ�������ߡ�
% ���е�"�������"�������������õ��ģ���Ҫ�����˹�������
% ���ǵ�Ŀ���Ǽ����˹���Ԥ����Ҫ�˹���Ԥ��
