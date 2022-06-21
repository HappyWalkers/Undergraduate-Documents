function [Idx, Center] = K_means(X, xstart)
% K-means聚类
% Idx是数据点属于哪个类的标记，Center是每个类的中心位置
% X是全部二维数据点，xstart是类的初始中心位置

len = length(X);        %X中的数据点个数
Idx = zeros(len, 1);    %每个数据点的Id，即属于哪个类

C1 = xstart(1,:);       %第1类的中心位置
C2 = xstart(2,:);       %第2类的中心位置
C3 = xstart(3,:);       %第3类的中心位置

for i_for = 1:100
    %为避免循环运行时间过长，通常设置一个循环次数
    %或相邻两次聚类中心位置调整幅度小于某阈值则停止
    
    %更新数据点属于哪个类
    for i = 1:len
        x_temp = X(i,:);    %提取出单个数据点
        d1 = norm(x_temp - C1);    %与第1个类的距离
        d2 = norm(x_temp - C2);    %与第2个类的距离
        d3 = norm(x_temp - C3);    %与第3个类的距离
        d = [d1;d2;d3];
        [~, id] = min(d);   %离哪个类最近则属于那个类
        Idx(i) = id;
    end
    
    %更新类的中心位置
    L1 = X(Idx == 1,:);     %属于第1类的数据点
    L2 = X(Idx == 2,:);     %属于第2类的数据点
    L3 = X(Idx == 3,:);     %属于第3类的数据点
    C1 = mean(L1);      %更新第1类的中心位置
    C2 = mean(L2);      %更新第2类的中心位置
    C3 = mean(L3);      %更新第3类的中心位置
end

Center = [C1; C2; C3];  %类的中心位置


