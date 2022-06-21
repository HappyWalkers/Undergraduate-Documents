clear; clc

[a ,map]= imread('test.JPG');
I=im2bw(a,0.75);
I=1-I;
Ileast = bwlabel(I,4);   % 标定图像的连通域
nummax = max(Ileast(:)); % 分块数
col=length(I(:,1));      % 行数
row=length(I(1,:));      % 列数
Area_candidate = struct('top',{},'left',{},'bottom',{},'right',{});%初始化结构体
for n=1:nummax
    Area_candidate(n).top=col;
    Area_candidate(n).left=row;
    Area_candidate(n).bottom=0;
    Area_candidate(n).right=0;
end

%判定各个连通域的最小外接矩形的边界的值
for a=1:col
        for b=1:row
            if Ileast(a,b)~=0
               Area_candidate(Ileast(a,b)).top = min ( Area_candidate(Ileast(a,b)).top ,a);%得到各个连通域的边界
               Area_candidate(Ileast(a,b)).left = min ( Area_candidate(Ileast(a,b)).left ,b);
               Area_candidate(Ileast(a,b)).bottom = max ( Area_candidate(Ileast(a,b)).bottom ,a);
               Area_candidate(Ileast(a,b)).right = max ( Area_candidate(Ileast(a,b)).right ,b);
            end
        end
end
%新建的空矩阵上得出图像
I_out=zeros(size(I));
for n=1:nummax
    I_out(Area_candidate(1,n).top:Area_candidate(1,n).bottom , Area_candidate(1,n).left:Area_candidate(1,n).right) =1 ;%填充矩形
end
imshow(I_out)
