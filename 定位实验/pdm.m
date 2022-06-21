%pdm.m
% square_L: 正方形区域的边长，单位：m 
% comm_r: 通信半径，单位：m 
% node_n(1): 网络节点的个数 
% anchor_n: 信标节点个数 
% unknown_n: 未知节点个数 
% xy:存储矩阵中每个点的坐标 
% adjacency_m: 邻接矩阵 
% hop: 跳数矩阵
clear
close all
clc

square_L = 250;
comm_r = 20;
anchor_n = 0; %锚节点
unknown_n = 0; %未知节点
xy = load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_pos.txt');
Data_road1 = load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_topo-error free.txt');
% Data_road1= load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_topo-error 5.txt');
% Data_road1= load('/Users/mine/study/课程/无线定位/物联网定位技术实验2020/实验三参考资料/net1_topo-error 10.txt');

node_n = size(xy);
dis_n = size(Data_road1);
anchor = [];
unknown = [];
%分辨锚节点和未知节点
for i = 1:node_n(1)
    if xy(i,4) == 1
        anchor_n = anchor_n+1;%锚节点个数
        anchor = [anchor transpose(xy(i,:))];%锚节点矩阵
    else
        unknown_n = unknown_n+1;%普通节点个数
        unknown = [unknown transpose(xy(i,:))];%普通节点矩阵
    end
end
if anchor_n < 3
    disp('锚节点少于 3 个,DV-hop 算法无法执行');
    return;
end
xy = [anchor unknown];%先锚节点，后普通节点
for i=1:node_n(1)%初始化跳数矩阵，自己到自己为0，到其他人为无穷
    for j=1:node_n(1)
        if i==j
            hop(i,j) = 0;
            dis(i,j) = 0;
        else
            hop(i,j) = inf;
            dis(i,j) = inf;
        end
    end
end
% 计算锚节点之间距离
adjacency_m = zeros(node_n(1),node_n(1));
%距离矩阵
for i=1:dis_n(1)%初始化跳数矩阵与邻接矩阵，dis中给了的，将跳数置1，距离置为直接距离
    hop(Data_road1(i,1),Data_road1(i,2)) = 1;
    dis(Data_road1(i,1),Data_road1(i,2)) = Data_road1(i,3);
    hop(Data_road1(i,2),Data_road1(i,1)) = 1;
    dis(Data_road1(i,2),Data_road1(i,1)) = Data_road1(i,3);
end
for i=1:anchor_n%计算出锚节点之间的距离，填入距离矩阵
    for j=1:anchor_n
        dis(i,j) = sqrt( (xy(2,i)-xy(2,j))^2+(xy(3,i)-xy(3,j))^2 );
    end
end

% Flyod 算法求最短跳数，计算跳数矩阵
for k=1:node_n(1)
    for i=1:node_n(1)
        for j=1:node_n(1)
            if hop(i,k)+hop(k,j)<hop(i,j)
                hop(i,j)=hop(i,k)+hop(k,j);
            end
        end
    end
end

%dis:所有节点间距离，左上角为锚节点间距离
%hop为所有节点间最短跳数矩阵
dis_aa=dis(1:anchor_n,1:anchor_n);
hop_aa=hop(1:anchor_n,1:anchor_n);
hop_an=hop(1:anchor_n,anchor_n+1:end);
%计算锚节点间跳数距离转换矩阵
t_aa=dis_aa*transpose(hop_aa)*inv((hop_aa*transpose(hop_aa)));
%根据转换矩阵计算锚节点到普通节点间距离
dis_an=t_aa*hop_an;



%根据距离计算普通节点位置
esxy=[xy(2,1:node_n(1));xy(3,1:node_n(1))];% 估计坐标矩阵
for i=anchor_n+1:node_n(1)%对于所有普通节点
    A=zeros(anchor_n-1,2);
    b=zeros(anchor_n-1,1);
    X=zeros(2,1);% [x;y]
    for j=1:anchor_n-1%锚节点
        A(j,1)=2*(anchor(2,j)-anchor(2,anchor_n)); % 2(xj-xn)
        A(j,2)=2*(anchor(3,j)-anchor(3,anchor_n)); % 2(yj-yn)
        %bj = xj^2-xn^2+yj^2-yn^2+dn^2-dj^2
        %dn^2 - dj^2 = (hop(i,n)*hopdis(i))^2-(hop(i,j)*hopdis(i))^2
        b(j)=anchor(2,j)^2 - anchor(2,anchor_n)^2 + anchor(3,j)^2 ...
            -anchor(3,anchor_n)^2 + dis_an(anchor_n,i-anchor_n)^2-dis_an(j,i-anchor_n)^2;
    end
    %X=(A'*A)^-1*A'*b
    X=inv(A'*A)*A'*b;
    esxy(1,i)=X(1);
    esxy(2,i)=X(2);
end
% 画定位误差图
figure
avg = 0;
dx = 0; %方差

plot(xy(2,:),xy(3,:), 'bO',esxy(1,:),esxy(2,:),'r*'); hold on;
for i=1:node_n(1)
    line([xy(2,i),esxy(1,i)],[xy(3,i),esxy(2,i)],'Color','g')
    hold on;
end
legend('真实点','估计点');
xlim([0,200]);
ylim([0,200]);
title('pdm定位误差图');
xlabel('x')
ylabel('y')
saveas(gcf,'/Users/mine/study/课程/无线定位/result_and_plot/pdm_real_and_esti.jpg')
%计算方差（对于估计点）
for i=anchor_n:node_n(1)
    avg = avg+sqrt((xy(2,i)-esxy(1,i))^2+(xy(3,i)-esxy(2,i))^2);%真实点与估计点间欧式距离之和
end
avg = avg/unknown_n;%真实点与估计点间平均距离
disp(['真实点与估计点间平均距离：',num2str(avg)])
for i=anchor_n:node_n(1)
    dx =(sqrt((xy(2,i)-esxy(1,i))^2+(xy(3,i)-esxy(2,i))^2)-avg)^2+dx;
end
dx = sqrt(dx/unknown_n);%方差
disp(['方差：',num2str(dx)])
esxy=esxy';
save('/Users/mine/study/课程/无线定位/result_and_plot/pdm_results.mat','esxy')