% Dijkstra算法步骤
% （1）构造邻接矩阵
% （2）定义起始点
% （3）运行代码
clear
close all
clc
M=[  0     5     9   Inf   Inf   Inf   Inf
   Inf     0   Inf   Inf    12   Inf   Inf
   Inf     3     0    15   Inf    23   Inf
   Inf     6   Inf     0   Inf     8     7
   Inf    12   Inf     5     0   Inf    14
   Inf   Inf   Inf   Inf   Inf     0    10
   Inf   Inf   Inf   Inf   Inf   Inf     0];
%算两点间最小距离
first=2;
last=4;
[m,n]=size(M);
L=zeros(1,m);
symbol=zeros(1,m);
direction=zeros(1,m);
for i=1:m
    if(i~=first)
        L(i)=inf;
    end
    direction(i)=first;
end
judge=1;
while judge
for i=1:m
    if(symbol(i)==0)
        min=L(i);
        temporary=i;
        break
    end
end
for i=1:m
    if(symbol(i)==0)
        if(L(i)<min)
            min=L(i);
            temporary=i;
        end
    end
end
k=temporary;
for j=1:m
    if(symbol(1,j)==0)
        if(M(k,j)==inf)
            continue;
        else
            if(L(k)+M(k,j)<L(j))
                L(j)=L(k)+M(k,j);
                direction(j)=k;
            end
        end
    end
end
symbol(k)=1;
num=0;
for i=1:m
    if(symbol(i)==1)
        num=num+1;
    end
end
if(num==m)
    judge=0;
end
end
p=last;
arrow=zeros(1,m);
arrow(1)=last;
i=2;
while p~=first
    arrow(1,i)=direction(p);
    i=i+1;
    p=direction(p);
end
distance=L(last);