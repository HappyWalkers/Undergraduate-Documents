% 蚁群算法示例程序
clc;
clear;
close all;
%% 初始数据输入
x=[82 91 12 92 63 9 28 55 96 97 15 98 96 49 80 14 42 92 80 96];   % 坐标点x坐标
y=[66 3 85 94 68 76 75 39 66 17 71 3 27 4 9 83 70 32 95 3];     % 坐标点y坐标
% x=[1304,3639,4177,3712,3488,3326,3238,4196,4312,4386,3007,2562,2788,2381,1332,3715,3918,4061,3780,3676,4029,4263,3429,3507,3394,3439,2935,3140,2545,2778,2370];
% y=[2312,1315,2244,1399,1535,1556,1229,1004,790,570,1970,1756,1491,1676,695,1678,2179,2370,2212,2578,2838,2931,1908,2367,2643,3201,3240,3550,2357,2826,2975];
[X1,X2]=meshgrid(x,x);
[Y1,Y2]=meshgrid(y,y);
D=sqrt((X1-X2).^2+(Y1-Y2).^2);  % 两点之间距离
N=numel(x);   % 一共有多少个城市 
MaxIt=300;      % 最大迭代次数
nAnt=40;        % 蚂蚁的个数（种群数量）

tau=ones(N,N);   % 初始信息素
eta=1./D;        % 启发因子矩阵,也就是距离的倒数，用于对转移概率的修正
rho=0.05;       % 挥发率 
Tour=zeros(nAnt,N);% 用于记录路径
Cost=zeros(nAnt,1);% 用于记录路径总长度
BestCost=inf;
BestCostALL=Inf(MaxIt,1);
for iter=1:MaxIt   % 迭代次数
    for kAntID=1:nAnt   % 每个蚂蚁分别计算
        Tour(kAntID,1)=randi([1 N]);  % 1到N之间的任意一个整数，作为起始点
        for itourcity=2:N   % 需要走的城市路径下标，因为第一个已经有了，所以这里从2开始编号
            lastcityID=Tour(kAntID,itourcity-1);
            P=tau(lastcityID,:).*eta(lastcityID,:);% 转移概率
            P(Tour(kAntID,1:itourcity-1))=0;   % 禁忌表，已经走过的概率设置为0
            P=P/sum(P);  % 归一化
            r=rand;
            C=cumsum(P);    
            j=find(r<=C,1);   % 根据之前概率分布随机选择一个城市
            Tour(kAntID,itourcity)=j;  % 记录蚂蚁走过的城市
        end
        Ttemp=[Tour(kAntID,:)' Tour(kAntID,[2:end 1])'];  % 当前蚂蚁各段路径的起点终点
        L=0;   % 总路径长度初始值
        for i=1:N
            L=L+D(Ttemp(i,1),Ttemp(i,2)); % 将各段路径长度加起来
        end
        Cost(kAntID)=L;   % 总的路径长度
        if Cost(kAntID)<BestCost    % 如果路径更短
            BestTour=Tour(kAntID,:);  % 更新最佳路径
            BestCost=Cost(kAntID);    % 更新最佳路径长度
        end
    end
    % 更新信息素
    for kAntID=1:nAnt
        tour=[Tour(kAntID,:) Tour(kAntID,1)]; %  首尾相连的完整路径 去掉最后一个首尾不相连
        for itourcity=1:N      %首尾不相连N-1
            i=tour(itourcity);
            j=tour(itourcity+1);
            tau(i,j)=tau(i,j)+1/Cost(kAntID);  
            % 原有信息素，加上新增加的信息素，新增加的信息素按照总长度的倒数来计算
        end
    end
    % 信息素挥发
    tau=(1-rho)*tau;
    % 存储每代最优结果
    BestCostALL(iter)=BestCost;
    
    % 显示迭代结果信息
    disp(['Iteration ' num2str(iter) ': Best Cost = ' num2str(BestCostALL(iter))]);
    
    % 绘制中间结果图
    PlotSolution(BestTour,x,y);
    pause(0.01);
    
end

%% 结果

figure;
plot(BestCostALL,'LineWidth',2);
xlabel('Iteration');
ylabel('Best Cost');
grid on;