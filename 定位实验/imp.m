%imp.m

%% ����
close all
clear
clc
%% ��������
NodePos = load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_pos.txt'); %�ڵ�λ��
NodeDist = load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_topo-error free.txt'); %�ڵ�����
% NodeDist= load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_topo-error 5.txt');
% NodeDist= load('/Users/mine/study/�γ�/���߶�λ/��������λ����ʵ��2020/ʵ�����ο�����/net1_topo-error 10.txt');
save('/Users/mine/study/�γ�/���߶�λ/result_and_plot/node_pos.mat','NodePos')
save('/Users/mine/study/�γ�/���߶�λ/result_and_plot/node_dist.mat','NodeDist')
NodeCount=size(NodePos); %�ܽڵ�����

BeaconCount=sum(NodePos(:,4));
% BeaconCount=0; %����ê�ڵ�����
% for i=1:NodeCount
%     if NodePos(i,4)==1
%         BeaconCount=BeaconCount+1;
%     end
% end

if BeaconCount<3
    disp('ê�ڵ��������㣬�����Լ���������ľ���');
end
UnCount=NodeCount-BeaconCount;%number of normal node
Beacon=NodePos(1:BeaconCount,[1,2,3]); %ê�ڵ��λ������
Unknow=NodePos((1+BeaconCount):NodeCount,[1,2,3]); %��ê�ڵ��λ������
%�����ڵ�λ��ͼ
figure
%plot(Beacon(1:BeaconCount,2),Beacon(1:BeaconCount,3),'r*',Unknow(1:UnCount,2),Unknow(1:UnCount,3),'b.')
plot(Beacon(:,2),Beacon(:,3),'r*',Unknow(:,2),Unknow(:,3),'b.')
title('��ʵ�ڵ�ֲ�ͼ')
legend('ê�ڵ�','��ͨ�ڵ�')
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/�γ�/���߶�λ/result_and_plot/real.jpg')
%%
for k=1:11
    for i=(BeaconCount+1):NodeCount%������ͨ�ڵ�
        num=0;%��ͨ�ڵ������ӵ�ê�ڵ㣨�о��룩
        if NodePos(i,4)~=1%�������ͨ�ڵ㣨ԭ����Ӧ������ô��ģ���Ϊ֮��Ὣ�����λ�õĽڵ���Ϊê�ڵ㣬��˺�����п��ܱ�Ϊê�ڵ㣬Ȼ�����Ǵ�ǰ��������İ���
            for j=1:size(NodeDist,1)%�������Ӿ���Ѱ�����ӵ�ê�ڵ㣬�ﵽ����ʱ��ʼ����λ��
                if NodeDist(j,1)==i & NodePos(NodeDist(j,2),4)==1%���nodeDist��j�е�1��Ϊ��ǰ��ͨ�ڵ�,��2��Ϊê�ڵ�
                    num=num+1;
                    x(num,1)=NodePos( NodeDist(j,2),2);%��¼�¸���ͨ�ڵ������ӵ�ê�ڵ�λ�ã�����
                    y(num,1)=NodePos( NodeDist(j,2),3);
                    d(num,1)=NodeDist(j,3);
                elseif NodeDist(j,2)==i & NodePos(NodeDist(j,1),4)==1%���nodeDist��j�е�1��Ϊê�ڵ㣬��2��Ϊ��ǰ��ͨ�ڵ�
                    num=num+1;
                    x(num,1)=NodePos( NodeDist(j,1),2);
                    y(num,1)=NodePos( NodeDist(j,1),3);
                    d(num,1)=NodeDist(j,3);
                end
                if num==3%����ͨ�ڵ����ӵĽڵ㣨�Ѽ�⵽�ģ���������(�д��޸ģ���������������������������������������������
                    NodePos(i,4)=1;%������ͨ�ڵ���Ϊê�ڵ�
                    %����λ�������
                    A=[2 * ( x(1,1) - x(2,1) ), 2 * ( y(1,1) - y(2,1) );
                        2 * ( x(1,1) - x(3,1) ), 2 * ( y(1,1) - y(3,1) )];
                    b=[ ( d(2,1)^2 - x(2,1)^2 - y(2,1)^2 ) - ( d(1,1)^2 - x(1,1)^2 - y(1,1)^2 );
                        ( d(3,1)^2 - x(3,1)^2 - y(3,1)^2 ) - ( d(1,1)^2 - x(1,1)^2 - y(1,1)^2 )];
                    Z=inv(A'*A)*A'*b;
                    Loc(i,1)=Z(1,1);
                    Loc(i,2)=Z(2,1);
                    % error(i,1)=(abs(Loc(i,1)-NodePos(i,2))/NodePos(i,2)+abs(Loc(i,2)-NodePos(i,3))/NodePos(i,3))/2;%error��x���������� �� y���������� �ľ�ֵ
                    error(i,1) = sqrt((NodePos(i,2)-Loc(i,1))^2+(NodePos(i,3)-Loc(i,2))^2);
                end
            end
        end
    end
end


disp(strcat('��ʵ������Ƶ��ƽ�����룺', num2str( mean(error(:,1)) ) ) );
figure
plot(NodePos((BeaconCount+1):NodeCount,1),error((BeaconCount+1):NodeCount,1),'-o')
title('imp���ͼ')
xlabel('��ͨ�ڵ����')
ylabel('���')

figure
plot(NodePos((BeaconCount+1):end,2),NodePos((BeaconCount+1):end,3),'bO',Loc((BeaconCount+1):end,1),Loc((BeaconCount+1):end,2),'r*')
for i=BeaconCount+1:NodeCount(1)
    line([NodePos(i,2), Loc(i,1) ], [NodePos(i,3), Loc(i,2)],'Color','g')
end
title('��ʵ�ڵ���Ԥ��ڵ�ֲ�')
legend('��ʵ�ڵ�','Ԥ��ڵ�')
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/�γ�/���߶�λ/result_and_plot/imp_real_and_estimated.jpg')

avg = mean(error(:,1));%��ʵ������Ƶ��ƽ������
dx=0;
for i=BeaconCount:NodeCount(1)
    dx =(sqrt((NodePos(i,2)-Loc(i,1))^2+(NodePos(i,3)-Loc(i,2))^2)-avg)^2+dx;
end
dx = sqrt(dx/UnCount(1));%����
disp(['���',num2str(dx)])


save('/Users/mine/study/�γ�/���߶�λ/result_and_plot/imp_results.mat','Loc')
