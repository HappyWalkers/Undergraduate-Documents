function [b,u,w]=mintrees(a,k)%最小生成树 ，a 邻接矩阵，k 起点
if nargout==1
    k=1;
end
[m,n]=size(a);
for i=1:m
    for j=1:n
        if a(i,j)==0
            a(i,j)=inf;
        end
    end
end
b=zeros(n);
u(1)=k;
j=1;
v=zeros(1,n);
v(k)=1;
for o=1:n-1
    sn=ones(3,n)*inf;
    for xk=1:j
        k=u(xk);
        p=max(a(k,:));
        for i=1:n
            if v(i)<1&a(k,i)<p
                 p=a(k,i);
            end
        end
        for i=1:n
            if v(i)<1&a(k,i)==p
                break;
            end
        end
        sn([1 2 3],k)=[i,p,u(xk)];
    end
    [w(j),k]=min(sn(2,:));
    j=j+1;
    u(j)=sn(1,k);
    b(sn(1,k),sn(3,k))=sn(2,k);
    v(u(j))=1;
end
