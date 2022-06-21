function [Dd,E,W,S]=TEM(A,B,C)
%参数介绍：
%参数矩阵A是原始数据组成的矩阵。
%参数矩阵B是一个行矩阵，每一个元素由1或0组成（1代表该变量为高优指标；0代表该变量为底优指标）。
%参数矩阵C为一阶方阵，其元素由1或0组成（1代表数据越不混乱，权重越大，0代表数据越混乱，权重越大）
%返回值介绍：
%矩阵Dd是数据标准化后的结果。
%矩阵E的元素是各项指标的信息熵。
%矩阵W的元素是各项指标的权重。
%矩阵S的元素是各个样本的最终评分、及其排序的结果。
[m,n]=size(A);
Dd=[];
D=[];
E=[];
W=[];
S=[];
I=[];
for k=1:n
    if B(k)==1
        Ak=(A(:,k)-min(A(:,k)))./(max(A(:,k))-min(A(:,k)));
        Dd=[Dd,Ak];
    elseif B(k)==0
        Ak=(max(A(:,k))-A(:,k))./(max(A(:,k))-min(A(:,k)));
        Dd=[Dd,Ak];
    end
end
for k=1:n
    Ai=Dd(:,k)./sum(Dd(:,k));
    D=[D,Ai];
end
for k=1:n
    Aa=(-1)*(1/log(m))*(sum(D(:,k).*log(D(:,k)+1e-6)));
    E=[E,Aa];
end
if C==1
    E1=(1-E);
elseif C==0
    E1=E;
end
for k=1:n
    dj=E1(1,k)./sum(E1(1,:));
    W=[W,dj];
end
for k=1:m
    si=sum(W(1,:).*A(k,:));
    S=[S,si];
end  
S1=sort(S,'descend');
for k=1:m
    for w=1:m
        if S(k)==S1(w)
            I=[I;w];
            break
        end
    end
end
S=[S',I];