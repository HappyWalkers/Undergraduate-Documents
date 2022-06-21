%imp.m

%% 清屏
close all
clear
clc
%% 导入数据
NodePos = load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_pos.txt'); %节点位置
NodeDist = load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_topo-error free.txt'); %节点间距离
% NodeDist= load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_topo-error 5.txt');
% NodeDist= load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_topo-error 10.txt');
save('/Users/mine/study/课程/无线定位/result_and_plot/node_pos.mat','NodePos')
save('/Users/mine/study/课程/无线定位/result_and_plot/node_dist.mat','NodeDist')
NodeCount=size(NodePos); %总节点数量

BeaconCount=sum(NodePos(:,4));
% BeaconCount=0; %计算锚节点数量
% for i=1:NodeCount
%     if NodePos(i,4)==1
%         BeaconCount=BeaconCount+1;
%     end
% end

if BeaconCount<3
    disp('锚节点数量不足，不足以计算其他点的距离');
end
UnCount=NodeCount-BeaconCount;%number of normal node
Beacon=NodePos(1:BeaconCount,[1,2,3]); %锚节点的位置坐标
Unknow=NodePos((1+BeaconCount):NodeCount,[1,2,3]); %非锚节点的位置坐标
%画出节点位置图
figure
%plot(Beacon(1:BeaconCount,2),Beacon(1:BeaconCount,3),'r*',Unknow(1:UnCount,2),Unknow(1:UnCount,3),'b.')
plot(Beacon(:,2),Beacon(:,3),'r*',Unknow(:,2),Unknow(:,3),'b.')
title('真实节点分布图')
legend('锚节点','普通节点')
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/课程/无线定位/result_and_plot/real.jpg')
%%
for k=1:11
    for i=(BeaconCount+1):NodeCount%对于普通节点
        num=0;%普通节点所连接的锚节点（有距离）
        if NodePos(i,4)~=1%如果是普通节点（原作者应该是这么想的：因为之后会将计算出位置的节点作为锚节点，因此后面的有可能变为锚节点，然而他是从前往后遍历的啊）
            for j=1:size(NodeDist,1)%遍历连接矩阵，寻找连接的锚节点，达到三个时开始计算位置
                if NodeDist(j,1)==i & NodePos(NodeDist(j,2),4)==1%如果nodeDist第j行第1列为当前普通节点,第2列为锚节点
                    num=num+1;
                    x(num,1)=NodePos( NodeDist(j,2),2);%记录下该普通节点所连接的锚节点位置，距离
                    y(num,1)=NodePos( NodeDist(j,2),3);
                    d(num,1)=NodeDist(j,3);
                elseif NodeDist(j,2)==i & NodePos(NodeDist(j,1),4)==1%如果nodeDist第j行第1列为锚节点，第2列为当前普通节点
                    num=num+1;
                    x(num,1)=NodePos( NodeDist(j,1),2);
                    y(num,1)=NodePos( NodeDist(j,1),3);
                    d(num,1)=NodeDist(j,3);
                end
                if num==3%若普通节点连接的节点（已检测到的）到达三个(有待修改！！！！！！！！！！！！！！！！！！！！！！）
                    NodePos(i,4)=1;%将该普通节点置为锚节点
                    %计算位置与误差
                    A=[2 * ( x(1,1) - x(2,1) ), 2 * ( y(1,1) - y(2,1) );
                        2 * ( x(1,1) - x(3,1) ), 2 * ( y(1,1) - y(3,1) )];
                    b=[ ( d(2,1)^2 - x(2,1)^2 - y(2,1)^2 ) - ( d(1,1)^2 - x(1,1)^2 - y(1,1)^2 );
                        ( d(3,1)^2 - x(3,1)^2 - y(3,1)^2 ) - ( d(1,1)^2 - x(1,1)^2 - y(1,1)^2 )];
                    Z=inv(A'*A)*A'*b;
                    Loc(i,1)=Z(1,1);
                    Loc(i,2)=Z(2,1);
                    % error(i,1)=(abs(Loc(i,1)-NodePos(i,2))/NodePos(i,2)+abs(Loc(i,2)-NodePos(i,3))/NodePos(i,3))/2;%error：x方向相对误差 与 y方向相对误差 的均值
                    error(i,1) = sqrt((NodePos(i,2)-Loc(i,1))^2+(NodePos(i,3)-Loc(i,2))^2);
                end
            end
        end
    end
end


disp(strcat('真实点与估计点间平均距离：', num2str( mean(error(:,1)) ) ) );
figure
plot(NodePos((BeaconCount+1):NodeCount,1),error((BeaconCount+1):NodeCount,1),'-o')
title('imp误差图')
xlabel('普通节点序号')
ylabel('误差')

figure
plot(NodePos((BeaconCount+1):end,2),NodePos((BeaconCount+1):end,3),'bO',Loc((BeaconCount+1):end,1),Loc((BeaconCount+1):end,2),'r*')
for i=BeaconCount+1:NodeCount(1)
    line([NodePos(i,2), Loc(i,1) ], [NodePos(i,3), Loc(i,2)],'Color','g')
end
title('真实节点与预测节点分布')
legend('真实节点','预测节点')
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/课程/无线定位/result_and_plot/imp_real_and_estimated.jpg')

avg = mean(error(:,1));%真实点与估计点间平均距离
dx=0;
for i=BeaconCount:NodeCount(1)
    dx =(sqrt((NodePos(i,2)-Loc(i,1))^2+(NodePos(i,3)-Loc(i,2))^2)-avg)^2+dx;
end
dx = sqrt(dx/UnCount(1));%方差
disp(['方差：',num2str(dx)])


save('/Users/mine/study/课程/无线定位/result_and_plot/imp_results.mat','Loc')
