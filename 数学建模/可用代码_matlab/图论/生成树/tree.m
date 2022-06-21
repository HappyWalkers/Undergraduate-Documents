% 生成树算法代码
clear
close all
clc
M=[ 0 17 11 inf inf inf
    17 0 13 12 28 15
    11 13 0 inf 19 inf
    inf 12 inf 0 inf 16
    inf 28 19 inf 0 10
    inf 15 inf 16 10 0];
[m,n]=size(M);
X=zeros(m,n);
Y=zeros(m);
Z=zeros(m);
Y(1)=1;
for i=2:m
    Z(i)=i;
end
judge=1;
while judge
for i=1:m
    if(Y(i)~=0)
        for j=1:m
            if(Z(j)~=0)
                min=M(i,j);
                a=i;
                b=j;
            end
        end
    end
end
for i=1:m
    if(Y(i)~=0)
        for j=1:m
            if(Z(j)~=0)
                if(M(i,j)<min)
                    min=M(i,j);
                    a=i;
                    b=j;
                end
            end
        end
    end
end
Y(b)=b;
Z(b)=0;
X(a,b)=1;
X(b,a)=1;
c=0;
for i=1:m
    if(Y(i)~=0)
        c=c+1;
    end
end
if(c==m)
    judge=0;
end
end